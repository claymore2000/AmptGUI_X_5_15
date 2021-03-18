/****************************************************************************
**
**
****************************************************************************/
#include <QTime>
#include <QDateTime>
#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionMatch>


#include "parseParameterBlockThread.h"
#include "amptgui_x_status.h"
#include "amptgui_x_utilities.h"
#include "amptparameterblockconstants.h"

static const QString formatIt("yyyy_MM_dd_HH_mm_ss");

//QMap<QString, int>::const_iterator qSIIter;
//QMap<QString, bool>::const_iterator qSBIter;
//static QMap<QString, QVector<QString>>::const_iterator qSVIter;

// static int IntervalToReadParameterBlockInMS = 720 * 2 * 2;

ParseParameterBlockThread::ParseParameterBlockThread(QObject *parent) :
    QThread(parent)
{
    m_newReadOfParameterBlock = false;
    m_parameterBlockReadTimerRunning = false;
    m_parametersAutoRead = false;
}

ParseParameterBlockThread::~ParseParameterBlockThread()
{
    m_mutex.lock();
    m_operational = false;
    m_cond.wakeOne();
    m_mutex.unlock();
    wait();
}

void ParseParameterBlockThread::setCurrentOptimizerFamily(QString s)
{
      m_currentOptimizerFamily = s;
      qDebug() << Q_FUNC_INFO << " setting current family to " << s << Qt::endl;
}

void ParseParameterBlockThread::stopParseParameterBlockThreadOperation( void )
{
    m_operational = false;
}

void ParseParameterBlockThread::handleOTADataThreadCoeffsMessage( const QString s)
{
    const QMutexLocker locker(&m_mutex);
    m_otaParameterBlockCoeffLineToParseList.append(s);
    // qDebug() << Q_FUNC_INFO << " INFO: received Coeff line, size of queue:" << m_otaParameterBlockCoeffLineToParseList.size();
}


void ParseParameterBlockThread::parseOTAParameterBlockData(const QString & data)
{

    const QMutexLocker locker(&m_mutex);
    m_otaParameterBlockDataToParseList.append(data);
    // qDebug() << Q_FUNC_INFO << " received PB info " << data << " size of queue:" << m_otaParameterBlockDataToParseList.size();
}

void ParseParameterBlockThread::startParseParameterBlockThreadInterface(int waitTimeout, const bool logging)
{
    const QMutexLocker locker(&m_mutex);
    m_waitTimeout = waitTimeout;
    m_logData = logging;
	m_operational = true;

	if (m_logData)
	  {
		// Create name, try to open for write,
	  }

    if (!isRunning())
        start();
    else
        m_cond.wakeOne();
}

void ParseParameterBlockThread::handleParseParameterBlockTimerExpired( void )
{
    // qDebug() << Q_FUNC_INFO << " sending signal to re-enable reading parameter blocks from GUI.";
    m_parameterBlockReadTimerRunning = false;
    m_expectedPBInformationForMAC.clear();
    emit enableReadParameterBlocks(true);
}

void ParseParameterBlockThread::handleParseParameterBlockTimerStarted( void )
{
    qDebug() << Q_FUNC_INFO << " received parameter block timer started, parsing should begin.";
    m_parameterBlockReadTimerRunning = true;

}

void ParseParameterBlockThread::handleParametersAutoRead(bool s)
{
    // qDebug() << Q_FUNC_INFO << " INFO: AutoRead PBs => " << s;
    m_parametersAutoRead = s;
}

void ParseParameterBlockThread::run()
{
  QString CurrentDateTime(""); // (QDateTime::currentDateTime()).toString(formatIt);
  static const QRegularExpression SC_RE("SC[0|5-9|A-E]:");
  static const QRegularExpression MAC_RE("[0-9|A-F]{12}");
  static const QRegularExpression DATA_RE("[0-9|A-F]{48}");
  static QRegularExpressionMatch match;
  static QString scInLine;
  static QString macInLine;
  static QString dataInLine;

  static const QString SCE("SCE:");
  static const QString SCD("SCD:");
  static const QString SCC("SCC:");
  static const QString SCB("SCB:");
  static const QString SCA("SCA:");
  static const QString SC9("SC9:");
  static const QString SC8("SC8:");
  static const QString SC7("SC7:");
  static const QString SC6("SC6:");
  static const QString SC5("SC5:");

  static const QString SC4("SC4:"); // For reading Coeffs (byte command 113)

  QString parseParameterBlockData;
  QString parseCoeffLineData;

  bool matchedSCLine = false;

  QMap<QString,int> scxToIntLookup;

  scxToIntLookup.insert(SCE,9);
  scxToIntLookup.insert(SCD,8);
  scxToIntLookup.insert(SCC,7);
  scxToIntLookup.insert(SCB,6);
  scxToIntLookup.insert(SCA,5);
  scxToIntLookup.insert(SC9,4);
  scxToIntLookup.insert(SC8,3);
  scxToIntLookup.insert(SC7,2);
  scxToIntLookup.insert(SC6,1);
  scxToIntLookup.insert(SC5,0);


  QMap<QString, QVector<QString>>::const_iterator qSVIter;

  // qDebug() << Q_FUNC_INFO << " running...";

  while (m_operational)
    {
      // mutex these operations
     //  qDebug() << Q_FUNC_INFO << " timer " << m_parameterBlockReadTimerRunning << " list " << m_otaParameterBlockDataToParseList.isEmpty();

      if ((m_parameterBlockReadTimerRunning == true) &&  (m_otaParameterBlockDataToParseList.isEmpty() == false))
		{
          matchedSCLine = false;
          m_mutex.lock();
          parseParameterBlockData = m_otaParameterBlockDataToParseList.takeFirst();
          m_mutex.unlock();

          // qDebug() << Q_FUNC_INFO << " got Parameter block dATA to PARSE... " << parseParameterBlockData;

          if ((parseParameterBlockData.length() > 60) && (parseParameterBlockData.at(0) == 'S') && (parseParameterBlockData.at(1) == 'C'))
          {
              QStringList lineOfPB = parseParameterBlockData.split('\t');
              if (lineOfPB.size() != 3)
              {
                  QString ErrorStr(Q_FUNC_INFO);
                  CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
                  ErrorStr += " ERROR: " + CurrentDateTime + " parameter block data line not recognized, parsing error : " + parseParameterBlockData;
                  emit publishParseParameterBlockThreadParseDataError(ErrorStr);
                  qDebug() << ErrorStr;
              }
              else
              {
                  // qDebug() << Q_FUNC_INFO << " INFO: &&&& &&&& &&&& found 3 valid strings in PB line ..."  << parseParameterBlockData;
                  scInLine = lineOfPB.at(0);
                  lineOfPB.removeAt(0);
                  // qDebug() << Q_FUNC_INFO << " SC => " << scInLine;

                  match = SC_RE.match(scInLine);
                  if (match.hasMatch())
                  {
                      macInLine = lineOfPB.at(0);
                      lineOfPB.removeAt(0);
                      //qDebug() << Q_FUNC_INFO << " INFO: &&&& &&&& &&&& SC has matched,  MAC => " << macInLine;

                      match = MAC_RE.match(macInLine);

                      if (match.hasMatch())
                      {
                          dataInLine = lineOfPB.at(0);
                          lineOfPB.removeAt(0);
                          // qDebug() << Q_FUNC_INFO << " INFO: &&&& &&&& &&&& SC and MAC has matched, Data => " << dataInLine;

                          match = DATA_RE.match(dataInLine);
                          if (match.hasMatch())
                          {
                              matchedSCLine = true;
                              //qDebug() << Q_FUNC_INFO << " INFO: &&&& &&&& &&&& matched SC, MAC, and data => " << dataInLine;
                              QString currentPBKey = macInLine + "_" + QString::number(m_parametersReadFromFlash) + "_" + m_currentOptimizerFamily;


                              // qDebug() << Q_FUNC_INFO << " INFO: &&&& &&&& &&&& PB KEY used is " << currentPBKey;

                              auto qSIIter2 = m_expectedPBInformationForMAC.find(currentPBKey);

                              if (qSIIter2 != m_expectedPBInformationForMAC.end())
                              {

                                  if (qSIIter2.value() == 0) /* Implies no parameter block data for this key has been stored yet. */
                                  {
                                      //  First time expected PB data has been seen for the MAC (...key...), create the Vector entry which will track the needed lines
                                      auto & pbsForOneKey = m_pbData[currentPBKey];
                                      pbsForOneKey.clear();
                                      pbsForOneKey.resize(10);
                                      pbsForOneKey[scxToIntLookup.value(scInLine)] = dataInLine;
                                      m_expectedPBInformationForMAC[currentPBKey] = 1;
                                      qDebug() << Q_FUNC_INFO << " m_expectedPBInformationForMAC for " << currentPBKey << " set to 1.";
                                      emit publishRequestRunningImageForMAC(macInLine);
                                  }
                                  else /* At least one parameter block data line for this key has been stored. */
                                  {
                                      qSVIter = m_pbData.find(currentPBKey);
                                      if (qSVIter != m_pbData.end()) /* A key for this MAC should be/ expected to be present */
                                      {
                                          auto & pbsForOneKey = m_pbData[currentPBKey];
                                          int scLineNumber = scxToIntLookup.value(scInLine);

                                          if (pbsForOneKey[scLineNumber] == "")
                                          {
                                              pbsForOneKey[scLineNumber] = dataInLine;
                                              m_pbData[currentPBKey] = pbsForOneKey;
                                              int numberOfSCXLinesObserved = qSIIter2.value();
                                              m_expectedPBInformationForMAC[currentPBKey] = numberOfSCXLinesObserved + 1;

                                              // qDebug() << Q_FUNC_INFO <<" lines for " << currentPBKey << " was " << numberOfSCXLinesObserved << "  now " << qSIIter2.value() << " by adding line " << scInLine;

                                              if (qSIIter2.value() == 10)
                                              {
                                                  qDebug() << Q_FUNC_INFO << " have received " << qSIIter2.value() << " lines or the complete parameter block for key: " << qSIIter2.key();
                                                  auto & pbsForOneKey = m_pbData[qSIIter2.key()];

                                                  QString data240 = pbsForOneKey.at(0) + pbsForOneKey.at(1) + pbsForOneKey.at(2) + pbsForOneKey.at(3) + pbsForOneKey.at(4) +
                                                          pbsForOneKey.at(5) + pbsForOneKey.at(6) + pbsForOneKey.at(7) + pbsForOneKey.at(8) + pbsForOneKey.at(9);

                                                  // qDebug() << Q_FUNC_INFO << "emiting parsedCompleteParameterBlockDataFor key " << qSIIter2.key() << " data: " << "data240 :" << data240;
                                                  emit parsedCompleteParameterBlockDataFor(qSIIter2.key(), data240);
                                                  qSIIter2 = m_expectedPBInformationForMAC.erase(qSIIter2);

                                                  if (m_expectedPBInformationForMAC.size() == 0)
                                                  {
                                                      qDebug() << Q_FUNC_INFO << " INFO: all requested PB info obtained... ";
                                                      m_newReadOfParameterBlock = false;
                                                      m_parameterBlockReadTimerRunning = false;
                                                      emit enableReadParameterBlocks(true);
                                                      emit publishEndDeviceParameterBlockReadSuccessful();
                                                      emit publishAllRequestedParameterBlocksRead();
                                                      m_expectedPBInformationForMAC.clear();

                                                      // qDebug() << Q_FUNC_INFO << " INFO: Just Published Read PB Success!!!!   CurrentKey:" << currentPBKey;
                                                  }
                                                  else
                                                  {
                                                      qDebug() << Q_FUNC_INFO << " INFO: still need PB info for " << m_expectedPBInformationForMAC.size() << " more MACs...";
                                                  }
                                              }
                                              else
                                              {
                                                  // qDebug() << Q_FUNC_INFO << " have received " << qSIIter2.value() << " lines of the expected ten PB lines for key: " << qSIIter2.key();
                                              }
                                          }
                                          else if (pbsForOneKey[scLineNumber] != dataInLine)
                                          {
                                              QString ErrorStr(Q_FUNC_INFO);
                                              CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
                                              ErrorStr += " ERROR: " + CurrentDateTime + " data for MAC " + macInLine + ", " + scInLine + " just received " + dataInLine + " does not match previously seen " + pbsForOneKey[scLineNumber];
                                              qDebug() << ErrorStr;
                                              emit publishParseParameterBlockThreadError(ErrorStr);
                                          }
                                          else
                                          {
                                              // qDebug() << Q_FUNC_INFO << "INFO : data for MAC " << macInLine << "," << scInLine << " just recevied matches previous seen data.";
                                          }
                                      }
                                      else
                                      {
                                          QString ErrorStr(Q_FUNC_INFO);
                                          CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
                                          ErrorStr += " ERROR: " + CurrentDateTime + " No key entry for Expected MAC " + macInLine + " in pbdata data structure.";
                                          qDebug() << ErrorStr;
                                          emit publishParseParameterBlockThreadError(ErrorStr);
                                      }
                                  }
                              }
                              else
                              {
                                  if (m_currentlyReadingParameterBlocks == true)
                                  {
                                      QString ErrorStr(Q_FUNC_INFO);
                                      CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
                                      ErrorStr += " ERROR: " + CurrentDateTime + " Received Unexpected Parameter Block line for " + currentPBKey;
                                      qDebug() << ErrorStr;
                                      emit publishParseParameterBlockThreadError(ErrorStr);
                                  }
                              }
                          }
                          else
                          {
                              emit publishParseParameterBlockThreadParseDataError(parseParameterBlockData);
                          }
                      }
                      else
                      {
                          emit publishParseParameterBlockThreadParseMACError(parseParameterBlockData);
                      }
                  }
                  else
                  {
                      emit publishParseParameterBlockThreadParseSCXError(parseParameterBlockData);
                  }

                  if (matchedSCLine == true)
                  {
                      emit  validParameterBlockSCXLine(parseParameterBlockData);
                  }
              }
          }
          else  // ACTUALLY THIS IS ERROR
          {
              QString ErrorStr(Q_FUNC_INFO);
              CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
              ErrorStr += " ERROR: " + CurrentDateTime + " parameter block data line not recognized, parsing error : " + parseParameterBlockData;
              emit publishParseParameterBlockThreadParseDataError(ErrorStr);
              qDebug() << ErrorStr;
          }
      }
      else if ((m_parameterBlockReadTimerRunning == false) &&  (m_otaParameterBlockDataToParseList.isEmpty() == false))
      {
          matchedSCLine = false;
          m_mutex.lock();
          parseParameterBlockData = m_otaParameterBlockDataToParseList.takeFirst();
          m_mutex.unlock();

          if (m_parametersAutoRead == true)
          {

              qDebug() << Q_FUNC_INFO << " got possible AutoRead DATA to PARSE..." << parseParameterBlockData;

              if ((parseParameterBlockData.length() > 60) && (parseParameterBlockData.at(0) == 'S') && (parseParameterBlockData.at(1) == 'C') && (parseParameterBlockData.at(2) == 'E'))
              {
                  QStringList lineOfPB = parseParameterBlockData.split('\t');
                  if (lineOfPB.size() != 3)
                  {
                      QString ErrorStr(Q_FUNC_INFO);
                      CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
                      ErrorStr += " ERROR: " + CurrentDateTime + " parameter block data line not recognized, parsing error : " + parseParameterBlockData;
                      emit publishParseParameterBlockThreadParseDataError(ErrorStr);
                      qDebug() << ErrorStr;
                  }
                  else
                  {
                      macInLine = lineOfPB.at(1);
                      qDebug() << Q_FUNC_INFO << " INFO: emit signal publishPossibleAutoReadOfPB(" << macInLine << ")";
                      emit publishPossibleAutoReadOfPB(macInLine);
                  }
              }
          }
          else if (parseParameterBlockData.at(2) != '5')
          {
              QString ErrorStr(Q_FUNC_INFO);
              CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
              ErrorStr += " ERROR: " + CurrentDateTime + " parameter block data line not recognized, parsing error : " + parseParameterBlockData;
              emit publishParseParameterBlockThreadParseDataError(ErrorStr);
              qDebug() << ErrorStr;
          }
      }
      else if ((!m_otaParameterBlockCoeffLineToParseList.isEmpty()) && (m_parameterBlockReadTimerRunning == false) &&  (m_otaParameterBlockDataToParseList.isEmpty() == true))
      {
          m_mutex.lock();
          parseCoeffLineData = m_otaParameterBlockCoeffLineToParseList.takeFirst();
          m_mutex.unlock();

          qDebug() << Q_FUNC_INFO << " INFO: got Parameter coeff dATA to PARSE... " << parseCoeffLineData;

          if ((parseCoeffLineData.length() > 60) && (parseCoeffLineData.at(0) == 'S') && (parseCoeffLineData.at(1) == 'C') && (parseCoeffLineData.at(2) == '4'))
          {
              QStringList lineOfPB = parseCoeffLineData.split('\t');
              if (lineOfPB.size() != 3)
              {
                  QString ErrorStr(Q_FUNC_INFO);
                  CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
                  ErrorStr += " ERROR: " + CurrentDateTime + " parameter coeff line  not recognized, parsing error : " + parseCoeffLineData;
                  emit publishParseParameterBlockThreadParseDataError(ErrorStr);
                  qDebug() << ErrorStr;
              }
              else
              {
                  // qDebug() << Q_FUNC_INFO << " INFO: &&&& &&&& &&&& found 3 valid strings in PB line ..."  << parseParameterBlockData;
                  scInLine = lineOfPB.at(0);
                  lineOfPB.removeAt(0);

                  macInLine = lineOfPB.at(0);
                  lineOfPB.removeAt(0);
                  qDebug() << Q_FUNC_INFO << " INFO: &&&& &&&& &&&& SC has matched for COEFF line,  MAC => " << macInLine;

                  match = MAC_RE.match(macInLine);

                  if (match.hasMatch())
                  {
                      dataInLine = lineOfPB.at(0);
                      lineOfPB.removeAt(0);
                      // qDebug() << Q_FUNC_INFO << " INFO: &&&& &&&& &&&& SC and MAC has matched, Data => " << dataInLine;

                      match = DATA_RE.match(dataInLine);
                      if (match.hasMatch())
                      {
                          qDebug() << Q_FUNC_INFO << " emiting parsedCoeffLineFor:" << macInLine << " " << dataInLine;
                          emit parsedCoeffLineFor(macInLine, dataInLine);
                      }
                      else
                      {
                          QString errString(Q_FUNC_INFO);
                          errString += " ERROR: did not match data:" +  parseCoeffLineData;
                          emit publishParseParameterBlockThreadParseDataError(errString);
                          qDebug() << errString;
                      }
                  }
                  else
                  {
                      QString errString(Q_FUNC_INFO);
                      errString += " ERROR: did not match mac" + parseCoeffLineData;
                      emit publishParseParameterBlockThreadParseMACError(errString);
                      qDebug() << errString;
                  }
              }
          } /* END if ((parseCoeffLineData.length() > 60) && (parseCoeffLineData.at(0) == 'S') && (parseCoeffLineData.at(1) == 'C') && (parseCoeffLineData.at(2) == '4')) */
          else
          {
              QString errString(Q_FUNC_INFO);
              errString +=  " ERROR: did not match " + parseCoeffLineData + " length:" + QString::number(parseCoeffLineData.length());
              emit publishParseParameterBlockThreadParseSCXError(errString);
              qDebug() << errString;
          }
      } /* END else if ((!m_otaParameterBlockCoeffLineToParseList.isEmpty()) && (m_parameterBlockReadTimerRunning == false) &&  (m_otaParameterBlockDataToParseList.isEmpty() == true)) */
	  else
		{
          QThread::msleep(80);

          // If timer expired, check to see if all expected parameter block data has been received
          if ((m_parameterBlockReadTimerRunning == false) && ( m_newReadOfParameterBlock == true ))
          {
              qDebug() << Q_FUNC_INFO << " INFO: if timer not running and a new PB read happened ...";

              bool allPBsCompletelyRead = true;
              m_newReadOfParameterBlock = false;

              for (auto it = m_expectedPBInformationForMAC.begin(); it != m_expectedPBInformationForMAC.end(); )
              {
                  qDebug() << Q_FUNC_INFO << " $$$$$$$ $$$$$$$ checkng if entire PB has been read for key: " << it.key();
                  if (it.value() == 10)
                  {
                      qDebug() << Q_FUNC_INFO << " $$$$$$$ $$$$$$$ $$$$$$$ Entire PB has been read for MAC: " << it.key();
                      auto & pbsForOneKey = m_pbData[it.key()];

                      QString data240 = pbsForOneKey.at(0) + pbsForOneKey.at(1) + pbsForOneKey.at(2) + pbsForOneKey.at(3) + pbsForOneKey.at(4) +
                              pbsForOneKey.at(5) + pbsForOneKey.at(6) + pbsForOneKey.at(7) + pbsForOneKey.at(8) + pbsForOneKey.at(9);

                      qDebug() << Q_FUNC_INFO << "emiting parsedCompleteParameterBlockDataFor key " << it.key() << " data: " << "data240 :" << data240;
                      emit parsedCompleteParameterBlockDataFor(it.key(), data240);
                      // emit enableReadParameterBlocks(true);
                      it = m_expectedPBInformationForMAC.erase(it);
                  }
                  else
                  {
                      qDebug() << Q_FUNC_INFO << " NEED to RESTART TIMER And reissue PB read command... it.key() == " << it.key() << " it.value(): " << it.value();
                      auto & pbsForOneKey = m_pbData[it.key()];
                      allPBsCompletelyRead = false;
                      for (quint8 num = 9; num > 0; num--)
                      {
                          if (pbsForOneKey[num] == "")
                          {
                              QString errPBReadString(Q_FUNC_INFO);
                              errPBReadString += " ERROR: 'First' missing line number for key: " + it.key() + " is " + QString::number(num);
                              errPBReadString += "\n\tcommand that needs to be sent is s mMAC 57.32 b" + QString::number(10-num);
                              emit publishParseParameterBlockThreadParseDataError(errPBReadString);
                              qDebug() << errPBReadString;
                              emit resendParameterBlockCommand(macInLine,m_parametersReadFromFlash,10 - num);
                              break;
                          }
                      }
                      it++;
                  }
              } /* END for (auto it = m_expectedPBInformationForMAC.begin(); it != m_expectedPBInformationForMAC.end(); ) */
              /* Done here in case broadcase read was requested, ALL pbs must respond.  LBC Need to determine a better way, not to "hang up" read button if not all responded. */
              if (allPBsCompletelyRead == true)
              {
                  // qDebug() << Q_FUNC_INFO << " INFO: &&&& &&&& &&&& if timer not running and a new PB read happened AND ALL expected happened...";
                  emit enableReadParameterBlocks(true);
                  emit publishAllRequestedParameterBlocksRead();
              }
              else
              {
                  QString errString(Q_FUNC_INFO);
                  errString += " ERROR: &&&& &&&& &&&& if timer not running and a new PB read happened AND ALL expected happened...";
                  emit publishParseParameterBlockThreadError(errString);
                  qDebug() << errString;
              }
          } /* END if ((m_parameterBlockReadTimerRunning == false) && ( m_newReadOfParameterBlock == true )) */
      } /* END else */
  } /*END while (m_operational) */

  qDebug() << Q_FUNC_INFO << " INFO: exiting ...";

  emit this->parseParameterBlockThreadExit();
  
}

void ParseParameterBlockThread::setParseParameterBlockThreadLogging( bool logging )
{
    m_logData = logging;
}

void ParseParameterBlockThread::handleOptimizerFamilyChanged( const QString & s)
{
    if (s.length() > 2)
    {
        m_currentOptimizerFamily = s;
        qDebug() << Q_FUNC_INFO << " Family changed: to " << s << Qt::endl;
    }
}

void ParseParameterBlockThread::setParameterBlockReadFrom(const bool s)
{
    m_parametersReadFromFlash = s;
    // qDebug() << Q_FUNC_INFO << " Read from: " << s << Qt::endl;
}


void ParseParameterBlockThread::handleParametersReadFromChange( const bool s)
{
    qDebug() << Q_FUNC_INFO << " reading from flash:" << s;
    m_parametersReadFromFlash = s;
}

void ParseParameterBlockThread::handleStartParameterBlockRead( void )
{
    qDebug() << Q_FUNC_INFO << " new read of parameter block is starting ...";
    m_newReadOfParameterBlock = true;
}



void ParseParameterBlockThread::handleNewMACDiscovered(const QString & s)
{
    // qDebug() << Q_FUNC_INFO << " possible new MAC to be aware of: " << s;
    QMap<QString, int>::const_iterator it;

    it = m_macs.find(s);
    if (it == m_macs.end())
    {
        // qDebug() << Q_FUNC_INFO << " mac: " << s << " is a New Mac";
        m_macs.insert(s,0);

        /*
        for ( it = m_macs.begin(); it != m_macs.end(); ++it)
        {
            qDebug() << Q_FUNC_INFO << " m_macs key: " << it.key() << " value: " << it.value();
        }
        */
    }
    else
    {
        qDebug() << Q_FUNC_INFO << " INFO: mac: " << " is NOT a New Mac";
    }

}

void ParseParameterBlockThread::handleRequestAllEndDeviceParameterBlocks( const QString s )
{
   qDebug() << Q_FUNC_INFO << " INFO: expecting to read parameter blocks of all end devices: " << s;
   QString pbKey;
   QStringList theMacs;
   theMacs = s.split(",");
   QMap<QString, int>::const_iterator it;
   QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

   for (int i = 0; i < theMacs.size(); i++)
   {
       pbKey = theMacs.at(i) + "_" + QString::number(m_parametersReadFromFlash) + "_" + m_currentOptimizerFamily;
       qDebug() << Q_FUNC_INFO << " INFO: key to use is " << pbKey;


       it = m_expectedPBInformationForMAC.find(pbKey);
       if (it == m_expectedPBInformationForMAC.end())
       {
           m_expectedPBInformationForMAC.insert(pbKey,0);
       }
       else
       {
           QString ErrorStr(Q_FUNC_INFO);

           ErrorStr += " ERROR: " + CurrentDateTime + " already watching for parameter block information for mac: ";
           ErrorStr += pbKey;
           qDebug() << ErrorStr;
           emit publishParseParameterBlockThreadError(ErrorStr);
       }
   }
   qDebug() << Q_FUNC_INFO << " INFO: size of m_expectedPBInformation is " << m_expectedPBInformationForMAC.size();

   for (it = m_expectedPBInformationForMAC.begin(); it != m_expectedPBInformationForMAC.end(); ++it)
   {
       qDebug() << Q_FUNC_INFO << " INFO: " << CurrentDateTime << " pb information for mac " << it.key() << " expected: " << it.value();
   }
}

void ParseParameterBlockThread::handleRequestMACParameterBlock(const QString & s)
{
    // qDebug() << Q_FUNC_INFO << " INFO: expecting to read parameter block info for mac: " << s;
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
    QString pbKey;

    pbKey = s + "_" + QString::number(m_parametersReadFromFlash) + "_" + m_currentOptimizerFamily;

    // qDebug() << Q_FUNC_INFO << " INFO: key to use is " << pbKey;

    QMap<QString, int>::const_iterator it;

    it = m_expectedPBInformationForMAC.find(pbKey);
    if (it == m_expectedPBInformationForMAC.end())
    {
        m_expectedPBInformationForMAC.insert(pbKey,0);
    }
    else
    {
        QString ErrorStr(Q_FUNC_INFO);

        ErrorStr += " ERROR: " + CurrentDateTime + " already watching for parameter block information for mac: ";
        ErrorStr += pbKey;
        qDebug() << ErrorStr;

        emit publishParseParameterBlockThreadError(ErrorStr);
    }

    qDebug() << Q_FUNC_INFO << " INFO: size of m_expectedPBInformation is " << m_expectedPBInformationForMAC.size();

    for (it = m_expectedPBInformationForMAC.begin(); it != m_expectedPBInformationForMAC.end(); ++it)
    {
        qDebug() << Q_FUNC_INFO << " INFO: " << CurrentDateTime << " pb information for mac " << it.key() << " expected: " << it.value();
    }
}
