#include <QTime>
#include <QDebug>
#include "defaultParameterBlockValues.h"

ParameterBlock_600V_V2 default_600V __attribute__((__packed__)) __attribute__ ((aligned (1))) = {// Main image PB
  0xAAAA,    // barrier
  (BYTE)0,   // netId
  (BYTE)0,   // myBunch
  0xFFFF,    //  permanent !!! Normal  groupId
  { 0, 0, 0, 0, 0, 0 }, // myMac
  {
    //-0.000784329277, 0.069999928482, -1.557036645365, -229.914041475601 + 32.0    dfK3
    // -0.000693, 0.0556, 0.613, -280 //+ 300.0
    -0.000693, 0.0556, 0.613, -200 // -245 //+ 300.0
  }, // temperature compensation
  {  2496.0, 0.0000004, 73.0 }, // vref polynomials  vrefPolynom
  // linearK offsets and coefficients
   { {16.5, -1700}, {15.3, 0.0}, {7.5, -555.0}, {15.2, -60.0},  {0.435, 625.0}, {7.6, -570 }, {7.6, -520} },
  { 'A', 'N', 'D', 'S',  0,  'l', 'a', 'r', 'A', 'u', 'g', 'u', 's', 't',  0,   7 },   // curKey
  { 'A', 'u', 'g', 'u', 's', 't',  0,   7,  'A', 'u', 'g', 'u', 's', 't',  0,   7 },   // curIV
  0, // fetFailCount (2) (in ticks), 0 disables
  700, // fetCurrentThreshold (2) (in mA)
  80, // fetDeltaCurrent (2) (in mA)
  -250,    // mA, LowCurrentLimitTo255
  35000, // raw ADC counts, VhvLimitVout (07/01/2019, Dr. L wants 700 Volts)
  100,   // IhvLimitVout -> what to set oc to when Vout protection exceeded (07/01/2019)
  32500, // raw ADC counts, VhvLimitVins (07/01/2019, Dr. L wants 650 Volts)
  40,    // IhvLimitVins -> what to set oc to when Vins protection exceeded (07/01/2019)
  { 0, 0, 0 },  //versions[3],
  0, // tests -> MFNetStatus if set to 1 ( MFDebug )
  0xFFFFFFFF,   //install date
  0xFF, 0xFF,   // k_ov_volt, k_oc_cur
  0xF0F0, // syncword
  0, // vin_disable_radio
  0, // rbunch
  0, // gbunch
  181,  // shortCircuitProtection , was 170
  0x85, // was 0xFF, was reserved, now MF: Upper Nibble :Number of Cycles MPP off, lower Nibble # Times to cycle off.
  120,  // sync_phase
  128,  // synch_freq
  0x4D, // bandwidth250
  (BYTE)0, //  should be changed to 0 in the production version   channel
  0, // utcProgram
  0, // utcLow
  0, // utcHigh
  0.00002, // tkCurrent
  0.00005, // tkPower
  false,  // mpp
  false,  // module
  (BYTE)100, // ov
  (BYTE)190, // oc
  0xFF, 2, 1, 0, // radioPower, edAddr, gwAddr, repeaterChannel
  0xFF,  // repeaterPower
  0x97,  // flags
  1,     // showState
  -92,   // CriticalLevel500
  -102,  // CriticalLevel10
  -200,  // pureOffset
  40,    // defCyclesTo500
  30,    // defCyclesTo10
  3,     // defCyclesToStep500Channel
  4,     // defCyclesToStep10Channel
  31250,     // defCycles2SoftKick -> Vout Limit for MF in 600V MF firmware (value set 07/01/2019)
  11900,    // defCycles2HardKick  -> Iout Limit for MF in 600V MF firmware (value set 07/01/2019)
  0x83F, // imageAddr
  0x01,  // versionLow
  0x01,  // versionHigh
  0xFF,  // starting500Channel
  (BYTE)0x89, // flags2
  0xFFFF, // prepAddr
    // rep_step, ov_startup, t_superhot, t_hot, t_cold, fallback_time, network cnst1, network_cnst_2,  oc_protection
        25,          70,         110,    100,     90,     10,              7,             11,           60,
    //oc_step,   mfTimer1,  mfTimer2, ov_step, shunt, max_off,
    10,          0x1000, /*0,          0x10,*/     10,      12,      1,
    // vin_limit, vin_turn_on, vin_switch_off
         0,            0,           0,
    0x5555 // post_barrier
};

ParameterBlock_1300V default_1300V __attribute__((__packed__)) __attribute__ ((aligned (1))) = {// Main image PB
  0xAAAA,    // barrier
  (BYTE)0,   // netId
  (BYTE)0,   // myBunch
  0xFFFF,    //  permanent !!! Normal  groupId
  { 0, 0, 0, 0, 0, 0 }, // myMac
  { -0.000693, 0.0556, 0.613, -200 }, // temperature compensation
  {  2496.0, 0.0000004, 73.0 }, // vref polynomials  vrefPolynom
  // linearK offsets and coefficients
  //  600 MS was Vout  0         Pin  1         Iout   2         Vin  3         Text 4          Iin2  5         Iout+ 6
  //  Vout  0         Vin1  1         Iout   2         Vin2  3         Text 4          Iin1  5         Iin2  6
  // { {27.664, -3575}, {25.083, 0.0}, {7.767, -573.0}, {24.767, 0.0}, {0.435, 625.0}, {7.857, -592 }, {8.037, -545} },
  // { {27.64, -3500}, {25.06, 0.0}, {7.75, -570.0}, {24.97, -235.0}, {0.435, 625.0}, {7.9, -532 }, {7.78, -586} },
   { {18.45, -2300}, {16.73, 0.0}, {7.45, -548.0}, {16.63, -60.0},  {0.435, 625.0}, {7.46, -558 }, {7.61, -511} },
  { 'A', 'N', 'D', 'S',  0,  'l', 'a', 'r', 'A', 'u', 'g', 'u', 's', 't',  0,   7 },   // curKey
  { 'A', 'u', 'g', 'u', 's', 't',  0,   7,  'A', 'u', 'g', 'u', 's', 't',  0,   7 },   // curIV
  0, // fetFailCount (2) (in ticks)
  700, // fetCurrentThreshold (2) (in mA)
  80, // fetDeltaCurrent (2) (in mA)
  -250,    // mA, LowCurrentLimitTo255
  33333, // raw ADC counts, VhvLimitVout (want 1000 V)
  200,   // IhvLimitVout -> what to set oc to
  36667, // raw ADC counts, VhvLimitVins (want 1100 V)
  40,    // IhvLimitVins -> what to set oc to
  { 0, 0, 0 },  //version[3], tests 4
  0, // tests
  0xFFFFFFFF,   //install date
  0xFF, 0xFF,   // k_ov_volt, k_oc_cur
  0xF0F0, // syncword
  0, // vin_disable_radio
  0, // rbunch
  0, // gbunch
  170,  // shortCircuitProtection
  //0xFF, // reserved
  0x85, //reserved now upper nibble how many seconds between Timer2 firing, lower nibble how many times to fire once off limit.
  120,  // sync_phase
  128,  // synch_freq
  0x4D, // bandwidth250
  (BYTE)0, //  should be changed to 0 in the production version   channel
  0, // utcProgram
  0, // utcLow
  0, // utcHigh
  0.00002, // tkCurrent
  0.00005, // tkPower
  false,  // mpp
  false,  // module
  (BYTE)100, // ov
  (BYTE)190, // oc
  0xFF, 2, 1, 0, // radioPower, edAddr, gwAddr, repeaterChannel
  0xFF,  // repeaterPower
  0x97,  // flags
  1,     // showState
  -92,   // CriticalLevel500
  -102,  // CriticalLevel10
  -200,  // pureOffset
  40,    // defCyclesTo500
  30,    // defCyclesTo10
  3,     // defCyclesToStep500Channel
  4,     // defCyclesToStep10Channel
  28800,     // defCycles2SoftKick (Now Memory fix V_OV)
  15000,    // defCycles2HardKick (Now Memory fix I_OC)
  0x83F, // imageAddr
  0x01,  // versionLow
  0x01,  // versionHigh
  0xFF,  // starting500Channel
  (BYTE)0x89, // flags2
  0xFFFF, // prepAddr
    // rep_step, ov_startup, t_superhot, t_hot, t_cold, fallback_time, network cnst1, network_cnst_2,  oc_protection
        25,          70,         110,    100,     90,     10,              7,             11,           60,
    //oc_step,   mfTimer1,  mfTimer2, ov_step, shunt, max_off,
  10,          0x800, /*0,          0x8,*/     10,      26,      1,
    // vin_limit, vin_turn_on, vin_switch_off
         0,            0,           0,
   0x5555 // post_barrier
};

ParameterBlock_1300V_2nd default_1300V_2nd __attribute__((__packed__)) __attribute__ ((aligned (1))) = {// Main image PB
  0xAAAA,    // barrier
  (BYTE)0,   // netId
  (BYTE)0,   // myBunch
  0xFFFF,    //  permanent !!! Normal  groupId
  { 0, 0, 0, 0, 0, 0 }, // myMac
  { -0.000693, 0.0556, 0.613, -200 }, // temperature compensation
  {  2496.0, 0.0000004, 73.0 }, // vref polynomials  vrefPolynom
  // linearK offsets and coefficients
  //  600 MS was Vout  0         Pin  1         Iout   2         Vin  3         Text 4          Iin2  5         Iout+ 6
  //  Vout  0         Vin1  1         Iout   2         Vin2  3         Text 4          Iin1  5         Iin2  6
  // { {27.664, -3575}, {25.083, 0.0}, {7.767, -573.0}, {24.767, 0.0}, {0.435, 625.0}, {7.857, -592 }, {8.037, -545} },
  // { {27.64, -3500}, {25.06, 0.0}, {7.75, -570.0}, {24.97, -235.0}, {0.435, 625.0}, {7.9, -532 }, {7.78, -586} },
   { {18.45, -2300}, {16.73, 0.0}, {7.45, -548.0}, {16.63, -60.0},  {0.435, 625.0}, {7.46, -558 }, {7.61, -511} },
  { 'A', 'N', 'D', 'S',  0,  'l', 'a', 'r', 'A', 'u', 'g', 'u', 's', 't',  0,   7 },   // curKey
  { 'A', 'u', 'g', 'u', 's', 't',  0,   7,  'A', 'u', 'g', 'u', 's', 't',  0,   7 },   // curIV
  0, // fetFailCount (2) (in ticks)
  700, // fetCurrentThreshold (2) (in mA)
  80, // fetDeltaCurrent (2) (in mA)
  -250,    // mA, LowCurrentLimitTo255
  33333, // raw ADC counts, VhvLimitVout (want 1000 V)
  200,   // IhvLimitVout -> what to set oc to
  36667, // raw ADC counts, VhvLimitVins (want 1100 V)
  40,    // IhvLimitVins -> what to set oc to
  { 0, 0, 0 },  //version[3], tests 4
  0, // tests
  0xFFFFFFFF,   //install date
  0xFF, 0xFF,   // k_ov_volt, k_oc_cur
  0xF0F0, // syncword
  0, // vin_disable_radio
  0, // rbunch
  0, // gbunch
  170,  // shortCircuitProtection
  //0xFF, // reserved
  0x85, //reserved now upper nibble how many seconds between Timer2 firing, lower nibble how many times to fire once off limit.
  120,  // sync_phase
  128,  // synch_freq
  0x4D, // bandwidth250
  (BYTE)0, //  should be changed to 0 in the production version   channel
  0, // utcProgram
  0, // utcLow
  0, // utcHigh
  0.00002, // tkCurrent
  0.00005, // tkPower
  false,  // mpp
  false,  // module
  (BYTE)100, // ov
  (BYTE)190, // oc
  0xFF, 2, 1, 0, // radioPower, edAddr, gwAddr, repeaterChannel
  0xFF,  // repeaterPower
  0x97,  // flags
  1,     // showState
  -92,   // CriticalLevel500
  -102,  // CriticalLevel10
  -200,  // pureOffset
  40,    // defCyclesTo500
  30,    // defCyclesTo10
  3,     // defCyclesToStep500Channel
  4,     // defCyclesToStep10Channel
  28800,     // defCycles2SoftKick (Now Memory fix V_OV)
  15000,    // defCycles2HardKick (Now Memory fix I_OC)
  0x83F, // imageAddr
  0x01,  // versionLow
  0x01,  // versionHigh
  0xFF,  // starting500Channel
  (BYTE)0x89, // flags2
  0xFFFF, // prepAddr
    // rep_step, ov_startup, t_superhot, t_hot, t_cold, fallback_time, network cnst1, network_cnst_2,  oc_protection
        25,          70,         110,    100,     90,     10,              7,             11,           60,
    //oc_step,   cur_noise, ov_step, shunt, max_off,
  10,          0x800,           10,      26,      1,
    // vin_limit, vin_turn_on, vin_switch_off
         0,            0,           0,
   0x5555 // post_barrier
};

ParameterBlock_1500V default_1500V __attribute__((__packed__)) __attribute__ ((aligned (1))) = {
        0xAAAA,    // barrier
        (BYTE)0,   // netId
        (BYTE)0,   // myBunch
        0xFFFF,    //  permanent !!! Normal  groupId
        { 0, 0, 0, 0, 0, 0 }, // myMac
        { -0.000693, 0.0556, 0.613, -190 }, // temperature compensation
        {  2496.0, 0.0000004, 73.0 }, // vref polynomials  vrefPolynom
        // linearK offsets and coefficients
        { {27.6, -3500}, {25.0, 0.0}, {9.05, -660.0}, {25.0, -235.0},  {0.435, 625.0}, {9.05, -690 }, {9.05, -680} },
        { 'A', 'N', 'D', 'S',  0,  'l', 'a', 'r', 'A', 'u', 'g', 'u', 's', 't',  0,   7 },   // curKey
        { 'A', 'u', 'g', 'u', 's', 't',  0,   7,  'A', 'u', 'g', 'u', 's', 't',  0,   7 },   // curIV
        0, // fetFailCount (2) (in ticks)
        700, // fetCurrentThreshold (2) (in mA)
        80, // fetDeltaCurrent (2) (in mA)
        -250,    // mA, LowCurrentLimitTo255
        20000,   // VoutLimitCount (milliseconds in protection mode due to Vout > VoutLimit)
        48000,    // VoutLimit  threshold setting (Volts) to engage Over Voltage protection.
        23000,   // IoutLimitCout (milliseconds in protection mode due to Iout > IoutLimit)
        20000,    // IoutLimit -> threshold setting (milliAmps) to engage Over Current protection.
        { 0, 0, 0 }, //version[3], tests in fourth position.
        0, // tests
        0xFFFFFFFF,   //install date
        0xFF, 0xFF,   // k_ov_volt, k_oc_cur
        0xF0F0, // syncword
        0, // vin_disable_radio
        0, // rbunch
        0, // gbunch
        100,  // shortCircuitProtection
        0xFF, // reserved
        120,  // sync_phase
        128,  // synch_freq
        0x4D, // bandwidth250
        (BYTE)0, //  should be changed to 0 in the production version   channel
        0, // utcProgram
        0, // utcLow
        0, // utcHigh
        0.00002, // tkCurrent
        0.00005, // tkPower
        false,  // mpp
        false,  // module
        (BYTE)100, // ov
        (BYTE)190, // oc
        0xFF, 2, 1, 0, // radioPower, edAddr, gwAddr, repeaterChannel
        0xFF,  // repeaterPower
        0x1F,  // flags
        1,     // showState
        -92,   // CriticalLevel500
        -102,  // CriticalLevel10
        -190,  // pureOffset
        40,    // defCyclesTo500
        30,    // defCyclesTo10
        3,     // defCyclesToStep500Channel
        4,     // defCyclesToStep10Channel
        8,     // defCycles2SoftKick
        80,    // defCycles2HardKick
        0x83F, // imageAddr
        0x01,  // versionLow
        0x01,  // versionHigh
        0xFF,  // starting500Channel
        (BYTE)0x82, // flags2
        0xFFFF, // prepAddr
          // rep_step, ov_startup, t_superhot, t_hot, t_cold, fallback_time, network cnst1, network_cnst_2,  oc_protection
              25,          70,         110,    100,     90,     10,              7,             11,           60,
          //oc_step,   cur_noise (dis),  ov_step, shunt, max_off,
             10,          -1000,               10,      30,      1,
          // vin_limit, vin_turn_on, vin_switch_off
               0,            0,           0,
          0x5555 // post_barrier
};


ParameterBlock_1500V_2nd default_1500V_2nd __attribute__((__packed__)) __attribute__ ((aligned (1))) = {
        0xAAAA,    // barrier
        (BYTE)0,   // netId
        (BYTE)0,   // myBunch
        0xFFFF,    //  permanent !!! Normal  groupId
        { 0, 0, 0, 0, 0, 0 }, // myMac
        { -0.000693, 0.0556, 0.613, -190 }, // temperature compensation
        {  2496.0, 0.0000004, 73.0 }, // vref polynomials  vrefPolynom
        // linearK offsets and coefficients
        { {27.6, -3500}, {25.0, 0.0}, {9.05, -660.0}, {25.0, -235.0},  {0.435, 625.0}, {9.05, -690 }, {9.05, -680} },
        { 'A', 'N', 'D', 'S',  0,  'l', 'a', 'r', 'A', 'u', 'g', 'u', 's', 't',  0,   7 },   // curKey
        { 'A', 'u', 'g', 'u', 's', 't',  0,   7,  'A', 'u', 'g', 'u', 's', 't',  0,   7 },   // curIV
        23000, // ef_InputCurrentThreshold (2) (in mA)
        0,     // ef_OccurrenceThreshold (1) 0 disables, else # of occurrence to for algorithm to take action
        4,     // ef_CountDown_Timer (1)  value times 3 for # of seconds between checks
        20,    // ef_AlphaNumerator (1)  value is divided by 1000.0
        0,     // ef_ModuleOff (1) only two valid values (0, and 0xFE), a read only value, set indirectly by firmware.
        -250,    // mA, LowCurrentLimitTo255
        20000,   // VoutLimitCount (milliseconds in protection mode due to Vout > VoutLimit)
        48000,    // VoutLimit  threshold setting (Volts) to engage Over Voltage protection.
        23000,   // IoutLimitCout (milliseconds in protection mode due to Iout > IoutLimit)
        20000,    // IoutLimit -> threshold setting (milliAmps) to engage Over Current protection.
        { 0, 0, 0 }, //versionSuffix[3], tests in fourth position.
        0, // monitoring
        0xFFFFFFFF,   //install date
        0xFF, 0xFF,   // k_ov_volt, k_oc_cur
        0xF0F0, // syncword
        0, // vin_disable_radio
        0, // rbunch
        0, // gbunch
        100,  // shortCircuitProtection
        0xFF, // reserved
        120,  // sync_phase
        128,  // synch_freq
        0x4D, // bandwidth250
        (BYTE)0, //  should be changed to 0 in the production version   channel
        0, // utcProgram
        0, // utcLow
        0, // utcHigh
        0.00002, // tkCurrent
        0.00005, // tkPower
        false,  // mpp
        false,  // module
        (BYTE)100, // ov
        (BYTE)190, // oc
        0xFF, 2, 1, 0, // radioPower, edAddr, gwAddr, repeaterChannel
        0xFF,  // repeaterPower
        0x1F,  // flags
        1,     // showState
        -92,   // CriticalLevel500
        -102,  // CriticalLevel10
        -190,  // pureOffset
        40,    // defCyclesTo500
        30,    // defCyclesTo10
        3,     // defCyclesToStep500Channel
        4,     // defCyclesToStep10Channel
        8,     // defCycles2SoftKick
        80,    // defCycles2HardKick
        0x83F, // imageAddr
        0x01,  // versionLow
        0x01,  // versionHigh
        0xFF,  // starting500Channel
        (BYTE)0x82, // flags2
        0xFFFF, // prepAddr
          // rep_step, ov_startup, t_superhot, t_hot, t_cold, fallback_time, network cnst1, network_cnst_2,  oc_protection
              25,          70,         110,    100,     90,     10,              7,             11,           60,
          //oc_step,   cur_noise (dis),  ov_step, shunt, max_off,
             10,          -1000,               10,      30,      1,
          // vin_limit, vin_turn_on, vin_switch_off
               0,            0,           0,
          0x5555 // post_barrier
};






ParameterBlock_1500V_30 default_1500V_30 __attribute__((__packed__)) __attribute__ ((aligned (1))) = {// Main image PB
  0xAAAA,    // barrier
  (BYTE)0,   // netId
  (BYTE)0,   // myBunch
  0xFFFF,    //  permanent !!! Normal  groupId
  { 0, 0, 0, 0, 0, 0 }, // myMac
  { -0.000693, 0.0556, 0.613, -190 //-200 // -245 //+ 300.0
  }, // temperature compensation
  {  2496.0, 0.0000004, 73.0 }, // vref polynomials  vrefPolynom
  // linearK offsets and coefficients
  { {27.6, -3470}, {25.0, 0.0}, {13.17, -652.0}, {25.0, -235.0},  {0.435, 625.0}, {13.22, -690 }, {13.22, -682} },
  { 'A', 'N', 'D', 'S',  0,  'l', 'a', 'r', 'A', 'u', 'g', 'u', 's', 't',  0,   7 },   // curKey
  { 'A', 'u', 'g', 'u', 's', 't',  0,   7,  'A', 'u', 'g', 'u', 's', 't',  0,   7 },   // curIV
  0, // fetFailCount (2) (in ticks)
  700, // fetCurrentThreshold (2) (in mA)
  80, // fetDeltaCurrent (2) (in mA)
  -250,    // mA, LowCurrentLimitTo255
  20000,   // VoutLimitCount (milliseconds in protection mode due to Vout > VoutLimit)
  48000,    // VoutLimit  threshold setting (Volts) to engage Over Voltage protection.
  23000,   // IoutLimitCount (milliseconds in protection mode due to Iout > IoutLimit)
  31000,    // IoutLimit -> threshold setting (milliAmps) to engage Over Current protection.
  { 0, 0, 0 },  //version[3], tests in fourth position.
  0, // test
  0xFFFFFFFF,   //install date
  0x3FFF,   // IinLimit
  0xF0F0, // syncword
  0, // vin_disable_radio
  0, // rbunch
  0, // gbunch
  100,  // shortCircuitProtection
  0xFF, // reserved
  120,  // sync_phase
  128,  // synch_freq
  0x4D, // bandwidth250
  (BYTE)0, //  should be changed to 0 in the production version channel
  0, // utcProgram
  0, // utcLow
  0, // utcHigh
  0.00002, // tkCurrent
  0.00005, // tkPower
  false,  // mpp
  false,  // module
  (BYTE)200, // ov
  (BYTE)200, // oc
  0xFF, 2, 1, 0, // radioPower, edAddr, gwAddr, repeaterChannel
  0xFF,  // repeaterPower
  0x97,  // flags
  0x0F,     // IinLimitStepsAndDelay
  -92,   // CriticalLevel500
  -102,  // CriticalLevel10
  -190,  // pureOffset
  40,    // defCyclesTo500
  30,    // defCyclesTo10
  3,     // defCyclesToStep500Channel
  4,     // defCyclesToStep10Channel
  8,     // defCycles2SoftKick
  80,    // defCycles2HardKick
  0x83F, // imageAddr
  0x01,  // versionLow
  0x01,  // versionHigh
  0xFF,  // starting500Channel
  (BYTE)0x89, // flags2
  0xFFFF, // prepAddr
    // rep_step, ov_startup, t_superhot, t_hot, t_cold, fallback_time, network cnst1, network_cnst_2,  oc_protection
        25,          200,         110,    100,     90,     10,              7,             11,           60,
    //oc_step,   cur_noise (dis),  ov_step, shunt, max_off,
       10,          -1000,               10,      33,      1,
    // vin_limit, vin_turn_on, vin_switch_off
         0,            0,           0,
    0x5555 // post_barrier
};



defaultParameterBlock::defaultParameterBlock( void )
{

}

defaultParameterBlock::defaultParameterBlock(const QString tFamily, const QString tMac) :
    _family{tFamily},
    _mac{tMac}
{
}

void defaultParameterBlock::obtainTrackerDefaultParameterBlockValues( void )
{
    if (_family == Family600V_V2)
    {
        qDebug() << Q_FUNC_INFO << " INFO: setting default PB info for MAC " << _mac << " family " << _family << "\n";
        defaultPBValues.parameterBlockFamily = Family600V_V2_Shunt;
        defaultPBValues.PB.a600V_V2VPB = default_600V;
    }
    else if (_family == Family1300V)
    {
        qDebug() << Q_FUNC_INFO << " INFO: setting default PB info for MAC " << _mac << " family " << _family << "\n";
        defaultPBValues.parameterBlockFamily = Family1300V_Shunt;
        defaultPBValues.PB.a1300VPB = default_1300V;
    }
    else if (_family == Family1300V_2nd)
    {
        qDebug() << Q_FUNC_INFO << " INFO: setting default PB info for MAC " << _mac << " family " << _family << "\n";
        defaultPBValues.parameterBlockFamily = Family1300V_2nd_Shunt;
        defaultPBValues.PB.a1300_2ndVPB = default_1300V_2nd;
    }
    else if (_family == Family1500V)
    {
        qDebug() << Q_FUNC_INFO << " INFO: setting default PB info for MAC " << _mac << " family " << _family << "\n";
        defaultPBValues.parameterBlockFamily = Family1500V_Shunt;
        defaultPBValues.PB.a1500VPB = default_1500V;
    }
    else if (_family == Family1500V_2nd)
    {
        qDebug() << Q_FUNC_INFO << " INFO: setting default PB info for MAC " << _mac << " family " << _family << "\n";
        defaultPBValues.parameterBlockFamily = Family1500V_2nd_Shunt;
        defaultPBValues.PB.a1500_2ndVPB = default_1500V_2nd;
    }
    else if (_family == Family1500V_30)
    {
        qDebug() << Q_FUNC_INFO << " INFO: setting default PB info for MAC " << _mac << " family " << _family << "\n";
        defaultPBValues.parameterBlockFamily = Family1500V_30_Shunt;
        defaultPBValues.PB.a1500_30VPB = default_1500V_30;
    }
    else
    {
        qDebug() << Q_FUNC_INFO << " ERROR: default PB information not available for family " << _family << "\n";
    }
}

bool defaultParameterBlock::obtainDefaultParameterBlock( void )
{
    bool retValue = false;
    if (_mac != "")
    {
        if (_family != "")
        {
            qDebug() << Q_FUNC_INFO << " INFO: Getting default PB for MAC " << _mac << " family: " << _family << "\n";
            // based on family, get the default parameter block
        }
        else
        {
            qDebug() << Q_FUNC_INFO << " ERROR: Trying to obtain default parameter info without optimizer family info...\n";
        }
    }
    else
    {
        qDebug() << Q_FUNC_INFO << " ERROR: Trying to obtain default parameter info without a MAC...\n";
    }
    return retValue;
}
