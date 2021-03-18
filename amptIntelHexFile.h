#ifndef AMPTINTELHEXFILE_H
#define AMPTINTELHEXFILE_H

#include <QString>
#include <QMap>
#include <QHash>
#include <QFile>
#include <QTextStream>

class AmptIntelHexFile
{
public:
    AmptIntelHexFile( void );
    AmptIntelHexFile( const QString & hexFileName);
    ~AmptIntelHexFile( void );
    void SetNameOfAmptIntelHexFile( const QString & hexFileName);
    bool ValidAmptIntelHexFile( void );
private:

    bool validateLineOfDataAgainstCRC(const QString & oneLineOfData, const QString & crcForLine);
    int AddressInPage( const int & address );
    QString name;
    QMap<unsigned int, bool> pagesOccupiedByHexFileQMap;
    QMap<uint16_t, QString> addressToLinesQMap;
    bool valid;
    QFile * hexFile;
    QTextStream hexFileInStream;
    uint16_t firstAddress;
    uint16_t lastAddress;
    bool readOneLine;
};

#endif // AMPTINTELHEXFILE_H
