#include <amptIntelHexFile.h>

#include <QTime>
#include <QDateTime>
#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

static const QRegularExpression ValidStartOfIntelHexFile("^:[0-1][0-9|A-F][0-9|A-F]{4}[0][0-5]");
static const QRegularExpression ValidIntelHexFileByteCount("^(:)/([0-1][0-9|A-F])");
static QRegularExpressionMatch match;

// Last two characters are CRC, generate CRC to validate ...

AmptIntelHexFile::AmptIntelHexFile( void ) : valid (false)
{

}

AmptIntelHexFile::AmptIntelHexFile(const QString & fileName) : name{fileName}, valid{false}, firstAddress{65535}, lastAddress{0}
{
    qDebug() << Q_FUNC_INFO << " INFO: name of file is " << name;
    hexFile = nullptr;
}

AmptIntelHexFile::~AmptIntelHexFile( void )
{

}

int AmptIntelHexFile::AddressInPage( const int & address )
{
     return address >> 10;
}

bool AmptIntelHexFile::validateLineOfDataAgainstCRC(const QString & oneLineOfData, const QString & crcForLine)
{
    bool retValue = false;

    int lengthOfOneLineOfData = oneLineOfData.length();
    if ((lengthOfOneLineOfData % 2) == 0)
    {
        int numberOfBytesInLine = lengthOfOneLineOfData / 2;
        uint16_t calculatedCRC = 0;
        //uint16_t onesComplement = 0;
        uint16_t twosComplement = 0;

        bool ok = true;
        for (int i = 0; (i < numberOfBytesInLine) && (ok == true); i++)
        {
            calculatedCRC += (oneLineOfData.mid(i * 2,2)).toUInt(&ok,16);
        }

        if (ok)
        {
            // onesComplement = ~calculatedCRC;
            twosComplement = (((~calculatedCRC) + 1) & 0x00FF);
            //calculatedCRC = (((~calculatedCRC) + 1) * 0x00FF);
            qDebug() << Q_FUNC_INFO << " CRC:" << crcForLine << " cCRC:" << (QString::number(twosComplement,16)).toUpper() ;
            if ((crcForLine.toUInt(&ok,16) == twosComplement) && (ok == true))
            {
                retValue = true;
            }
            else
            {
                qDebug() << Q_FUNC_INFO << " ERROR: Expected CRC:" << crcForLine << " does not match calculated CRC:" << (QString::number(twosComplement,16)).toUpper();
            }
        }
        else
        {
            qDebug() << Q_FUNC_INFO << " ERROR: Failed converted line of data for CRC comparison for line:" << oneLineOfData;
        }
    }
    else
    {
        qDebug() << Q_FUNC_INFO << " ERROR: valid line should be length of mod 2 remainder 0, line: " << oneLineOfData;
    }

    return retValue;
}

bool AmptIntelHexFile::ValidAmptIntelHexFile ( void )
{
    qDebug() << Q_FUNC_INFO << " Entering ..., attempt to open Intel Hex file " << name;

    if (hexFile == nullptr)
    {
        hexFile = new QFile(name);
    }
    else
    {
        delete hexFile;
        pagesOccupiedByHexFileQMap.clear();
        addressToLinesQMap.clear();

        hexFile = new QFile(name);
    }
    if (hexFile->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << Q_FUNC_INFO << " successful open of hex file " << name;

        valid = true;
        bool ok = true;
        firstAddress = 65535;
        lastAddress = 0;
        readOneLine = false;
        uint16_t lastLinesAddress = 0;

        while ((!hexFile->atEnd()) && valid)
        {
            QByteArray line = hexFile->readLine();

            qDebug() << Q_FUNC_INFO << " line before trim:" << line << " length:" << line.length();
            line = line.trimmed();
            qDebug() << Q_FUNC_INFO << " line after trim:" << line << " length:" << line.length();

            if (line.length() == 0)
            {
                continue;
            }

            match = ValidStartOfIntelHexFile.match(line);
            if (match.hasMatch())
            {
                QString lineWithoutFirstCharAndCRC = line.mid(1, line.length() - 2 - 1);
                QString byteCount = line.mid(1,2);
                QString addressStr = line.mid(3,4);
                QString recordType = line.mid(7,2);
                QString data = line.mid(9, line.length() - 9 - 2);
                QString cRC = line.mid(line.length() - 2,2);
                //qDebug() << Q_FUNC_INFO << " VALID Intel Hex Line: " << line << " lineWithout:" << lineWithoutFirstCharAndCRC;
                //qDebug() << Q_FUNC_INFO << " byteCount:" << byteCount
                //         << " address:" << addressStr
                //         << " recordType: " << recordType
                //         << " data:" << data
                //         << " cRC:" << cRC;
                if ((valid = validateLineOfDataAgainstCRC(lineWithoutFirstCharAndCRC, cRC)) == true)
                {
                    uint16_t address = addressStr.toUInt(&ok,16);

                    if (readOneLine)
                    {
                        qDebug() << Q_FUNC_INFO << " INFO: checking for gaps (at least 2nd line read) " << QString::number(lastLinesAddress,16);
                        QMap<uint16_t,QString>::iterator iTer = addressToLinesQMap.find(lastLinesAddress);
                        if (iTer != addressToLinesQMap.end())
                        {

                            if (address == (((iTer.value()).length() / 2) + lastLinesAddress) )
                            {
                                qDebug() << Q_FUNC_INFO << " no gap ...";
                            }
                            else
                            {
                                qDebug() << Q_FUNC_INFO << " ERROR: unaccounted for gap in hex file"
                                         << " address:" << address
                                         << " lastLinesAddress:" << lastLinesAddress
                                         << " lastLinesData length:" << ((iTer.value()).length() / 2);
                                valid = false;
                            }
                        }
                        else
                        {
                            qDebug() << Q_FUNC_INFO << " ERROR: last address not found in map.";
                            valid = false;
                        }
                    }
                    lastLinesAddress = address;
                    pagesOccupiedByHexFileQMap.insert(AddressInPage( address),true);
                    addressToLinesQMap.insert(address,data);
                    if (address < firstAddress)
                    {
                        firstAddress = address;
                    }
                    if (address > lastAddress) // could be else but just in case a one line boot file ... :-)
                    {
                        lastAddress = address;
                    }
                    readOneLine = true;
                    lastLinesAddress = address;
                }

            }
            else
            {
               qDebug() << Q_FUNC_INFO << " ERROR INVALID Intel Hex Line: " << line;
               valid = false;
            }
            // break line apart, validate and break into map of address and info ...
        }
        // if valid, set valid
        hexFile->close();
    }
    else
    {
        qDebug() << Q_FUNC_INFO << " ERROR: failed to open hex file: " << name;
    }

    qDebug() << Q_FUNC_INFO << "Exiting .. valid: " << valid;
    QMap<unsigned int, bool>::const_iterator pagesIter = pagesOccupiedByHexFileQMap.constBegin();
    while (pagesIter != pagesOccupiedByHexFileQMap.constEnd())
    {
        qDebug() << Q_FUNC_INFO << " pages mapped :" << pagesIter.key();
        ++pagesIter;
    }
    qDebug() << Q_FUNC_INFO << " firstAddress:" << firstAddress << " lastAddress:" << lastAddress;
    QMap<uint16_t,QString>::const_iterator addressIter = addressToLinesQMap.constBegin();
    while (addressIter != addressToLinesQMap.constEnd())
    {

        qDebug() << Q_FUNC_INFO << " address: " << QString::number(addressIter.key(),16) << " hexLine:" << addressIter.value();
        ++addressIter;
    }

    return valid;
}

void AmptIntelHexFile::SetNameOfAmptIntelHexFile( const QString & hexFileName)
{
    name = hexFileName;
    qDebug() << Q_FUNC_INFO << " Info: name of hexfile: " << name;
}
