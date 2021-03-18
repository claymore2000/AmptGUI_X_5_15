#ifndef DEFAULTPARAMETERBLOCKVALUES_H
#define DEFAULTPARAMETERBLOCKVALUES_H

#include "amptparameterblockconstants.h"
#include "parameter_block_1300V.h"

class defaultParameterBlock
{
public:
    defaultParameterBlock( void );
    defaultParameterBlock(const QString tMac, const QString tFamily);
    bool obtainDefaultParameterBlock( void );

private:
    QString _family;
    QString _mac;
    ParameterBlock_Union defaultPBValues;
    ParameterBlock_Union activePBValues;
    void obtainTrackerDefaultParameterBlockValues( void );
};

#endif // DEFAULTPARAMETERBLOCKVALUES_H
