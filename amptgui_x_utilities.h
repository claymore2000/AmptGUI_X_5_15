#ifndef AMPTGUI_X_UTILITIES_H
#define AMPTGUI_X_UTILITIES_H

#include <QString>
#include <QByteArray>

#include "amptgui_x_status.h"
#include "dataTypeMappings.h"

const unsigned char AsciiCodeFor0 = 48;
const unsigned char AsciiCodeFor9 = 57;
const unsigned char AsciiCodeForA = 65;
const unsigned char AsciiCodeForF = 70;
const unsigned char AsciiCodeFora = 97;
const unsigned char AsciiCodeForf = 102;

AmptGUI_X_Status fourByteHexStringToFloat(QString & token , float & floatValue, const bool & reverse);

AmptGUI_X_Status hexStringToDecimalSignedLong(QString & token, qint32 & longValue, const bool & reverse );
AmptGUI_X_Status hexStringToDecimalUnsignedLong( QString & token, quint32 & longValue, const bool & reverse );

AmptGUI_X_Status hexStringToDecimalSignedInt( QString & token, qint16 & intValue, const bool & reverse );
AmptGUI_X_Status hexStringToDecimalUnsignedInt( QString & token, quint16 & intValue, const bool & reverse );

AmptGUI_X_Status hexStringToDecimalSignedByte( QString & token, qint8 & byteValue );
AmptGUI_X_Status hexStringToDecimalUnsignedByte( QString & token, quint8 & byteValue );

AmptGUI_X_Status macStringToSerialNumber(const char * macAddress, char * serialNumber);
AmptGUI_X_Status macQStringToSerialNumber(QString & macAddress, char * serialNumber);

AmptGUI_X_Status serialNumberQStringToMACAddressQString(const QString serialNumber, QString & macAddress);

AmptGUI_X_Status macQStringTo6ByteHexString(const QString & macAddress, BYTE * macHexString);

AmptGUI_X_Status versionSuffixQStringTo3ByteHexString(const QString & versionSuffix, BYTE * versionSuffixHexString);

AmptGUI_X_Status aesStrQStringTo16ByteHexString(const QString & aesStr, BYTE *aesHexString);

float QByteArrayToFloat(QByteArray arr);

void  reverseSignedLong(qint32 & longValue);

bool fileExists(QString path);


#endif // AMPTGUI_X_UTILITIES_H
