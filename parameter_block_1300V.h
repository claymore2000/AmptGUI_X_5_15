

#include "dataTypeMappings.h"
#include "amptparameterblockconstants.h"

#define PAGESIZE   242
#define AES_SIZE    16

typedef struct
{
    UINT16 barrier;
    BYTE   netId, myBunch;
    UINT16 groupId;

    BYTE   myMac[6];
    float dFk[4];
    float vrefPolynom[3];

    float linearK [7][2];

    char curKey[ AES_SIZE ];
    char curIV [ AES_SIZE ];

    INT16 fetFailureCount;
    INT16 fetCurrentThreshold;
    INT16 fetDeltaCurrent;
    INT16 oscLowCurrentLimitInmA;
    UINT16 oscDeltaV;
    INT16 oscOVStartupDelay;
    INT16 oscAfterStartupDelay;
    INT16 oscLowCurrentOnlyDelay;

    BYTE versionSuffix[3];
    BYTE tests;

    UINT32 installDate;
    BYTE k_ov_volt, k_oc_cur;

    UINT16 syncword;
    BYTE   vin_disable_radio, rbunch, gbunch, shortCircuitLevel, reserved;

    BYTE synch_phase, synch_freq, bandwidth250;
    BYTE channel;

    UINT32 utcProgram, utcLow, utcHigh;
    float   tkCurrent, tkPower;

    BOOL    mpp, module;
    BYTE    ov,  oc;

    BYTE    radioPower, edAddr, gwAddr, repeaterChannel, repeaterPower;
    BOOL boolByte1;
        /* production          :      1,         // least significant bit
        ensureWDReset       :      1,
        use12kbod           :      1,
        treatLastByteAsChannel :   1,
        hoppingAllowed      :      1,
        isRelay             :      1,
        is500Always         :      1,
        searchCommunication :      1;         // most significant bit
        */
    BYTE    showState;
    signed char CriticalLevel500, CriticalLevel10;
    INT16  pureOffset;

    UINT16  defCyclesTo500, defCyclesTo10, defCyclesToStep500Channel, defCyclesToStep10Channel,
        defCycles2SoftKick, defCycles2HardKick;
    UINT16  imageAddr;    // magic number - addr 0x4D4
    UINT16  versionLow, versionHigh;
    BYTE    starting500Channel;
    BOOL boolByte2;
       /* tryOtherImageFirst : 1,    // least significant bit
        use250kbod         : 1,
        speculative_report : 1,
        stay_in_rx         : 1,
        useFEC             : 1,
        fuseOVOC           : 1,
        fuseComm           : 1,
        reportUTC          : 1;    // most significant bit
        */
    UINT16  prepAddr;
    BYTE repStep, ov_startup, t_mod_off, toff_fallback, ton_fallback, fallback_time, network_cnst_1, network_cnst_2, oc_protection,
    oc_step;
    INT16   cur_noise;
    BYTE    ov_step, shunt, max_off;
    BYTE    vin_limit, vin_turn_on, vin_switch_off;
    UINT16  post_barrier;
} ParameterBlock_600V_V2;

typedef struct
{
    UINT16 barrier;
    BYTE   netId, myBunch;
    UINT16 groupId;
    BYTE   myMac[6];
    float dFk[4];
    float vrefPolynom[3];
    float linearK [7][2];

    char curKey[ 16 ];
    char curIV [ 16 ];

    INT16 fetFailureCount;
    INT16 fetCurrentThreshold;
    INT16 fetDeltaCurrent;

    INT16  LowCurrentLimitTo255;
    UINT16 VhvLimitVout;
    UINT16 IhvLimitVout;
    UINT16 VhvLimitVins;
    UINT16 IhvLimitVins;

    BYTE versionSuffix[3];
    BYTE tests;
    UINT32 installDate;

    BYTE k_ov_volt, k_oc_cur;
    UINT16 syncword;
    BYTE   vin_disable_radio, rbunch, gbunch, shortCircuitLevel, reserved;
    BYTE synch_phase, synch_freq, bandwidth250;
    BYTE channel;
    UINT32 utcProgram, utcLow, utcHigh;
    float   tkCurrent, tkPower;
    BOOL    mpp, module;
    BYTE    ov,  oc;
    BYTE    radioPower, edAddr, gwAddr, repeaterChannel, repeaterPower;
    BOOL boolByte1;
           /* production          :      1,         // least significant bit (this will be a quint8)
            ensureWDReset       :      1,
            use12kbod           :      1,
            treatLastByteAsChannel :   1,
            hoppingAllowed      :      1,
            isRelay             :      1,
            is500Always         :      1,
            searchCommunication :      1;         // most significant bit
            */
    BYTE    showState;
    signed char CriticalLevel500, CriticalLevel10;
    INT16  pureOffset;

    UINT16  defCyclesTo500, defCyclesTo10, defCyclesToStep500Channel, defCyclesToStep10Channel,
            defCycles2SoftKick, defCycles2HardKick;
    UINT16  imageAddr;
    UINT16  versionLow, versionHigh;
    BYTE    starting500Channel;
    BOOL boolByte2;
          /* tryOtherImageFirst : 1,    // least significant bit (this will be a quint8)
            use250kbod         : 1,
            speculative_report : 1,
            stay_in_rx         : 1,
            useFEC             : 1,
            fuseOVOC           : 1,
            fuseComm           : 1,
            reportUTC          : 1;    // most significant bit
            */
    UINT16  prepAddr;
    BYTE    repStep, ov_startup, t_mod_off, toff_fallback, ton_fallback, fallback_time, network_cnst_1, network_cnst_2, oc_protection,
            oc_step;
    INT16   cur_noise;
    BYTE    ov_step, shunt, max_off;
    BYTE    vin_limit, vin_turn_on, vin_switch_off;
    UINT16  post_barrier;
} ParameterBlock_600V_V2_2nd;

typedef struct
{
    UINT16 barrier;
    BYTE   netId, myBunch;
    UINT16 groupId;

    BYTE   myMac[6];

    float dFk[4];
    float vrefPolynom[3];
    float linearK [7][2];

    char curKey[ AES_SIZE ];
    char curIV [ AES_SIZE ];

    INT16 fetFailureCount;
    INT16 fetCurrentThreshold;
    INT16 fetDeltaCurrent;

    INT16 oscLowCurrentLimitInmA;
    UINT16 oscDeltaV;
    INT16 oscOVStartupDelay;
    INT16 oscAfterStartupDelay;
    INT16 oscLowCurrentOnlyDelay;

    BYTE tests[4];
    UINT32 installDate;
    BYTE k_ov_volt, k_oc_cur;

    UINT16 syncword;
    BYTE   vin_disable_radio, rbunch, gbunch, shortCircuitLevel, reserved;
    BYTE synch_phase, synch_freq, bandwidth250;
    BYTE channel;

    UINT32 utcProgram, utcLow, utcHigh;
    float   tkCurrent, tkPower;

    BOOL    mpp, module;
    BYTE    ov,  oc;
    BYTE    radioPower, edAddr, gwAddr, repeaterChannel, repeaterPower;
    BOOL boolByte1;
       /* production          :      1,         // least significant bit
        ensureWDReset       :      1,
        use12kbod           :      1,
        treatLastByteAsChannel :   1,
        hoppingAllowed      :      1,
        isRelay             :      1,
        is500Always         :      1,
        searchCommunication :      1;         // most significant bit
        */
    BYTE    showState;
    signed char CriticalLevel500, CriticalLevel10;
    INT16  pureOffset;

    UINT16  defCyclesTo500, defCyclesTo10, defCyclesToStep500Channel, defCyclesToStep10Channel,
        defCycles2SoftKick, defCycles2HardKick;

    UINT16  imageAddr;
    UINT16  versionLow, versionHigh;
    BYTE    starting500Channel;

    BOOL boolByte2;
       /* tryOtherImageFirst : 1,    // least significant bit
        use250kbod         : 1,
        speculative_report : 1,
        stay_in_rx         : 1,
        useFEC             : 1,
        fuseOVOC           : 1,
        fuseComm           : 1,
        reportUTC          : 1;    // most significant bit
        */
    UINT16  prepAddr;
    BYTE repStep, ov_startup, t_mod_off, toff_fallback, ton_fallback, fallback_time, network_cnst_1, network_cnst_2, oc_protection,
        oc_step;
    INT16   cur_noise;
    BYTE    ov_step, shunt, max_off;
    BYTE    vin_limit, vin_turn_on, vin_switch_off;
    UINT16  post_barrier;
} ParameterBlock_1000V;

typedef struct 
{
    UINT16 barrier;    
    BYTE   netId, myBunch;
    UINT16 groupId; 
    BYTE   myMac[6];
    float dFk[4];
    float vrefPolynom[3];
    float linearK [7][2];

    char curKey[ 16 ];
    char curIV [ 16 ];

    INT16 fetFailureCount;
    INT16 fetCurrentThreshold;
    INT16 fetDeltaCurrent;

    INT16  LowCurrentLimitTo255;
    UINT16 VhvLimitVout;
    UINT16 IhvLimitVout;
    UINT16 VhvLimitVins;
    UINT16 IhvLimitVins;
    
    BYTE versionSuffix[3];
    BYTE tests;                                   
    UINT32 installDate;
    
    BYTE k_ov_volt, k_oc_cur;
    UINT16 syncword;
    BYTE   vin_disable_radio, rbunch, gbunch, shortCircuitLevel, reserved;
    BYTE synch_phase, synch_freq, bandwidth250;
    BYTE channel;
    UINT32 utcProgram, utcLow, utcHigh;
    float   tkCurrent, tkPower;
    BOOL    mpp, module;
    BYTE    ov,  oc;
    BYTE    radioPower, edAddr, gwAddr, repeaterChannel, repeaterPower;
    BOOL boolByte1;
           /* production          :      1,         // least significant bit (this will be a quint8)
            ensureWDReset       :      1, 
            use12kbod           :      1, 
            treatLastByteAsChannel :   1, 
            hoppingAllowed      :      1,
            isRelay             :      1, 
            is500Always         :      1, 
            searchCommunication :      1;         // most significant bit
            */
    BYTE    showState;
    signed char CriticalLevel500, CriticalLevel10;
    INT16  pureOffset;
    
    UINT16  defCyclesTo500, defCyclesTo10, defCyclesToStep500Channel, defCyclesToStep10Channel, 
            defCycles2SoftKick, defCycles2HardKick;
    UINT16  imageAddr;
    UINT16  versionLow, versionHigh;
    BYTE    starting500Channel;
    BOOL boolByte2;
          /* tryOtherImageFirst : 1,    // least significant bit (this will be a quint8)
            use250kbod         : 1,    
            speculative_report : 1,    
            stay_in_rx         : 1,    
            useFEC             : 1,    
            fuseOVOC           : 1,    
            fuseComm           : 1,    
            reportUTC          : 1;    // most significant bit
            */
    UINT16  prepAddr;
    BYTE    repStep, ov_startup, t_mod_off, toff_fallback, ton_fallback, fallback_time, network_cnst_1, network_cnst_2, oc_protection, 
            oc_step;
    INT16   cur_noise;
    BYTE    ov_step, shunt, max_off;
    BYTE    vin_limit, vin_turn_on, vin_switch_off;
    UINT16  post_barrier;
} ParameterBlock_1300V;

typedef struct
{
    UINT16 barrier;
    BYTE   netId, myBunch;
    UINT16 groupId;
    BYTE   myMac[6];
    float dFk[4];
    float vrefPolynom[3];
    float linearK [7][2];

    char curKey[ 16 ];
    char curIV [ 16 ];

    INT16 fetFailureCount;
    INT16 fetCurrentThreshold;
    INT16 fetDeltaCurrent;

    INT16  LowCurrentLimitTo255;
    UINT16 VhvLimitVout;
    UINT16 IhvLimitVout;
    UINT16 VhvLimitVins;
    UINT16 IhvLimitVins;

    BYTE versionSuffix[3];
    BYTE tests;
    UINT32 installDate;

    BYTE k_ov_volt, k_oc_cur;
    UINT16 syncword;
    BYTE   vin_disable_radio, rbunch, gbunch, shortCircuitLevel, reserved;
    BYTE synch_phase, synch_freq, bandwidth250;
    BYTE channel;
    UINT32 utcProgram, utcLow, utcHigh;
    float   tkCurrent, tkPower;
    BOOL    mpp, module;
    BYTE    ov,  oc;
    BYTE    radioPower, edAddr, gwAddr, repeaterChannel, repeaterPower;
    BOOL boolByte1;
           /* production          :      1,         // least significant bit (this will be a quint8)
            ensureWDReset       :      1,
            use12kbod           :      1,
            treatLastByteAsChannel :   1,
            hoppingAllowed      :      1,
            isRelay             :      1,
            is500Always         :      1,
            searchCommunication :      1;         // most significant bit
            */
    BYTE    showState;
    signed char CriticalLevel500, CriticalLevel10;
    INT16  pureOffset;

    UINT16  defCyclesTo500, defCyclesTo10, defCyclesToStep500Channel, defCyclesToStep10Channel,
            defCycles2SoftKick, defCycles2HardKick;
    UINT16  imageAddr;
    UINT16  versionLow, versionHigh;
    BYTE    starting500Channel;
    BOOL boolByte2;
          /* tryOtherImageFirst : 1,    // least significant bit (this will be a quint8)
            use250kbod         : 1,
            speculative_report : 1,
            stay_in_rx         : 1,
            useFEC             : 1,
            fuseOVOC           : 1,
            fuseComm           : 1,
            reportUTC          : 1;    // most significant bit
            */
    UINT16  prepAddr;
    BYTE    repStep, ov_startup, t_mod_off, toff_fallback, ton_fallback, fallback_time, network_cnst_1, network_cnst_2, oc_protection,
            oc_step;
    INT16   cur_noise;
    BYTE    ov_step, shunt, max_off;
    BYTE    vin_limit, vin_turn_on, vin_switch_off;
    UINT16  post_barrier;
} ParameterBlock_1300V_2nd;



typedef struct
{
    UINT16 barrier;
    BYTE   netId, myBunch;
    UINT16 groupId;
    BYTE   myMac[6];
    float dFk[4];
    float vrefPolynom[3];
    float linearK [7][2];
    char curKey[ AES_SIZE ];
    char curIV [ AES_SIZE ];

    INT16 fetFailureCount;
    INT16 fetCurrentThreshold;
    INT16 fetDeltaCurrent;

    INT16  LowCurrentLimitTo255;
    INT16  VoutLimitCount;
    UINT16 VoutLimit;
    INT16  IoutLimitCount;
    INT16  IoutLimit;
    BYTE versionSuffix[3];
    BYTE tests;

    UINT32 installDate;

    BYTE k_ov_volt, k_oc_cur;
    UINT16 syncword;
    BYTE vin_disable_radio, rbunch, gbunch, shortCircuitLevel, reserved;
    BYTE synch_phase, synch_freq, bandwidth250;
    BYTE channel;

    UINT32 utcProgram, utcLow, utcHigh;
    float   tkCurrent, tkPower;
    BOOL    mpp, module;
    BYTE    ov,  oc;
    BYTE    radioPower, edAddr, gwAddr, repeaterChannel, repeaterPower;
    BOOL boolByte1;
      /*  production          :      1,         // least significant bit
        ensureWDReset       :      1,
        use12kbod           :      1,
        treatLastByteAsChannel :   1,
        hoppingAllowed      :      1,
        isRelay             :      1,
        is500Always         :      1,
        searchCommunication :      1;         // most significant bit
       */
    BYTE    showState;
    signed char CriticalLevel500, CriticalLevel10;
    INT16  pureOffset;

    UINT16  defCyclesTo500, defCyclesTo10, defCyclesToStep500Channel, defCyclesToStep10Channel,
        defCycles2SoftKick, defCycles2HardKick;

    UINT16  imageAddr;
    UINT16  versionLow, versionHigh;
    BYTE    starting500Channel;
    BOOL boolByte2;
      /* tryOtherImageFirst : 1,    // least significant bit
        use250kbod         : 1,
        speculative_report : 1,
        stay_in_rx         : 1,
        useFEC             : 1,
        fuseOVOC           : 1,
        fuseComm           : 1,
        reportUTC          : 1;    // most significant bit
        */
UINT16  prepAddr;
BYTE    repStep, ov_startup, t_mod_off, toff_fallback, ton_fallback, fallback_time, network_cnst_1, network_cnst_2, oc_protection,
        oc_step;
INT16   cur_noise;
BYTE    ov_step, shunt, max_off;
BYTE    vin_limit, vin_turn_on, vin_switch_off;
UINT16  post_barrier;
} ParameterBlock_1500V;

typedef struct
{
    UINT16 barrier;
    BYTE   netId, myBunch;
    UINT16 groupId;
    BYTE   myMac[6];
    float dFk[4];
    float vrefPolynom[3];
    float linearK [7][2];
    char curKey[ AES_SIZE ];
    char curIV [ AES_SIZE ];

    INT16 ef_InputCurrentThreshold;
    BYTE  ef_OccurrenceThreshold;
    BYTE  ef_CountDownTimer;
    BYTE  ef_AlphaNumerator;
    BYTE  ef_ModuleOff;

    INT16  LowCurrentLimitTo255;
    INT16  VoutLimitCount;
    UINT16 VoutLimit;
    INT16  IoutLimitCount;
    INT16  IoutLimit;
    BYTE versionSuffix[3];
    BYTE monitoring;

    UINT32 installDate;

    BYTE k_ov_volt, k_oc_cur;
    UINT16 syncword;
    BYTE vin_disable_radio, rbunch, gbunch, shortCircuitLevel, reserved;
    BYTE synch_phase, synch_freq, bandwidth250;
    BYTE channel;

    UINT32 utcProgram, utcLow, utcHigh;
    float   tkCurrent, tkPower;
    BOOL    mpp, module;
    BYTE    ov,  oc;
    BYTE    radioPower, edAddr, gwAddr, repeaterChannel, repeaterPower;
    BOOL boolByte1;
      /*  production          :      1,         // least significant bit
        ensureWDReset       :      1,
        use12kbod           :      1,
        treatLastByteAsChannel :   1,
        hoppingAllowed      :      1,
        isRelay             :      1,
        is500Always         :      1,
        searchCommunication :      1;         // most significant bit
       */
    BYTE    showState;
    signed char CriticalLevel500, CriticalLevel10;
    INT16  pureOffset;

    UINT16  defCyclesTo500, defCyclesTo10, defCyclesToStep500Channel, defCyclesToStep10Channel,
        defCycles2SoftKick, defCycles2HardKick;

    UINT16  imageAddr;
    UINT16  versionLow, versionHigh;
    BYTE    starting500Channel;
    BOOL boolByte2;
      /* tryOtherImageFirst : 1,    // least significant bit
        use250kbod         : 1,
        speculative_report : 1,
        stay_in_rx         : 1,
        useFEC             : 1,
        fuseOVOC           : 1,
        fuseComm           : 1,
        reportUTC          : 1;    // most significant bit
        */
UINT16  prepAddr;
BYTE    repStep, ov_startup, t_mod_off, toff_fallback, ton_fallback, fallback_time, network_cnst_1, network_cnst_2, oc_protection,
        oc_step;
INT16   cur_noise;
BYTE    ov_step, shunt, max_off;
BYTE    vin_limit, vin_turn_on, vin_switch_off;
UINT16  post_barrier;
} ParameterBlock_1500V_2nd;



typedef struct
{
    UINT16 barrier;
    BYTE   netId, myBunch;
    UINT16 groupId;
    BYTE   myMac[6];
    float dFk[4];
    float vrefPolynom[3];
    float linearK [7][2];
    char curKey[ AES_SIZE ];
    char curIV [ AES_SIZE ];

    INT16 fetFailureCount;
    INT16 fetCurrentThreshold;
    INT16 fetDeltaCurrent;

    INT16  LowCurrentLimitTo255;
    INT16  VoutLimitCount;
    UINT16 VoutLimit;
    INT16  IoutLimitCount;
    INT16  IoutLimit;
    BYTE versionSuffix[3];
    BYTE monitoring;

    UINT32 installDate;

    INT16 IinLimit;
    UINT16 syncword;
    BYTE   vin_disable_radio, rbunch, gbunch, shortCircuitLevel, reserved;
    BYTE synch_phase, synch_freq, bandwidth250;
    BYTE channel;

    UINT32 utcProgram, utcLow, utcHigh;
    float   tkCurrent, tkPower;
    BOOL    mpp, module;
    BYTE    ov,  oc;
    BYTE    radioPower, edAddr, gwAddr, repeaterChannel, repeaterPower;
    BOOL boolByte1;
      /*  production          :      1,         // least significant bit
        ensureWDReset       :      1,
        use12kbod           :      1,
        treatLastByteAsChannel :   1,
        hoppingAllowed      :      1,
        isRelay             :      1,
        is500Always         :      1,
        searchCommunication :      1;         // most significant bit
       */
    BYTE    IinOCStepsAndDelay;
    signed char CriticalLevel500, CriticalLevel10;
    INT16  pureOffset;

    UINT16  defCyclesTo500, defCyclesTo10, defCyclesToStep500Channel, defCyclesToStep10Channel,
        defCycles2SoftKick, defCycles2HardKick;

    UINT16  imageAddr;
    UINT16  versionLow, versionHigh;
    BYTE    starting500Channel;
    BOOL boolByte2;
      /* tryOtherImageFirst : 1,    // least significant bit
        use250kbod         : 1,
        speculative_report : 1,
        stay_in_rx         : 1,
        useFEC             : 1,
        fuseOVOC           : 1,
        fuseComm           : 1,
        reportUTC          : 1;    // most significant bit
        */
UINT16  prepAddr;
BYTE    repStep, ov_startup, t_mod_off, toff_fallback, ton_fallback, fallback_time, network_cnst_1, network_cnst_2, oc_protection,
        oc_step;
INT16   cur_noise;
BYTE    ov_step, shunt, max_off;
BYTE    vin_limit, vin_turn_on, IinLimitTempAmbientAdjust;
UINT16  post_barrier;
} ParameterBlock_1500V_30;



typedef struct
{
    int parameterBlockFamily;
    union
    {
        ParameterBlock_600V_V2 a600V_V2VPB;
        ParameterBlock_600V_V2_2nd a600V_V2_2ndVPB;
        ParameterBlock_1000V a1000VPB;
        ParameterBlock_1300V a1300VPB;
        ParameterBlock_1300V_2nd a1300_2ndVPB;
        ParameterBlock_1500V a1500VPB;
        ParameterBlock_1500V_2nd a1500_2ndVPB;
        ParameterBlock_1500V_30 a1500_30VPB;
    } PB;
    QString rawData;
} ParameterBlock_Union;
