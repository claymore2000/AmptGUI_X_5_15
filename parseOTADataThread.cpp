/****************************************************************************
**
**
****************************************************************************/
#include <QTime>
#include <QDateTime>
#include <QHash>
#include <QDebug>

#include "parseOTADataThread.h"
#include "amptgui_x_status.h"
#include "amptgui_x_utilities.h"
#include "amptparameterblockconstants.h"

static quint8 bunch = 0;
static qint8  igwOffset = 0;
static qint8  igwRSSI   = 0;
static qint32 itimeStamp = 0;
static qint16 maskIt    = 0;
static QByteArray MAC(12, 'A');
static quint16 iVout = 0;
static quint16 iVin1 = 0;
static qint16  iIout = 0;
static quint16 iVin2 = 0;
static quint16 iText = 0;
static qint16  iIin2 = 0;
static qint16  iIin1 = 0;
static double   dPowerDiss = 0.0;
static quint16 iStatus = 0;
static quint16 iMask = 0;
static qint8   edOffset = 0;
static qint8   edRSSI = 0;
static quint8  ov = 0;
static quint8  oc = 0;
static qint8 itimeSlot = 0;
static quint8 ichannel = 0;

static QHash<QString,int> voltageMultiplier;
static QHash<QString,bool> onMainImage;

static QString formatIt("yyyy_MM_dd:HH_mm_ss");

ParseOTADataThread::ParseOTADataThread(QObject *parent) :
    QThread(parent)
{
    m_operational = true; 
}

ParseOTADataThread::~ParseOTADataThread()
{
    m_mutex.lock();
    m_operational = false;
    m_cond.wakeOne();
    m_mutex.unlock();
    wait();
}


void ParseOTADataThread::setCurrentOptimizerFamily(QString s)
{
      m_currentOptimizerFamily = s;
      setVoltageMultiplier(s);
      qDebug() << Q_FUNC_INFO << " Family is " << s;
}

void ParseOTADataThread::stopParseOTADataThreadOperation( void )
{
    m_mutex.lock();
    m_operational = false;
    m_mutex.unlock();
}


void ParseOTADataThread::parseOTAData(const QString data)
{
    m_mutex.lock();
    m_otaDataToParseList.append(data);
    m_mutex.unlock();
}

void ParseOTADataThread::startParseOTADataThreadInterface(int waitTimeout, const bool logging)
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

void ParseOTADataThread::handleRequestRunningImageForMAC(const QString mac)
{
    if ( onMainImage.contains(mac) )
    {
        publishOnMainImage(mac,onMainImage[mac]);
    }
    else
    {
        QString ErrorStr(Q_FUNC_INFO);
        QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
        ErrorStr += " ERROR: " + CurrentDateTime + " Request for running image for unknown MAC:" + mac;
        emit publishParseOTADataThreadError(mac);
        qDebug() << ErrorStr;
    }
}


void ParseOTADataThread::run()
{
    //QTextStream out(stdout);

    QString qBunch;
    QString qTimeSlot;
    QString qVout;
    QString qVin1;
    QString qIout;
    QString qVin2;
    QString qText;

    QString qIIn2;
    QString qIIn1;

    QString qPowerDiss;
    QString qStatus;
    QString qEDOffset;
    QString qEDRSSI;
    QString qOV;
    QString qOC;
    QString qGWOffset;
    QString qGWRSSI;
    QString qChannel;
    QString qModule;
    QString qMpp;
    QString qMAC;
    QString qSN;
    QString qTime;

    bool ok = false;
    double dTemp;
    const double doubleValue100 = 100.0;

  while (m_operational) 
    {
      // mutex these operations
      m_mutex.lock();
      if (m_otaDataToParseList.isEmpty() == false)
		{
          try
          {
              QString parseOTAData = m_otaDataToParseList.takeFirst();
              m_mutex.unlock();

              if ((parseOTAData.length() == 72) && (parseOTAData.at(0) == '|') && (parseOTAData.at(7) == '|' ))
              {
                   //           1         2         3         4         5         6         7
                   // 012345678901234567890123456789012345678901234567890123456789012345678901
                   // |01FFA5|46047052A7C63C53C00001E881535E000000FB4C610532052F000400F39F960A
                   // |               : 0 to 0,    ignore
                   // Bunch           : 1 to 2,    one unsigned byte
                   // Gateway Offset  : 3 to 4,    one signed byte
                   // Gateway RSSI    : 5 to 6,    one signed byte
                   // |               : 7 to 7,    ignore
                   // timestamp       : 8 to 15,   4 bytes signed integer, flip bytes
                   // several         : 16 to 19,  2 bytes, flip bytes (a mask), a hex string, convert to decimal, then mask
                   // MAC             : 20 to 31,  12 bytes as is
                   // Vout            : 32 to 35,  2 bytes, flip
                   // Vin             : 36 to 39,  2 bytes, flip
                   // Iout            : 40 to 43,  2 bytes, flip, signed, first bit set, make 0
                   // Vin2            : 44 to 47,  2 bytes, flip
                   // Text            : 48 to 51,  2 bytes, flip
                   // Iin2            : 52 to 55,  2 bytes, flip, signed, first bit set, make 0
                   // Iin1            : 56 to 59,  2 bytes, flip, signed. first bit set, make 0
                   // Status          : 60 to 63,  2 bytes, flip
                   // ED off          : 64 to 65,  1 byte
                   // ED RSSI         : 66 to 67,  1 byte
                   // OV              : 68 to 69,  1 byte
                   // OC              : 70 to 71,  1 byte

                  // Send to RawDataArray with MAC first?

                  // QString RawData("Raw Data dude 72 ...");


                  bunch = static_cast<quint8>(parseOTAData.mid(1,2).toInt(&ok, 16));
                  igwOffset = static_cast<qint8>(parseOTAData.mid(3,2).toInt(&ok,16));
                  igwRSSI = static_cast<qint8>(parseOTAData.mid(5,2).toInt(&ok,16));
                  QString imeStamp(parseOTAData.mid(8,8));
                  //qint32 tS = 0;
                  hexStringToDecimalSignedLong(imeStamp,itimeStamp,true);

                  QDateTime qDTime(QDateTime::fromTime_t(static_cast<uint>(itimeStamp)));
                  qTime = qDTime.toString(formatIt);

                  maskIt = static_cast<qint16>(parseOTAData.mid(16,4).toInt(&ok,16));
                  QString rmaskIt(parseOTAData.mid(16,4)); //18,1));
                  // rmaskIt += parseOTAData.mid(19,1);
                  // rmaskIt += parseOTAData.mid(16,1);
                  // rmaskIt += parseOTAData.mid(17,1);

                  // quint16 tM = 0;

                  hexStringToDecimalUnsignedInt(rmaskIt,iMask, true);
                  bool mppOn = ((iMask >> 14) & 1);
                  bool moduleOn = ((iMask >> 15) & 1);
                  itimeSlot = ((iMask >> 10) & 0xF);
                  ichannel = ((iMask & 0xFF));

                  qMAC = parseOTAData.mid(20,12);
                  char serialNumber[12];
                  macQStringToSerialNumber(qMAC,serialNumber);
                  qSN = serialNumber;

                  QString vOut(parseOTAData.mid(32,4));
                  hexStringToDecimalUnsignedInt(vOut,iVout,true);

                  QString vIn1(parseOTAData.mid(36,4));
                  hexStringToDecimalUnsignedInt(vIn1,iVin1,true);

                  QString iOut(parseOTAData.mid(40,4));
                  hexStringToDecimalSignedInt(iOut,iIout,true);

                  QString vIn2(parseOTAData.mid(44,4));
                  hexStringToDecimalUnsignedInt(vIn2,iVin2,true);

                  QString text(parseOTAData.mid(48,4));
                  hexStringToDecimalUnsignedInt(text,iText,true);

                  QString iIn2(parseOTAData.mid(52,4));
                  hexStringToDecimalSignedInt(iIn2,iIin2,true);

                  QString iIn1(parseOTAData.mid(56,4));
                  hexStringToDecimalSignedInt(iIn1,iIin1,true);

                  QString status(parseOTAData.mid(60,4));
                  hexStringToDecimalUnsignedInt(status,iStatus,true);

                  edOffset = static_cast<qint8>(parseOTAData.mid(64,2).toInt(&ok,16));
                  edRSSI = static_cast<qint8>(parseOTAData.mid(66,2).toInt(&ok,16));
                  ov = static_cast<quint8>(parseOTAData.mid(68,2).toInt(&ok,16));
                  oc = static_cast<quint8>(parseOTAData.mid(70,2).toInt(&ok,16));

                  if (! voltageMultiplier.contains(qMAC))
                  {
                      voltageMultiplier.insert(qMAC,m_voltageMultiplier); // insert multiplier for selected family until one knows better (when Parameter block is read)
                      // qDebug() << Q_FUNC_INFO << " inserting mac:" << qMAC << " and multiplier:" << m_voltageMultiplier << " into voltageMultiplier hash.";
                  }


                  if ((status < 20) || (status > 47)) // Best way to tell if on main image or 8K is status value
                  {
                      onMainImage.insert(qMAC,true);
                      int vMult = voltageMultiplier[qMAC];
                      qVout = QString::number(((iVout * vMult) / 100.0));
                      qVin1 = QString::number(((iVin1 * vMult) / 100.0));
                      qIout = QString::number((iIout / 1000.0));
                      qVin2 = QString::number(((iVin2 * vMult) / 100.0));
                      qText = QString::number((iText / 100.0));

                      qIIn2 = QString::number((iIin2 / 1000.0));
                      qIIn1 = QString::number((iIin1 / 1000.0));
                      dPowerDiss = ((qVin1.toDouble() * qIIn1.toDouble()) + (qVin2.toDouble() * qIIn2.toDouble())) - (qVout.toDouble() * qIout.toDouble());
                      qPowerDiss = QString::number(dPowerDiss);
                  }
                  else
                  {
                      onMainImage.insert(qMAC,false);
                  }
                  qStatus = QString::number(iStatus);
                  qEDOffset = QString::number(edOffset);
                  qEDRSSI = QString::number(edRSSI);
                  qOV = QString::number(ov);
                  qOC = QString::number(oc);
                  qGWOffset = QString::number(igwOffset);
                  qGWRSSI = QString::number(igwRSSI);
                  qChannel = QString::number(ichannel);
                  qBunch = QString::number(bunch);
                  qTimeSlot = QString::number(itimeSlot);
                  qModule = "Off";
                  if (moduleOn)
                      qModule = "On";
                  qMpp = "Off";
                  if (mppOn)
                      qMpp = "On";

                 //  out << Qt::endl << " parseOTAData:" << parseOTAData << Qt::endl;
                //  out << "MAC: " << qMAC << " SN: " << SN <<
                //         " bunch:" << bunch << " gwOffset:" << gwOffset << " gwRSSI:" << gwRSSI << " timeStamp:" << tS <<
                //         " mask " << tM << " MPP: " << mppOn << " Module: " << moduleOn <<
                //         " timeSlot: " << timeSlot << " channel: " << channel << " vOut: " << tVout <<
                //         " Vin1: " << tVin1 << " Iout: " << tIOut << " Vin2: " << tVin2 <<
                //         " text: " << tText << " IIn2: " << tIIn2 << " IIn1: " << tIIn1 <<
                //         " status: " << tStatus << " edOffset: " << edOffset << " edRSSI: " << edRSSI <<
               //          " ov: " << ov << " oc: " << oc << " qoc: " << qOC
               //       << Qt::endl;

                  QString restOfData(qMAC);
                  restOfData += ",";
                  // restOfData += QString::number(itimeStamp);
                  restOfData += qTime;
                  restOfData += ",";
                  restOfData += qVin1;
                  restOfData += ",";
                  restOfData += qVin2;
                  restOfData += ",";
                  restOfData += qVout;
                  restOfData += ",";
                  restOfData += qIIn1;
                  restOfData += ",";
                  restOfData += qIIn2;
                  restOfData += ",";
                  restOfData += qIout;
                  restOfData += ",";
                  restOfData += qPowerDiss;
                  restOfData += ",";
                  restOfData += qText;
                  restOfData += ",";
                  restOfData += qStatus;
                  restOfData += ",";
                  restOfData += qOV;
                  restOfData += ",";
                  restOfData += qOC;
                  restOfData += ",";
                  restOfData += qModule;
                  restOfData += ",";
                  restOfData += qMpp;
                  restOfData += ",";
                  restOfData += qChannel;
                  restOfData += ",";
                  restOfData += qBunch;
                  restOfData += ",";
                  restOfData += qTimeSlot;
                  restOfData += ",";
                  restOfData += qGWOffset;
                  restOfData += ",";
                  restOfData += qGWRSSI;
                  restOfData += ",";
                  restOfData += qEDOffset;
                  restOfData += ",";
                  restOfData += qEDRSSI;


                  // out << "restOfData: " << restOfData << Qt::endl;

                  emit parsedOTADataThreadRawMessage(qSN,restOfData); // MAC); //parseOTAData);
              }
              else if (parseOTAData.mid(0,5) == "\r\nL1:")
              {
                  ok = true;

              // qDebug() << Q_FUNC_INFO << " got a Long Format message: " << parseOTAData;
              QStringList longFormatSplit = parseOTAData.split('\t');

              // qDebug() << Q_FUNC_INFO << " number of elements when split: " << longFormatSplit.size();

              for (int i = 0; i < longFormatSplit.size(); i++)
              {
                  // qDebug() << Q_FUNC_INFO << " index: " << i << " value: " << longFormatSplit.at(i);
                  if (i == 2)
                  {
                      QStringList netID = (longFormatSplit.at(i)).split(':');
                      if (netID.size() == 2)
                      {
                          qBunch = netID.at(0);
                          qTimeSlot = netID.at(1);
                      }

                  }
                  else if (i == 3)
                  {
                      qMAC = longFormatSplit.at(i);
                      char serialNumber[12];
                      macQStringToSerialNumber(qMAC,serialNumber);
                      qSN = serialNumber;
                  }
                  else if (i == 4) // UTC
                  {
                      QDateTime qDTime(QDateTime::fromTime_t(static_cast<uint>((longFormatSplit.at(i)).toInt())));
                      qTime = qDTime.toString(formatIt);

                  }
                  else if (i == 5)
                  {
                      qChannel = longFormatSplit.at(i);
                  }
                  else if (i == 6)
                  {
                      qGWOffset = longFormatSplit.at(i);
                  }
                  else if (i == 7)
                  {
                      QStringList gwOffSplit = (longFormatSplit.at(i)).split(' ');
                      if (gwOffSplit.size() == 2)
                      {
                          qGWRSSI = gwOffSplit.at(0);
                      }
                  }
                  else if (i == 8)
                  {
                      qEDOffset = longFormatSplit.at(i);
                  }
                  else if (i == 9)
                  {
                      QStringList edOffSplit = (longFormatSplit.at(i)).split(' ');
                      if (edOffSplit.size() == 2)
                      {
                          qEDRSSI = edOffSplit.at(0);
                      }
                  }
                  else if (i == 10)
                  {
                      dTemp = longFormatSplit.at(i).toDouble(&ok);
                      if (ok == true)
                      {
                          dTemp = (m_voltageMultiplier * dTemp) / doubleValue100;
                          qVout = QString::number(dTemp);
                      }
                      else
                      {
                          qVout = "ERROR";
                      }
                  }
                  else if (i == 11)
                  {
                      dTemp = longFormatSplit.at(i).toDouble(&ok);
                      if (ok == true)
                      {
                          dTemp = (m_voltageMultiplier * dTemp) / 100.0;
                          qVin1 = QString::number(dTemp);
                      }
                      else
                      {
                          qVin1 = "ERROR";
                      }
                  }
                  else if (i == 12)
                  {
                      dTemp = longFormatSplit.at(i).toDouble(&ok);
                      if (ok == true)
                      {
                          dTemp = dTemp/ 1000.0;
                          qIout = QString::number(dTemp);
                      }
                  }
                  else if (i == 13)
                  {
                      dTemp = longFormatSplit.at(i).toDouble(&ok);
                      if (ok == true)
                      {
                          dTemp = (m_voltageMultiplier * dTemp) / 100.0;
                          qVin2 = QString::number(dTemp);
                      }
                      else
                      {
                          qVin2 = "ERROR";
                      }
                  }
                  else if (i == 14)
                  {
                      dTemp = longFormatSplit.at(i).toDouble(&ok);
                      if (ok == true)
                      {
                          dTemp = dTemp / 100.0;
                          qText = QString::number(dTemp);
                      }
                  }
                  else if (i == 15)
                  {
                      dTemp = longFormatSplit.at(i).toDouble(&ok);
                      if (ok == true)
                      {
                          dTemp = dTemp/ 1000.0;
                          qIIn2 = QString::number(dTemp);
                      }
                  }
                  else if (i == 16)
                  {
                      dTemp = longFormatSplit.at(i).toDouble(&ok);
                      if (ok == true)
                      {
                          dTemp = dTemp/ 1000.0;
                          qIIn1 = QString::number(dTemp);
                      }
                  }
                  else if (i == 17)
                  {
                      qStatus = longFormatSplit.at(i);
                  }
                  else if (i == 18)
                  {
                      QStringList ovSplit = (longFormatSplit.at(i)).split(' ');
                      if (ovSplit.size() == 2)
                      {
                          qOV = ovSplit.at(1);
                      }
                  }
                  else if (i == 19)
                  {
                      QStringList ocSplit = (longFormatSplit.at(i)).split(' ');
                      if (ocSplit.size() == 2)
                      {
                          qOC = ocSplit.at(1);
                      }
                  }
                  else if (i == 20)
                  {
                      // qDebug() << Q_FUNC_INFO << " MPP: " << longFormatSplit.at(i) << " length: " << (longFormatSplit.at(i)).size();

                      if ((longFormatSplit.at(i)).mid(0,7) == "mpp on ")
                      {
                          qMpp = "On";
                      }
                      else
                      {
                          qMpp = "Off";
                      }
                  }
                  else if (i == 21)
                  {

                      if ((longFormatSplit.at(i)).mid(0,9) == "module on")
                      {
                          qModule = "On";
                      }
                      else
                      {
                          qModule = "Off";

                      }
                  }
              }
              dPowerDiss = ((qVin1.toDouble() * qIIn1.toDouble()) + (qVin2.toDouble() * qIIn2.toDouble())) - (qVout.toDouble() * qIout.toDouble());
              qPowerDiss = QString::number(dPowerDiss);

              // "\r\nL1:\t1182\t0:1\t4866400388E6\t1519681934\t2\t-1\t-44 dB\t12\t-49 dB\r\nL2:\t259\t34412\t8490\t37586\t2357\t8325\t8441\t316\tOV: 190\tOC: 40\tmpp on \tmodule on\r\n"
              QString restOfData(qMAC);
              restOfData += ",";
              // restOfData += QString::number(itimeStamp);
              restOfData += qTime;
              restOfData += ",";
              restOfData += qVin1;
              restOfData += ",";
              restOfData += qVin2;
              restOfData += ",";
              restOfData += qVout;
              restOfData += ",";
              restOfData += qIIn1;
              restOfData += ",";
              restOfData += qIIn2;
              restOfData += ",";
              restOfData += qIout;
              restOfData += ",";
              restOfData += qPowerDiss;
              restOfData += ",";
              restOfData += qText;
              restOfData += ",";
              restOfData += qStatus;
              restOfData += ",";
              restOfData += qOV;
              restOfData += ",";
              restOfData += qOC;
              restOfData += ",";
              restOfData += qModule;
              restOfData += ",";
              restOfData += qMpp;
              restOfData += ",";
              restOfData += qChannel;
              restOfData += ",";
              restOfData += qBunch;
              restOfData += ",";
              restOfData += qTimeSlot;
              restOfData += ",";
              restOfData += qGWOffset;
              restOfData += ",";
              restOfData += qGWRSSI;
              restOfData += ",";
              restOfData += qEDOffset;
              restOfData += ",";
              restOfData += qEDRSSI;


              // restOfData += QString::number(itimeStamp);
              /*
              restOfData += qTime;
              restOfData += ",";
              restOfData += qVin1;
              restOfData += ",";
              restOfData += qVin2;
              restOfData += ",";
              restOfData += qVout;
              restOfData += ",";
              restOfData += qIIn1;
              restOfData += ",";
              restOfData += qIIn2;
              restOfData += ",";
              restOfData += qIout;
              restOfData += ",";
              restOfData += qText;
              restOfData += ",";
              restOfData += qStatus;
              restOfData += ",";
              restOfData += qGWOffset;
              restOfData += ",";
              restOfData += qGWRSSI;
              restOfData += ",";
              restOfData += qEDOffset;
              restOfData += ",";
              restOfData += qEDRSSI;
              restOfData += ",";
              restOfData += qOV;
              restOfData += ",";
              restOfData += qOC;
              restOfData += ",";
              restOfData += qChannel;
              restOfData += ",";
              restOfData += qBunch;
              restOfData += ",";
              restOfData += qTimeSlot;
              restOfData += ",";
              restOfData += qModule;
              restOfData += ",";
              restOfData += qMpp;
              */

              // qDebug() << Q_FUNC_INFO << " rest Of data: " << restOfData;
              emit parsedOTADataThreadRawMessage(qSN,restOfData);
              }
              else if (((parseOTAData.at(2) == '=') && (parseOTAData.at(3) == '>' )))
              {
                  // qDebug() << Q_FUNC_INFO << " got superCycle: " << parseOTAData;
              }
          }
          catch(...)
          {
              qDebug() << Q_FUNC_INFO << "Exception thrown getting OTA string. ";
          }
      }
	  else
		{
          m_mutex.unlock();
          QThread::msleep(80);
         // out << Qt::endl << "no data " << Qt::endl;

		}
	}

  qDebug() << Q_FUNC_INFO << " INFO: exiting ...";

  emit this->parseOTADataThreadExit();
  
}

void ParseOTADataThread::parseOTADataThreadLogging( bool logging )
{
    m_logData = logging;
}

void ParseOTADataThread::handleOptimizerFamilyChanged( const QString s)
{
    qDebug() << Q_FUNC_INFO << " INFO: got " << s;
    if (s.length() > 2)
    {
        m_currentOptimizerFamily = s;

        setVoltageMultiplier(s);

        qDebug() << Q_FUNC_INFO << " Optimizer Family Changed: to " << s << Qt::endl;
    }
}

void ParseOTADataThread::setVoltageMultiplier(const QString s)
{
    qDebug() << Q_FUNC_INFO << " passed family " << s;

    if ((s == Family1500V) || (s == Family1500V_30) || (s == Family1500V_2nd) ||
            (s == Family1300V) || (s == Family1300V_2nd))
    {
        m_voltageMultiplier = 3;
    }
    else if ((s == Family1000V) || (s == Family600V_V2) || (s == Family600V_V2_2nd))
    {
        m_voltageMultiplier = 2;

    }
    else
    {
        m_voltageMultiplier = 1;
    }
    qDebug() << Q_FUNC_INFO << " INFO: m_voltageMultiplier now " << m_voltageMultiplier;
}

void ParseOTADataThread::setParameterBlockReadFrom(const bool s)
{
    m_parametersReadFrom = s;
    // qDebug() << Q_FUNC_INFO << " -> " << s << Qt::endl;
}

void ParseOTADataThread::handleMemoryToFromLocationChanged( const bool s)
{
    qDebug() << Q_FUNC_INFO << " This slot needs to be in parseParameterBlockThread ... " << s;
}

void ParseOTADataThread::handlePublishedEndDeviceOptimizerFamily(const QString mac, const int familyShunt)
{
    int vMult = 1;

    // qDebug() << Q_FUNC_INFO << " mac:" << mac << " familyShunt:" << familyShunt;

    if ((familyShunt == Family1500V_Shunt) || ( familyShunt == Family1500V_30_Shunt) || (familyShunt == Family1500V_2nd_Shunt) ||
            (familyShunt == Family1300V_Shunt) || (familyShunt == Family1300V_2nd_Shunt))
    {
        vMult = 3;
    }
    else if ((familyShunt == Family1000V_Shunt) || (familyShunt == Family600V_V2_Shunt))
    {
        vMult = 2;
    }

    if (voltageMultiplier.contains(mac))
    {
        voltageMultiplier.insert(mac,vMult);
        // qDebug() << Q_FUNC_INFO << " inserting mac:" << mac << " and multiplier:" << vMult << " into voltageMultiplier hash.";
    }
    else
    {
        voltageMultiplier.insert(mac,vMult);
        QString ErrorStr(Q_FUNC_INFO);
        QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
        ErrorStr += " ERROR: " + CurrentDateTime + " Unknown mac:" + mac + " Multiplier:" + QString::number(vMult) + " into voltageMultiplier hash, should have already existed.";
        emit publishParseOTADataThreadError(ErrorStr);
        qDebug() << ErrorStr;
    }
}

void ParseOTADataThread::handleTerminate( void )
{
    // qDebug() << Q_FUNC_INFO << " INFO: begin ...";

    m_mutex.lock();
    m_otaDataToParseList.clear();
    m_operational = false;
    m_mutex.unlock();

    // qDebug() << Q_FUNC_INFO << " INFO: end ...";
}
