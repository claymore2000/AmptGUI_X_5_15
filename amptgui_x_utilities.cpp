#include <QTextStream>
#include <QDateTime>
#include <QFileInfo>
#include <QDebug>
#include <stdlib.h>
#include <string.h>
#include <limits>

#include "amptgui_x_utilities.h"


AmptGUI_X_Status convertASCIICodeToValidHexDigit(const char * aByte, unsigned char * validHexDigit)
{
  AmptGUI_X_Status retValue = NO_ERROR;

  if ((*aByte >= AsciiCodeFor0) && (*aByte <= AsciiCodeFor9))
    {
      *validHexDigit = static_cast<BYTE>(*aByte) - AsciiCodeFor0;
    }
  else if ((*aByte >= AsciiCodeForA) && (*aByte <= AsciiCodeForF))
    {
      *validHexDigit = static_cast<BYTE>(*aByte - (AsciiCodeForA - 10));
    }
  else if ((*aByte >= AsciiCodeFora) && (*aByte <= AsciiCodeForf))
    {
      *validHexDigit = static_cast<BYTE>(*aByte - (AsciiCodeFora - 10));
    }
  else
    {
      retValue = ERROR_INVALID_HEX_DIGIT;
    }
  return retValue;
}

AmptGUI_X_Status convertStringToHexBytes(const char * pToStr, BYTE * pToHexBytes, const int & numberOfHexBytes)
{
  AmptGUI_X_Status retValue = NO_ERROR;
  int i = 0;
  const char * ptr = pToStr;
  BYTE * pPtrToHexBytes = pToHexBytes;

  if ((pToStr == nullptr) || (pToHexBytes == nullptr))
    {
      retValue = ERROR_UNEXPECTED_NULL_PTR;
    }
  else
    {
      unsigned char asHexByte;
      AmptGUI_X_Status ok = NO_ERROR;

      for (i = 0; i < numberOfHexBytes && ok == NO_ERROR; i++)
      {
          if ((ok = convertASCIICodeToValidHexDigit(ptr, &asHexByte)) == NO_ERROR)
          {
              ptr++;
              *pPtrToHexBytes = static_cast<BYTE>(asHexByte << 4);
              if ((ok = convertASCIICodeToValidHexDigit(ptr,&asHexByte)) == NO_ERROR)
              {
                  *pPtrToHexBytes++ |= asHexByte;
                  ptr++;
                  // qDebug() << Q_FUNC_INFO << " Got one";
              }
              else
              {
                  retValue = ERROR_CONVERSION_FAILED;
              }
          }
          else
          {
              retValue = ERROR_CONVERSION_FAILED;
          }
      }
  }

  return retValue;
}

/*
int
main(int argc, char * argv[])
{
  int retValue = 0;
  unsigned char * ptrToStr = NULL;
  unsigned char * ptrToHexBytes = NULL;
  unsigned char hexBytesArray[(spaceToMalloc/2)];

  if ((spaceToMalloc % 2) != 0)
    {
      retValue = -3;
    }
  else if ((ptrToStr = (unsigned char *)malloc(spaceToMalloc)) == NULL)
    {
      retValue = -1;
    }
  else if ((ptrToHexBytes = (unsigned char *)malloc((spaceToMalloc/2))) == NULL)
    {
      retValue = -2;;
    }
  else
    {
      ptrToStr = memset((void *)ptrToStr,'9',spaceToMalloc);
      if (convertStringToHexBytes(ptrToStr,ptrToHexBytes) != 0)
      {
          retValue = -3;
      }
      else if (convertStringToHexBytes(ptrToStr,hexBytesArray) != 0)
      {
          retValue = -4;
      }
      free(ptrToStr);
  }
  return retValue;
}
*/

/*
 * pack method for storing data in network, big endian, byte order (MSB first)
 * returns number of bytes packed.
 *
 * usage:
 * float x, y, z;
 * int i = 0;
 * i += packFloat(&buffer[i], x);
 * i += packFloat(&buffer[i], y);
 * i += packFloat(&buffer[i], z);
*/
int packFloat(void *buf, float x)
{
    unsigned char *b = static_cast<unsigned char *>(buf); // (unsigned char *)buf;
    unsigned char *p = (unsigned char *) &x;

#if defined (_M_IX86) || (defined (CPU_FAMILY) && (CPU_FAMILY == I80X86))
    b[0] = p[3];
    b[1] = p[2];
    b[2] = p[1];
    b[3] = p[0];
#else
    b[0] = p[0];
    b[1] = p[1];
    b[2] = p[2];
    b[3] = p[3];
#endif
    return 4;
}

/* unpack method for retrieving data in network byte, big endian, order (MSB first)
 * increments index i by the number of bytes unpacked
 *
 * usage:
 * int i = 0;
 * float x = unpackFloat(&buffer[i], &i);
 * float y = unpackFloat(&buffer[i], &i);
 * float z = unpackFloat(&buffer[i], &i)
 */
float unpackFloat(const void *buf, int *i)
{
    //const unsigned char *b = (const unsigned char *)buf;
    const unsigned char *b = static_cast<const unsigned char *>(buf);

    quint32 temp = 0;
    *i += 4;
    temp = ((b[0] << 24 ) |
            (b[1] << 16) |
            (b[2] << 8) |
            b[3]);

    return *((float *)&temp);
}

static QString reversed;
static const int consume4Bytes = 4;
static unsigned char fourByteHexStringToFloatBuffer[consume4Bytes];

AmptGUI_X_Status fourByteHexStringToFloat(QString & token , float & floatValue, const bool & reverse)
{
    AmptGUI_X_Status retValue = NO_ERROR;
    int bytesConsumed = 4;
    bool *ok = nullptr;

    /*
     * qDebug() << Q_FUNC_INFO << " size of token: " << token.size();
     * qDebug() << Q_FUNC_INFO << " size of float: " << sizeof(float);
     */

    if (reverse == true)
    {
        reversed = token.mid(6,2) + token.mid(4,2) + token.mid(2,2) + token.mid(0,2);
        /*
        qDebug( ) << Q_FUNC_INFO << " reversed As Long " << reversed.toLong(ok,16);

        unsigned char firstByte = ((reversed.mid(0,1)).toInt(ok,16) << 4) + (reversed.mid(1,1)).toInt(ok,16);
        unsigned char secondByte = ((reversed.mid(2,1)).toInt(ok,16) << 4) + (reversed.mid(3,1)).toInt(ok,16);
        unsigned char thirdByte = ((reversed.mid(4,1)).toInt(ok,16) << 4) + (reversed.mid(5,1)).toInt(ok,16);
        unsigned char fourthByte = ((reversed.mid(6,1)).toInt(ok,16) << 4) + (reversed.mid(7,1)).toInt(ok,16);

        qDebug() << Q_FUNC_INFO << " first byte is " << firstByte;

        */

        fourByteHexStringToFloatBuffer[0] = static_cast<unsigned char>(((reversed.mid(0,1)).toInt(ok,16) << 4) + (reversed.mid(1,1)).toInt(ok,16));
        fourByteHexStringToFloatBuffer[1] = static_cast<unsigned char>(((reversed.mid(2,1)).toInt(ok,16) << 4) + (reversed.mid(3,1)).toInt(ok,16));
        fourByteHexStringToFloatBuffer[2] = static_cast<unsigned char>(((reversed.mid(4,1)).toInt(ok,16) << 4) + (reversed.mid(5,1)).toInt(ok,16));
        fourByteHexStringToFloatBuffer[3] = static_cast<unsigned char>(((reversed.mid(6,1)).toInt(ok,16) << 4) + (reversed.mid(7,1)).toInt(ok,16));




        /*
         * char buffer[4];

        buffer[0] = firstByte;
        buffer[1] = secondByte;
        buffer[2] = thirdByte;
        buffer[3] = fourthByte;


        for( int i = 0; i < 4; i++)
        {
            int b = buffer[i];
            qDebug() << " i = " << i << " buffer[i] = " << (quint8)b;
        }
        */

        floatValue = unpackFloat(fourByteHexStringToFloatBuffer,&bytesConsumed);

    }
    else
    {
        fourByteHexStringToFloatBuffer[0] = static_cast<unsigned char>(((token.mid(0,1)).toInt(ok,16) << 4) + (token.mid(1,1)).toInt(ok,16));
        fourByteHexStringToFloatBuffer[1] = static_cast<unsigned char>(((token.mid(2,1)).toInt(ok,16) << 4) + (token.mid(3,1)).toInt(ok,16));
        fourByteHexStringToFloatBuffer[2] = static_cast<unsigned char>(((token.mid(4,1)).toInt(ok,16) << 4) + (token.mid(5,1)).toInt(ok,16));
        fourByteHexStringToFloatBuffer[3] = static_cast<unsigned char>(((token.mid(6,1)).toInt(ok,16) << 4) + (token.mid(7,1)).toInt(ok,16));

        floatValue = unpackFloat(fourByteHexStringToFloatBuffer,&bytesConsumed);
    }
    return retValue;
}

AmptGUI_X_Status hexStringToDecimalUnsignedLong( QString & token, quint32 & longValue, const bool &reverse )
{
    AmptGUI_X_Status retValue = NO_ERROR;
    char * p;

    // qDebug() << Q_FUNC_INFO << " orig token is " << token;

    longValue = static_cast<quint32>(strtoull( (token.toLatin1()).data(), & p, 16 ));

    // qDebug() << Q_FUNC_INFO << " unreversed unsigned long is " << longValue;
    //if ( *p != 0 )
    //{
        // fprintf(OUT,"%s:%d ERROR: Converting %s failed.\n",__FILE__, __LINE__, hexString.c_str());
     //   retValue = ERROR_FAILED_CONVERTING_HEXSTRING;
   // }
    if (reverse == true)
    {
        quint32 temp;

        temp = ((0xFF000000 & longValue) >> 24);
        // qDebug() << Q_FUNC_INFO << " first temp is " << temp;
        temp |= ((0x00FF0000 & longValue) >> 8);
        temp |= ((0x0000FF00 & longValue) << 8);
        temp |= ((0x000000FF & longValue) << 24);

        longValue = temp;

        QString reversed(token.mid(6,2));
        reversed += token.mid(4,2);
        reversed += token.mid(2,2);
        reversed += token.mid(0,2);

        // qDebug() << Q_FUNC_INFO << " reversed token is " << reversed;
        longValue = static_cast<quint32>(strtoull( (reversed.toLatin1().data()), &p, 16 ));

    }

    return retValue;
}

AmptGUI_X_Status hexStringToDecimalSignedLong( QString & token, qint32 & longValue, const bool &reverse )
{
    AmptGUI_X_Status retValue = NO_ERROR;
    char * p;

    // QTextStream out(stdout);

    longValue = static_cast<qint32>(strtoll( (token.toLatin1()), &p, 16 ));
    // out << Qt::endl << "hexStringToDecimalSignedLong " << token <<  " " << longValue << Qt::endl;

    //if ( *p != '\0' )
    //{
    //    out << "hexStringToDecimalSignedLong ERROR" << Qt::endl;

    //    retValue = ERROR_FAILED_CONVERTING_HEXSTRING;
    //}
    if (reverse == true)
    {
        quint32 temp = 0;

        temp = ((0xFF000000 & static_cast<quint32>(longValue)) >> 24);
        temp |= ((0x00FF0000 & static_cast<quint32>(longValue)) >> 8);
        temp |= ((0x0000FF00 & static_cast<quint32>(longValue)) << 8);
        temp |= ((0x000000FF & static_cast<quint32>(longValue)) << 24);

        longValue = static_cast<qint32>(temp);
    }

    return retValue;
}

void reverseSignedLong(qint32 & longValue)
{
    qint32 temp;
    temp = (0x000000FF & longValue);
    temp = ((0x0000FF00 & longValue) >> 8);
    temp = ((0x00FF0000 & longValue) >> 16);
    temp = static_cast<qint32>(((0xFF000000 & static_cast<uint>(longValue)) >> 24));
    longValue = static_cast<qint32>(temp);
}

qint8 hexStringToDecimalSignedInt( QString & token, qint16 & intValue, const bool & reverse )
{
    AmptGUI_X_Status retValue = NO_ERROR;
    char * p;

    intValue = static_cast<qint16>(strtol( (token.toLatin1()).data(), & p, 16 ));

   // if ( *p != 0 )
    //{
        // fprintf(OUT,"%s:%d ERROR: Converting %s failed.\n",__FILE__, __LINE__, hexString.c_str());
    //    retValue = ERROR_FAILED_CONVERTING_HEXSTRING;
    // }
    if (reverse == true)
    {
        qint16 temp;
        temp = static_cast<qint16>(((0x00FF & intValue) << 8));
        temp |= ((0xFF00 & intValue) >> 8);
        intValue = temp;
    }

    return retValue;
}


AmptGUI_X_Status hexStringToDecimalUnsignedInt( QString & token, quint16 & intValue, const bool & reverse )
{
    AmptGUI_X_Status retValue = NO_ERROR;

    char * p;
    // QTextStream out(stdout);

    // out << Qt::endl << "hexStringToDecimalUnsignedInt " << token << Qt::endl;

    intValue = static_cast<quint16>(strtol( (token.toLatin1()).data(), & p, 16 ));

    //if ( *p != 0 )
    //{
    //    // fprintf(OUT,"%s:%d ERROR: Converting %s failed.\n",__FILE__, __LINE__, hexString.c_str());
    //    retValue = ERROR_FAILED_CONVERTING_HEXSTRING;
    //}
    if (reverse == true)
    {
        quint16 temp;
        temp = static_cast<quint16>(((0x00FF & intValue) << 8));
        temp |= ((0xFF00 & intValue) >> 8);
        intValue = temp;
    }

    return retValue;
}

AmptGUI_X_Status hexStringToDecimalSignedByte( QString & token, qint8 & byteValue )
{
    AmptGUI_X_Status retValue = NO_ERROR;
    qint16 intValue = 0;
    char * p;

    intValue = static_cast<qint16>(strtol( (token.toLatin1()).data(), & p, 16 ));
    byteValue = static_cast<qint8>((0x00FF & intValue));

    return retValue;
}

AmptGUI_X_Status hexStringToDecimalUnsignedByte( QString & token, quint8 & byteValue )

{
    AmptGUI_X_Status retValue = NO_ERROR;
    quint16 intValue = 0;
    char * p;

    intValue = static_cast<quint16>(strtol( (token.toLatin1()).data(), & p, 16 ));
    byteValue = (0x00FF & intValue);

    return retValue;
}

AmptGUI_X_Status macStringToSerialNumber(const char * macAddress, char * serialNumber)
{
    AmptGUI_X_Status retValue = NO_ERROR;
    char imac[7]; /* create char arrays for splitting string */
    char number[7];


    //strncpy(imac, &macAddress[0], 6); /* split str ing with strncpy */
    //strncpy(number, &macAddress[6], 6);

    memcpy(imac,&macAddress[0],6);
    memcpy(number,&macAddress[6],6);
    imac[6] = '\0'; /* null terminate strings */
    number[6] = '\0';

    int week = (static_cast<int>(strtol(imac, nullptr, 16)) >> 18) & 63; /* bitwise operations and */
    int year = (static_cast<int>(strtol(imac, nullptr, 16)) >> 11) & 127; /* hex str to int conversions */
    char letter = ((static_cast<int>(strtol(imac, nullptr, 16)) >> 6) & 31) + 65;
    int ser = static_cast<int>(strtol(number, nullptr, 16));

    snprintf(serialNumber, 12, "%02d%02d%c%06d", week, year, letter, ser);

    return retValue;
}

AmptGUI_X_Status versionSuffixQStringTo3ByteHexString(const QString & versionSuffix, BYTE * versionSuffixHexString)
{
    AmptGUI_X_Status retValue = NO_ERROR;

    if (versionSuffix.length() != 6)
    {
        retValue = ERROR_INCORRECT_VERSION_SUFFIX_STRING_LENGTH;
    }
    else if (versionSuffixHexString == nullptr)
    {
        retValue = ERROR_UNEXPECTED_NULL_PTR;
    }
    else
    {
        QByteArray versionSuffixAsQByteArray = versionSuffix.toLocal8Bit();
        char * versionSuffixCharBuffer = versionSuffixAsQByteArray.data();

        // qDebug() << Q_FUNC_INFO << " Ready 1";
        retValue = convertStringToHexBytes(versionSuffixCharBuffer, versionSuffixHexString, 3);
        // qDebug() << Q_FUNC_INFO << "Ready 2 retValue:" << QString::number(retValue) << ( (versionSuffixHexString== NULL) ? " NULL" : " NOT NULL");
    }
    return retValue;
}

AmptGUI_X_Status aesStrQStringTo16ByteHexString(const QString & aesStr, BYTE *aesHexString)
{
    AmptGUI_X_Status retValue = NO_ERROR;

    if (aesStr.length() != 32)
    {
        retValue = ERROR_INCORRECT_AES_STRING_LENGTH;
    }
    else if (aesHexString == nullptr)
    {
        retValue = ERROR_UNEXPECTED_NULL_PTR;
    }
    else
    {
        QByteArray aesStringAsQByteArray = aesStr.toLocal8Bit();
        char * aesStrCharBuffer = aesStringAsQByteArray.data();
        // qDebug() << Q_FUNC_INFO << " Ready 1";
        retValue = convertStringToHexBytes(aesStrCharBuffer, aesHexString, 16);
    }
    return retValue;
}

//static const int bytesInMACHexString = 6;

AmptGUI_X_Status macQStringTo6ByteHexString(const QString & macAddress, BYTE * macHexString)
{
    AmptGUI_X_Status retValue = NO_ERROR;

    if (macAddress.length() != 12)
    {
        retValue = ERROR_INCORRECT_MAC_STRING_LENGTH;
    }
    else if (macHexString == nullptr)
    {
        retValue = ERROR_UNEXPECTED_NULL_PTR;
    }
    else
    {
        QByteArray macAddressAsQByteArray = macAddress.toLocal8Bit();
        char* macAddressCharBuffer = macAddressAsQByteArray.data();
        // qDebug() << Q_FUNC_INFO << "Ready 1";
        retValue = convertStringToHexBytes(macAddressCharBuffer,macHexString,6);
        //qDebug() << Q_FUNC_INFO << "Ready 2 retValue:" << QString::number(retValue) << ( (macHexString == NULL) ? " NULL" : " NOT NULL");

    }

    return retValue;
}


AmptGUI_X_Status macQStringToSerialNumber(QString & macAddress, char * serialNumber)
{
    AmptGUI_X_Status retValue = NO_ERROR;
    QString imac(macAddress.mid(0,6));
    QString number(macAddress.mid(6,6));
    bool ok;

    int iMacAsInt = imac.toInt(&ok, 16);

    int week = ((iMacAsInt >> 18) & 63);
    int year = ((iMacAsInt >> 11) & 127);
    char letter = ((iMacAsInt >> 6) & 31) + 65;
    int ser = number.toInt(&ok,16);


   // int week = ((int)strtol(imac, NULL, 16) >> 18) & 63; /* bitwise operations and */
   // int year = ((int)strtol(imac, NULL, 16) >> 11) & 127; /* hex str to int conversions */
   // char letter = (((int)strtol(imac, NULL, 16) >> 6) & 31) + 65;
   // int ser = (int)strtol(number, NULL, 16);

    snprintf(serialNumber, 12, "%02d%02d%c%06d", week, year, letter, ser);

    return retValue;
}


AmptGUI_X_Status serialNumberQStringToMACAddressQString(const QString serialNumber, QString & macAddress)
{
    AmptGUI_X_Status retValue = NO_ERROR;

    QString s_week = serialNumber.mid(0,2);
    QString s_year = serialNumber.mid(2,2);
    QString s_letter = serialNumber.mid(4,1);
    QString s_ser = serialNumber.mid(5,6);

    int week = s_week.toInt();  /* convert to ints */
    int year = s_year.toInt();

    int letter = QString::number(s_letter.at(0).unicode()).toInt(); /* convert letter in serial to int */

    if ( letter > 96 ){ /* lower case */
        letter -= 97; /* 65 + 32 (to upper) */
    } else {
        letter -= 65;
    }

    int ser = s_ser.toInt();

    int prefix = ((week << 18) | (year << 11)) | (letter << 6); /* bitwise operations */

    macAddress = QString("%1%2").arg(prefix, 6, 16).arg(ser, 6, 16, QLatin1Char('0'));

    macAddress = macAddress.toUpper();

    return retValue;
}


float QByteArrayToFloat(QByteArray arr)
{
    static_assert(std::numeric_limits<float>::is_iec559, "Only supports IEC 559 (IEEE 754) float ");

    quint32 temp = static_cast<quint32>((static_cast<char>(arr[0] << 24)) | (static_cast<char>(arr[1]) << 16) | (static_cast<char>(arr[2]) << 8) | static_cast<char>(arr[3]));
    float *out = reinterpret_cast<float *>(&temp);

    return *out;
}

bool fileExists(QString path) {
    QFileInfo check_file(path);
    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile()) {
        return true;
    } else {
        return false;
    }
}
