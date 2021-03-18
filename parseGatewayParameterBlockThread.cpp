/****************************************************************************
**
**
****************************************************************************/
#include <QTime>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>
#include <QVector>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

#include "parseGatewayParameterBlockThread.h"
#include "amptgui_x_status.h"
#include "amptgui_x_utilities.h"
#include "gatewayParameterBlockKeyNames.h"

static QString formatIt("yyyy_MM_dd_HH_mm_ss");
static QString gatewayZCount;
static QString gatewayCmdCount;
static QString gatewayFWVer;
static QString gatewayVersion;
static QString gatewayDataRate;
static QString gatewayFrequency;
static QString gatewayMicroSecondsInTick;
static QString gatewayChannel;
static QString gatewayNetworkSize;
static QString gatewayBunchSize;
static QString gatewayUTC;
static QString gatewayLongPackets;
static QString gatewayRadioMode;
static QString gatewayShift;
static QString gatewayPower;
static QString gatewayMAC;
static QString gatewayHop;
static QString gatewayGWAddr;
static QString gatewayEDAddr;
static QString gatewaySyncword;

void ParseGatewayParameterBlockThread::constructAndPublishGatewayPBList()
{
    QString gatewayPBList;
    QTextStream gatewayPBStream(&gatewayPBList);

    // qDebug() << Q_FUNC_INFO << " gatewayVersionKey: " << gatewayVersionKey;

    gatewayPBList += gatewayVersionKey + gatewayKeyValueSeparator + gatewayVersion + " " + gatewayDataRateKey + gatewayKeyValueSeparator + gatewayDataRate + " "
                    + gatewayFrequencyKey + gatewayKeyValueSeparator + gatewayFrequency + " " + gatewayMicroSecondsInTickKey + gatewayKeyValueSeparator + gatewayMicroSecondsInTick + " "
                    + gatewayChannelKey + gatewayKeyValueSeparator + gatewayChannel + " " + gatewayNetworkSizeKey + gatewayKeyValueSeparator + gatewayNetworkSize + " "
                    + gatewayBunchSizeKey + gatewayKeyValueSeparator + gatewayBunchSize + " " + gatewayUTCKey + gatewayKeyValueSeparator + gatewayUTC + " "
                    + gatewayLongPacketsKey + gatewayKeyValueSeparator + gatewayLongPackets + " "
                    + gatewayRadioModeKey + gatewayKeyValueSeparator + gatewayRadioMode + " "
                    + gatewayShiftKey + gatewayKeyValueSeparator + gatewayShift + " "
                    + gatewayPowerKey + gatewayKeyValueSeparator + gatewayPower + " " + gatewayMACKey + gatewayKeyValueSeparator + gatewayMAC + " "
                    + gatewayHopKey + gatewayKeyValueSeparator + gatewayHop + " " + gatewayGWAddrKey + gatewayKeyValueSeparator + gatewayGWAddr + " "
                    + gatewayEDAddrKey + gatewayKeyValueSeparator + gatewayEDAddr + " " + gatewaySyncwordKey + gatewayKeyValueSeparator + gatewaySyncword + " "
                    + gatewayZCountKey + gatewayKeyValueSeparator + gatewayZCount + " " + gatewayCmdCountKey + gatewayKeyValueSeparator + gatewayCmdCount + " "
                    + gatewayFWVersionKey + gatewayKeyValueSeparator + gatewayFWVer;

    // qDebug() << Q_FUNC_INFO << " gateway Paramter Block Info length: " << gatewayPBList.length() << " in paired form: " << gatewayPBList;
    emit parsedGatewayParameterBlockInformation(gatewayPBList);

 }

ParseGatewayParameterBlockThread::ParseGatewayParameterBlockThread(QObject *parent) :
    QThread(parent)
{
    m_operational = true; 
}

ParseGatewayParameterBlockThread::~ParseGatewayParameterBlockThread()
{
    m_mutex.lock();
    m_operational = false;
    m_cond.wakeOne();
    m_mutex.unlock();
    wait();
}

void ParseGatewayParameterBlockThread::stopParseGatewayParameterBlockThreadOperation( void )
{
    m_operational = false;
}

void ParseGatewayParameterBlockThread::parseGatewayParameterBlockData(const QString & data)
{

    // qDebug() << Q_FUNC_INFO << " data to parse: => " << data;

    const QMutexLocker locker(&m_mutex);
    m_gatewayParameterBlockDataToParseList.append(data);

}

void ParseGatewayParameterBlockThread::startParseGatewayParameterBlockThreadInterface(int waitTimeout, const bool logging)
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

bool ParseGatewayParameterBlockThread::obtainZCountLineData(const QString &s)
{
    bool retValue = true;
    QStringList zCountLineSplit = s.split('\t');
    QString ErrorStr(Q_FUNC_INFO);
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

    // qDebug() << Q_FUNC_INFO << s << " number of split elements:" << zCountLineSplit.size();

    if (zCountLineSplit.size() == 5)
    {
        int index = -1;
        for (int i = 0; i < zCountLineSplit.size() && retValue == true; i++)
        {
            // qDebug() << Q_FUNC_INFO << " i =>" << i << " value:" << zCountLineSplit.at(i);
            if (i == 1) // zCount
            {
                index = (zCountLineSplit.at(i)).indexOf('=');
                if (index > 0)
                {
                    gatewayZCount = ((zCountLineSplit.at(i)).mid(index+1)).trimmed();
                    // qDebug() << Q_FUNC_INFO << " gatewayZCount:" << gatewayZCount;
                }
                else
                {
                    ErrorStr += " ERROR: " + CurrentDateTime + " expected format of gatewayZCount not found, line:" + zCountLineSplit.at(i);
                    qDebug() << ErrorStr;
                    emit publishParseGatewayParameterBlockThreadError(ErrorStr);
                    retValue = false;
                }
            }
            else if (i == 3) // comCount
            {
                index = (zCountLineSplit.at(i)).indexOf('=');
                if (index > 0)
                {
                    gatewayCmdCount = ((zCountLineSplit.at(i)).mid(index+1)).trimmed();
                    // qDebug() << Q_FUNC_INFO << " gatewayCmdCount:" << gatewayCmdCount;
                }
                else
                {
                    ErrorStr += " ERROR: " + CurrentDateTime + " expected format of gatewayCmdCount not found, line:" + zCountLineSplit.at(i);
                    qDebug() << ErrorStr;
                    emit publishParseGatewayParameterBlockThreadError(ErrorStr);
                    retValue = false;
                }
            }
            else if (i == 4) // fw Version
            {
                index = (zCountLineSplit.at(i)).indexOf('=');
                if (index > 0)
                {
                    gatewayFWVer = ((zCountLineSplit.at(i)).mid(index+1)).trimmed();
                    // qDebug() << Q_FUNC_INFO << " gatewayFWVer:" << gatewayFWVer;
                }
                else
                {
                    ErrorStr += " ERROR: " + CurrentDateTime + " expected format of gatewayFWVer not found, line:" + zCountLineSplit.at(i);
                    qDebug() << ErrorStr;
                    emit publishParseGatewayParameterBlockThreadError(ErrorStr);
                    retValue = false;
                }
            }
        }
    }
    else
    {
        ErrorStr += " ERROR: " + CurrentDateTime + " expected format of gateway parameter line not found, line:" + s;
        qDebug() << ErrorStr;
        emit publishParseGatewayParameterBlockThreadError(ErrorStr);
        retValue = false;
    }

    return retValue;
}

bool ParseGatewayParameterBlockThread::obtainVersionLineData(const QString &s)
{
    int index = s.indexOf('.');
    bool retValue = false;

    if (( index > 0) && (s.length() > index) && (s.length() > 28))
    {
        // qDebug() << Q_FUNC_INFO << " index is at " << index << " length: " << s.length() << Qt::endl;
        gatewayVersion = (s.mid(index+1)).trimmed();
        // qDebug() << Q_FUNC_INFO << " version:" << gatewayVersion;
        retValue = true;
    }
    return retValue;
}

bool ParseGatewayParameterBlockThread::obtainDataRateLineData(const QString &s)
{
    // \nDatarate:12001 Freq2410001 Tick (mks) 500 Chan 2 # SPTs 8 bunch size 16
    bool retValue = false;
    QString temp(s);
    int index1 = s.indexOf(':');
    int index2 = s.indexOf(' ');

    if ((index1 != -1) && (index2 != -1))
    {
        gatewayDataRate = (s.mid(index1 + 1, (index2 - index1))).trimmed();
        //qDebug() << Q_FUNC_INFO << " dataRate: " << gatewayDataRate;
        temp = temp.mid(index2 + 1);
        // qDebug() << Q_FUNC_INFO << " remaining " << temp << Qt::endl;

        index1 = temp.indexOf(' ');
        if ((temp.length() > 14) && (index1 == 11))
        {
            gatewayFrequency = (temp.mid(4, index1 - 4)).trimmed();
            // qDebug() << Q_FUNC_INFO << " frequency: " << gatewayFrequency;
            temp = temp.mid(index1 + 1);

            // qDebug() << Q_FUNC_INFO << " remaining " << temp << Qt::endl;
            index1 = temp.indexOf(')');
            if ((index1 != -1) && (temp.length() > (index1 + 2))) // Notice skip over space after close paren
            {
                temp = temp.mid(index1 + 2);
                index1 = temp.indexOf(' ');
                if (index1 > 0)
                {
                    gatewayMicroSecondsInTick = (temp.mid(0,index1)).trimmed();
                    // qDebug() << Q_FUNC_INFO << "microseconds in tick: " << gatewayMicroSecondsInTick;

                    if (index1 > 2)
                    {
                        temp = temp.mid(index1 + 1);

                        // qDebug() << Q_FUNC_INFO << " remaining " << temp << Qt::endl;
                        if (temp.length() > 10 && ((index1 = temp.indexOf(' ')) != -1))
                        {
                            temp = temp.mid(index1 + 1);
                            if ((index1 = temp.indexOf(' ')) != -1)
                            {
                                gatewayChannel = (temp.mid(0,index1)).trimmed();
                                //qDebug() << Q_FUNC_INFO << " channel: " << gatewayChannel;

                                temp = temp.mid(index1 + 1);
                                // qDebug() << Q_FUNC_INFO << " remaining " << temp << Qt::endl;

                                index1 = temp.indexOf('s');
                                if ((index1 > 0) && (temp.length() > 10))
                                {
                                    temp = temp.mid(index1 + 2); // Notice skip over blank also
                                    if (((index1 = temp.indexOf(' ')) != -1) && (temp.length() > 10))
                                    {
                                        gatewayNetworkSize = (temp.mid(0,index1)).trimmed();
                                        // qDebug() << Q_FUNC_INFO << " network size: " << gatewayNetworkSize;

                                        temp = temp.mid(index1 + 1);
                                        // qDebug() << Q_FUNC_INFO << " remaining: " << temp;

                                        if ((index1 = temp.lastIndexOf(' ')) != -1)
                                        {
                                            gatewayBunchSize = (temp.mid(index1 + 1)).trimmed();
                                            // qDebug() << Q_FUNC_INFO << " bunch size: " << gatewayBunchSize << Qt::endl;
                                            retValue = true;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

            }
        }
    }
    else
    {
        QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
        QString errString(Q_FUNC_INFO);
        errString += " ERROR: " + CurrentDateTime + " failed to match gateway PB information, line: " + s;
        publishParseGatewayParameterBlockThreadError(errString);
        qDebug() << errString;
    }

    return retValue;
}

bool ParseGatewayParameterBlockThread::obtainUTCLineData(const QString &s)
{
    bool retValue = false;
    QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
    int index1 = 0;
    int index2 = 0;
    QString temp;

    // qDebug() << Q_FUNC_INFO << " line: " << s << Qt::endl;
    // \nUTC:0 963 Normal   long packets  temp 3033\t shift -30 ADCs  TRUE  Power ED
    // find UTC: (find :, then find ' ', value between
    // find long packets // is long packets in string (yes), else no
    // find shift, find first blank, find next blank, value between
    // find Power. value is trimmed from index + 1 to end of string

    gatewayLongPackets = "No";

    index1 = s.indexOf(':');
    index2 = s.indexOf(' ');
    int numberFound = 0;
    QString nextValue("");

    if ((index1 >0) && (index2 >= index1 + 1))
    {
        gatewayUTC = s.mid(index1+1,index2 - index1 - 1);
        numberFound++;
        // qDebug() << Q_FUNC_INFO << " found UTC";

        temp = s.mid(index2 + 1);
        QStringList restOfUTCLine = s.split(' ');

        for (int i = 0; i < restOfUTCLine.size(); i++)
        {
            // qDebug() << Q_FUNC_INFO << " element is " << restOfUTCLine.at(i);
            if (restOfUTCLine.at(i) == "long")
            {
                nextValue = "packets";
            }
            else if ((nextValue == "packets") && (restOfUTCLine.at(i) == nextValue))
            {
                // qDebug() << Q_FUNC_INFO << " found long packets";
                gatewayLongPackets = "Yes";\
                numberFound++;
                nextValue = "";

            }
            else if (restOfUTCLine.at(i) == "Normal")
            {
                // qDebug() << Q_FUNC_INFO << " FOUND Normal";
                gatewayRadioMode = "Normal";
            }
            else if (restOfUTCLine.at(i) == "Listeni")
            {
                // qDebug() << Q_FUNC_INFO << " FOUND Listeni";
                gatewayRadioMode = "Listening";
            }
            else if (restOfUTCLine.at(i) == "shift")
            {
                nextValue = "shift";
            }
            else if (nextValue == "shift")
            {
                // qDebug() << Q_FUNC_INFO << " found shift.";
                gatewayShift = restOfUTCLine.at(i);
                nextValue = "";
                numberFound ++;
            }
            else if (restOfUTCLine.at(i) == "Power")
            {
                nextValue = "Power";
            }
            else if (nextValue == "Power")
            {
                // qDebug() << Q_FUNC_INFO << " found Power";
                gatewayPower = restOfUTCLine.at(i);
                nextValue = "";
                numberFound++;
            }
            else if (nextValue != "")
            {
                QString errString(Q_FUNC_INFO);
                errString += " ERROR: " + CurrentDateTime + " expected to find " + nextValue + " but failed to do so.";
                emit publishParseGatewayParameterBlockThreadError(errString);
                qDebug() << errString;
                break;

            }
        }
        if (((gatewayLongPackets == "Yes") && (numberFound == 4)) || ((gatewayLongPackets == "No") && (numberFound == 3)))
        {
            // qDebug() << Q_FUNC_INFO << " successfully pa\nSync Word: F0F0rsed line " << s;
            retValue = true;
        }
        else
        {
            QString errString(Q_FUNC_INFO);
            errString += " ERROR: " + CurrentDateTime + " (1) failed to parse line " + s + " expected 3 or 4 (if long packets found) elements, found " + QString::number(numberFound);
            emit publishParseGatewayParameterBlockThreadError(errString);
            qDebug() << errString;
        }
    }
    else
    {
        QString errString(Q_FUNC_INFO);
        errString += " ERROR: " + CurrentDateTime + " (2) failed to parse line " + s + " expected 3 or 4 (if long packets found) elements, found " + QString::number(numberFound);
        emit publishParseGatewayParameterBlockThreadError(errString);
        qDebug() << errString;
    }

    return retValue;
}

bool ParseGatewayParameterBlockThread::obtainMACLineData(const QString &s)
{
    bool retValue = false;
    int numberFound = 0;
    QString nextValue("");

    // qDebug() << Q_FUNC_INFO << " line: " << s << Qt::endl;

    // \nMAC 884A800006EA no hop  FEC=0GwAddr 1\tEdAddr 2
    QStringList macLineSplit = s.split(' ');\

    for (int i = 0; i < macLineSplit.size(); i++)
    {
        // qDebug() << Q_FUNC_INFO << " element is " << macLineSplit.at(i);
        // qDebug() << Q_FUNC_INFO << " nextValue: " << nextValue;

        if (macLineSplit.at(i) == "\nMAC")\
        {
            nextValue = "MAC";
        }
        else if (nextValue == "MAC")
        {
            gatewayMAC = macLineSplit.at(i);
            nextValue = "";
            numberFound++;
        }
        else if (macLineSplit.at(i) == "no")
        {
            nextValue = "hop";
        }
        else if (nextValue == "hop")
        {
            gatewayHop = "0";
            nextValue = "";
            numberFound++;
        }
        else if (macLineSplit.at(i) == "hopping")
        {
            gatewayHop = "1";
            numberFound++;
        }
        else if (macLineSplit.at(i) == "FEC=0GwAddr")
        {
            nextValue = "GWAddr";
        }
        else if (nextValue == "GWAddr")
        {
            QStringList justGWAddr( (macLineSplit.at(i)).split('\t') );
            if (justGWAddr.size() == 2)
            {
                gatewayGWAddr = justGWAddr.at(0);
                nextValue = "";
                numberFound++;
            }
            else
            {
                QString errString(Q_FUNC_INFO);
                QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
                errString += " ERROR: " + CurrentDateTime + " parsing GWAddr token: " + macLineSplit.at(i);
                emit publishParseGatewayParameterBlockThreadError(errString);
                qDebug() << errString;

                nextValue = "";
                break;
            }
        }
        else if (i == (macLineSplit.size() - 1))
        {
            gatewayEDAddr = macLineSplit.at(i);
            retValue = true;
        }
    }
    return retValue;
}

bool ParseGatewayParameterBlockThread::obtainSyncwordLineData(const QString &s)
{
    bool retValue = false;
    // qDebug() << Q_FUNC_INFO << " line: " << s << Qt::endl;
    // \nSync Word: F0F0
    QStringList syncSplitLine(s.split(" "));
    QString nextValue("");
    for (int i = 0; i < syncSplitLine.size(); i++)
    {
        if (syncSplitLine.at(i) == "\nSync")
        {
            nextValue = "Word:";
        }
        else if (syncSplitLine.at(i) == nextValue)
        {
            nextValue = "Sync Word:";
        }
        else if (nextValue == "Sync Word:")
        {
            gatewaySyncword = syncSplitLine.at(i);
            nextValue = "";
            retValue = true;
            //qDebug() << Q_FUNC_INFO << " successfully parsed Sync Word line: " << s;
        }
        else
        {
            QString errString(Q_FUNC_INFO);
            QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
            errString += " ERROR: " + CurrentDateTime + " failed to parse Sync Word line: " + s;
            emit publishParseGatewayParameterBlockThreadError(errString);
            qDebug() << errString;
        }
    }

    return retValue;
}

void ParseGatewayParameterBlockThread::run()
{
  // qDebug() << Q_FUNC_INFO << " begin ";

  static const QRegularExpression ZCount_RE("\nAuxilary GW information.");
  static const QRegularExpression Version_RE("\nAMPT BOU Radio Gateway ver. ");
  static const QRegularExpression DataRate_RE("\nDatarate:");
  static const QRegularExpression UTC_RE("\nUTC:" );
  static const QRegularExpression MAC_RE("\nMAC");
  static const QRegularExpression Sync_RE("\nSync Word:");
  static QRegularExpressionMatch match;

  QVector<QRegularExpression> orderOfGatewayOTALines;

  orderOfGatewayOTALines.append(ZCount_RE);
  orderOfGatewayOTALines.append(Version_RE);
  orderOfGatewayOTALines.append(DataRate_RE);
  orderOfGatewayOTALines.append(UTC_RE);
  orderOfGatewayOTALines.append(MAC_RE);
  orderOfGatewayOTALines.append(Sync_RE);

  /* NOTE These indexes must match the order in which their associated named regular expressions are appended into orderOfGatewayOTALines */
  const int ZCount_RE_INDEX = 0;
  const int Version_RE_INDEX = 1;
  const int DataRate_RW_INDEX = 2;
  const int UTC_RE_INDEX = 3;
  const int MAC_RE_INDEX = 4;
  const int Sync_RE_INDEX = 5;

  bool successfullyParsed = false;


  while (m_operational) 
    {
      // qDebug() << Q_FUNC_INFO << " running ... ";
      // mutex these operations
      QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);

      if (m_gatewayParameterBlockDataToParseList.empty() == false)

        {
          int numberOfMatches = 1;  // Make assumption that GW Parameters returning from "i" command, not "?" command.
          successfullyParsed = false;
          bool continueMatchingLines = true;
          // qDebug() << Q_FUNC_INFO << " some gw info to parse ... ";

          QString parseGatewayData = m_gatewayParameterBlockDataToParseList.takeFirst();

          /*
           *  "i\r\n\r\n\r\nAMPT BOU Radio Gateway ver. F\r\nDatarate:12001 Freq2410001 Tick (mks) 500 Chan 2 # SPTs 8 bunch size 16\r\nUTC:0 963 Normal   long packets  temp 3033\t shift -30 ADCs  TRUE  Power ED\r\nMAC 884A800006EA no hop  FEC=0GwAddr 1\tEdAddr 2\r\nSync Word: F0F0\r\n"
         */
          QStringList splitOnSlashR = parseGatewayData.split('\r');
          // qDebug() << Q_FUNC_INFO << " number of elements in splitOnSlashR: " << splitOnSlashR.size();

          if ( parseGatewayData.contains("Auxilary GW information"))
          {
              numberOfMatches = 0;
          }


          // for (int e = 0; e < splitOnSlashR.size(); e++)
          //{
              //qDebug() << Q_FUNC_INFO << " splitOnSlashR.at(" << e << ") is " << splitOnSlashR.at(e);
          //}

          bool startedMatching = false;

          for (int i = 0; i < splitOnSlashR.size() && continueMatchingLines == true; i++)
          {
              // qDebug() << Q_FUNC_INFO << " element: " << splitOnSlashR.at(i);
              if (numberOfMatches > orderOfGatewayOTALines.size())
              {
                  QString ErrorStr(Q_FUNC_INFO);
                  ErrorStr += " ERROR: " + CurrentDateTime + " Number of Gateway lines matched:" + QString::number(numberOfMatches) + " > number of expected (at most) RE lines:" + QString::number(orderOfGatewayOTALines.size());
                  emit publishParseGatewayParameterBlockThreadError(ErrorStr);
                  qDebug() << ErrorStr;
                  break;
              }
              else if (numberOfMatches >= orderOfGatewayOTALines.size())
              {
                  QString errString(Q_FUNC_INFO);
                  errString += " ERROR: " + CurrentDateTime + " Number of Gateway lines matched > number of expected RE lines. (2nd)";
                  emit publishParseGatewayParameterBlockThreadError(errString);
                  qDebug() << errString;
                  break;
              }

              match = (orderOfGatewayOTALines.at(numberOfMatches)).match(splitOnSlashR.at(i));
              if (match.hasMatch())
              {
                  // qDebug() << Q_FUNC_INFO << " found match at " << i;
                  if (numberOfMatches == ZCount_RE_INDEX)
                  {
                      continueMatchingLines = obtainZCountLineData(splitOnSlashR.at(i));
                      startedMatching = true;
                  }
                  else if (numberOfMatches == Version_RE_INDEX)
                  {
                      continueMatchingLines = obtainVersionLineData(splitOnSlashR.at(i));
                      startedMatching = true;
                  }
                  else if (numberOfMatches == DataRate_RW_INDEX)
                  {
                      continueMatchingLines = obtainDataRateLineData(splitOnSlashR.at(i));
                  }
                  else if (numberOfMatches == UTC_RE_INDEX)
                  {
                      continueMatchingLines = obtainUTCLineData(splitOnSlashR.at(i));
                  }
                  else if (numberOfMatches == MAC_RE_INDEX)
                  {
                      continueMatchingLines = obtainMACLineData(splitOnSlashR.at(i));
                  }
                  else if (numberOfMatches == Sync_RE_INDEX)
                  {
                      continueMatchingLines = obtainSyncwordLineData(splitOnSlashR.at(i));
                  }
                  numberOfMatches++;
                  if (numberOfMatches == orderOfGatewayOTALines.size())
                  {
                      // qDebug() << Q_FUNC_INFO << " got all Gateway Parameter Block data ...";
                      successfullyParsed = true;
                      break;
                  }
              }
              else if (startedMatching == true)
              {
                  QString ErrorStr(Q_FUNC_INFO);
                  ErrorStr += " ERROR: " + CurrentDateTime + " Failed to receive all Gateway Parameter Block data, received and matched:" + QString::number(numberOfMatches) + " of the exprected 5 Gateway PB lines. " + splitOnSlashR.at(i);
                  emit publishParseGatewayParameterBlockThreadError(ErrorStr);
                  qDebug() << ErrorStr;
              }
              else
              {
                  if ((i == (splitOnSlashR.size() - 1)) && (numberOfMatches != 6))
                  {
                      QString ErrorStr(Q_FUNC_INFO);
                      ErrorStr += " ERROR: " + CurrentDateTime + " Failed to receive all Gateway Parameter Block data, received:" + QString::number(numberOfMatches) + " of the expected 5 or 6 Gateway PB lines.";
                      qDebug() << ErrorStr;
                      emit publishParseGatewayParameterBlockThreadError(ErrorStr);
                  }
              }
          }

          if (successfullyParsed == true)
          {
              // qDebug() << Q_FUNC_INFO << " construct GW PB string to publish..." << Qt::endl;
              constructAndPublishGatewayPBList();
          }
          else
          {
              emit parsedGatewayParameterBlockInformation("");
              QString ErrorStr(Q_FUNC_INFO);
              ErrorStr += " ERROR: " + CurrentDateTime + " Unsuccessful in parsing Gateway Parameter Block Information, number of Matches:" + QString::number(numberOfMatches);
              emit publishParseGatewayParameterBlockThreadError(ErrorStr);
              qDebug() << ErrorStr;

          }
		}
	  else
		{
          QThread::msleep(80);
         // qDebug() << Q_FUNC_INFO  << " no data " << Qt::endl;

		}
	}

  qDebug() << Q_FUNC_INFO << " INFO: exiting ...";

  emit this->parseGatewayParameterBlockThreadExit();

}

void ParseGatewayParameterBlockThread::setParseGatewayParameterBlockThreadLogging( bool logging )
{
    qDebug() << Q_FUNC_INFO << " logging " << logging;

}

void ParseGatewayParameterBlockThread::handleTerminate( void )
{
    qDebug() << Q_FUNC_INFO << " INFO: begin ...";

    m_mutex.lock();
    m_gatewayParameterBlockDataToParseList.clear();
    m_operational = false;
    m_mutex.unlock();
    qDebug() << Q_FUNC_INFO << " INFO: end...";
}
