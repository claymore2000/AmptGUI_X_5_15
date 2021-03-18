#ifndef AMPTREGISTERCONSTANTS_H
#define AMPTREGISTERCONSTANTS_H

#include <QString>

  const QString offAsInt("0");
  const QString onAsInt("1");

  const QString ByteRegisterCommand("b");
  const QString ByteRegisterCommandInHex("h");
  const QString ByteRegisterCommandNegative("n");
  const QString ShortIntegerRegisterCommand("i");
  const QString ShortIntegerRegisterCommandInHex("H");
  const QString ShortIntegerRegisterCommandNegative("n");
  const QString FloatRegisterCommand("f");

  const QString ByteRegister_GWChannel =  " 1 "; 
  const QString ByteRegister_MPPTracking =  " 4 "; 
  const QString ByteRegister_ModuleOutput =  " 5 "; 
  const QString ByteRegister_ClearEDPage =  " 10 " ;
  const QString ByteRegister_FlashReset =  " 11 " ;
  const QString ByteRegister_Randomize =  " 12 " ;
  const QString ByteRegister_StayInRX = " 13 ";
  const QString ByteRegister_InstallationDate =  " 14 "; 
  const QString ByteRegister_MacByte0 =  " 16 " ;
  const QString ByteRegister_MacByte1 =  " 17 " ;
  const QString ByteRegister_MacByte2 =  " 18 " ;
  const QString ByteRegister_MacByte3 =  " 19 " ;
  const QString ByteRegister_MacByte4 =  " 20 " ;
  const QString ByteRegister_MacByte5 =  " 21 " ;
  const QString ByteRegister_OverVoltageLimit =  " 22 "; 
  const QString ByteRegister_OverCurrentLimit =  " 23 " ;
  const QString ByteRegister_BaseChannel =  " 26 " ;
  const QString ByteRegister_EntirePBToFlash =  " 28 "; 
  const QString ByteRegister_ReportUTCorEnergy =  " 29 "; 
  const QString ByteRegister_RestartMeasurement =  " 30 "; 
  const QString ByteRegister_DisbandNetwork =  " 31 " ;
  const QString ByteRegister_ReportParameterBlockFromRAM =  " 32 "; 
  const QString ByteRegister_MostPBToFlash =  " 33 " ;
  const QString ByteRegister_EDRadioPower =  " 35 " ;
  const QString ByteRegister_EnableSearchRestart =  " 36 "; 
  const QString ByteRegister_CommunicationBaudRate =  " 38 "; 
  const QString ByteRegister_UseFEC =  " 39 " ;
  const QString ByteRegister_EDFrequencyHopping =  " 40 "; 
  const QString ByteRegister_IsRepeater =  " 41 " ;
  const QString ByteRegister_IsSlave =  " 42 "; 
  const QString ByteRegister_RepeaterChannel =  " 43 "; 
  const QString ByteRegister_RepeaterPower =  " 44 " ;
  const QString ByteRegister_SearchModeEnable =  " 45 "; 
  const QString ByteRegister_ReportingMode =  " 46 " ;
  const QString ByteRegister_SearchSignalSlave =  " 47 "; 
  const QString ByteRegister_SearchSignalRepeater =  " 48 "; 
  const QString ByteRegister_EndOfTest =  " 49 " ;
  const QString ByteRegister_ClearMaxBunch =  " 50 "; 
  const QString ByteRegister_SynchronizeMPPCycles =  " 51 "; 
  const QString ByteRegister_SetStartSlaveChannel =  " 53 " ;
  const QString ByteRegister_TryOtherImage =  " 54 " ;
  const QString ByteRegister_CheckFlash =  " 55 " ;
  const QString ByteRegister_SwitchSecurity =  " 56 "; 
  const QString ByteRegister_ReportParameterBlockFromFlash =  " 57 "; 
  const QString ByteRegister_CalibrationRepeat =  " 58 " ;
  const QString ByteRegister_RepeaterSlaveBaudRate =  " 59 "; 
  const QString ByteRegister_SeculativeReport =  " 60 "; 
  const QString ByteRegister_RepeaterStep =  " 61 "; 
  const QString ByteRegister_OVStartup =  " 62 " ;
  const QString ByteRegister_OCFallback =  " 63 " ;
  const QString ByteRegister_TOffFallback =  " 64 "; 
  const QString ByteRegister_TOnFallback =  " 65 " ;
  const QString ByteRegister_FallbackTime =  " 66 " ;
  const QString ByteRegister_NetCnst1 =  " 67 " ;
  const QString ByteRegister_NetCnst2 =  " 68 " ;
  const QString ByteRegister_T_OC_JUMP =  " 69 " ;
  const QString ByteRegister_OCStep =  " 70 " ;
  const QString ByteRegister_WIGGLE_DCHAN =  " 72 "; 
  const QString ByteRegister_OVStep =  " 73 " ;
  const QString ByteRegister_Shunt =  " 74 " ;
  const QString ByteRegister_MaxOff =  " 75 " ;
  const QString ByteRegister_VinLimit =  " 76 "; 
  const QString ByteRegister_VinTurnOn =  " 77 "; 
  const QString ByteRegister_VinTurnOff =  " 78 "; 
  const QString ByteRegister_VinDisableRadio =  " 79 "; 
  const QString ByteRegister_NumberOfBunchesBeforeRepeat =  " 80 "; 
  const QString ByteRegister_GlobalBunchNumber =  " 81 " ;
  const QString ByteRegister_OCShortCircuitLimit =  " 82 "; 
  const QString ByteRegister_FuseCommunication =  " 83 " ;
  const QString ByteRegister_FuseOVAndOC =  " 84 " ;
  const QString ByteRegister_LowUTC =  " 85 " ;
  const QString ByteRegister_HighUTC =  " 86 " ;
  const QString ByteRegister_K_OV_VOLT =  " 87 "; 
  const QString ByteRegister_K_OV_CUR =  " 88 " ;
  const QString ByteRegister_TestStand =  " 91 " ;
  const QString ByteRegister_XTAL_Off =  " 92 " ;
  const QString ByteRegister_SyncPhase =  " 93 " ;
  const QString ByteRegister_SyncFrequency =  " 94 "; 
  const QString ByteRegister_Bandwidth250 =  " 95 " ;
  const QString ByteRegister_TempCalibrate =  " 96 " ;
  const QString ByteRegister_SetMPPCycle =  " 97 " ;
  const QString ByteRegister_Bandwidth500 =  " 100 ";
  const QString ByteRegister_CWave = " 109 " ;
  const QString ByteRegister_WriteMainPBUsing8KPB_f =  " 110 "; 
  const QString ByteRegister_WriteMainPBUsing8KPB_F =  " 111 " ;
  const QString ByteRegister_ReadMainPBFromFlashOf8K =  " 112 " ;
  const QString ByteRegister_ReadCoefficientsSomeOffsetsDFK3AndOC =  " 113 "; 

  // 1500V registers
  const QString ByteRegister_NetMonitoringStatus = " 117 ";
  const QString ByteRegister_SetEFOccurrentThreshold = " 118 ";
  const QString ByteRegister_SetEFCountDownTimer = " 119 ";
  const QString ByteRegister_SetEFAlphaNumerator = " 120 ";
  const QString ByteRegister_ClearEFModuleOff = " 121 ";
  const QString ByteRegister_SetIinLimitOCSteps = " 122 ";
  const QString ByteRegister_SetIinLimitOCDelay = " 123 ";
  const QString ByteRegister_SetIinLimitTempAmbientAdjust = " 124 ";

  const QString ShortIntegerRegister_GroupID =  " 1 " ;
  const QString ShortIntegerRegister_NetworkID =  " 2 " ;
  const QString ShortIntegerRegister_GWEDAddress =  " 3 "; 
  const QString ShortIntegerRegister_SearchCycles_HoppingChannels_C2 =  " 4 "; 
  const QString ShortIntegerRegister_SearchCycles_RepeaterChannels_C4 =  " 5 " ;
  const QString ShortIntegerRegister_SearchCycles_IndividualRepeaterChannel_C3 =  " 6 " ;
  const QString ShortIntegerRegister_SearchCycles_IndividualHoppingChannels_C1 =  " 7 " ;
  const QString ShortIntegerRegister_SearchCycles_SoftKick =  " 8 " ;
  const QString ShortIntegerRegister_SearchCycles_Restart_C5 =  " 9 "; 
  const QString ShortIntegerRegister_SetImageAddress =  " 10 " ;
  const QString ShortIntegerRegister_SetVersionLow_Main =  " 11 "; 
  const QString ShortIntegerRegister_SetVersionHigh_8K =  " 12 " ;
  const QString ShortIntegerRegister_BootImage =  " 13 " ;
  const QString ShortIntegerRegister_SyncWord =  " 14 " ;
  const QString ShortIntegerRegister_DelayedPackagePrep =  " 15 "; 
  const QString ShortIntegerRegister_SetBasePointer =  " 16 " ;
  const QString ShortIntegerRegister_CurrentNoise =  " 17 " ;
  const QString ShortIntegerRegister_MicroOffset =  " 18 " ;
  const QString ShortIntegerRegister_OscLowCurrentLimitInmA =  " 19 "; 
  const QString ShortIntegerRegister_OscillationDeltaVolts =  " 20 " ;
  const QString ShortIntegerRegister_OscillationOVStartupDelay =  " 21 " ;
  const QString ShortIntegerRegister_OscillationAfterStartupDelay =  " 22 " ;
  const QString ShortIntegerRegister_OscillationLowCurrentOnlyDelay =  " 23 " ;
  const QString ShortIntegerRegister_ReadOnePBRow_1000_or_vOutOV_600 =  " 24 " ;
  const QString ShortIntegerRegister_SetPBByte_1000_or_iOutOV_600 =  " 25 " ;
  const QString ShortIntegerRegister_FETFailureCount =  " 26 " ;
  const QString ShortIntegerRegister_FETCurrentThreshold =  " 27 "; 
  const QString ShortIntegerRegister_FETDeltaI =  " 28 " ;
  const QString ShortIntegerRegister_GroundShift =  " 29 "; 

  // 1300V registers (used, directed by Anatoli L. to use same numbers)
  const QString ShortIntegerRegister_LowCurrentLimitTo255 =  " 19 " ;
  const QString ShortIntegerRegister_VhvLimitVout =  " 20 " ;
  const QString ShortIntegerRegister_IhvLimitVout =  " 21 " ;
  const QString ShortIntegerRegister_VhvLimitVins =  " 22 " ;
  const QString ShortIntegerRegister_IhvLimitVins =  " 23 " ;

  // 1300V registers (AntiMemoryFix, firmware version suffix 1_D
  const QString ByteRegister_AMFTimer1 = " 114 ";
  const QString ByteRegister_AMFTimer2 = " 115 ";
  const QString ByteRegister_AMF_Timer2MPPOffCyclesAndTimesToCycle = " 116 ";
  const QString ByteRegister_AMF_Debug = " 117 ";

  const QString ShortIntegerRegister_AMFV_OV = " 37 ";
  const QString ShortIntegerRegister_AMFI_OC = " 38 ";

  // 1500V registers
  const QString ShortIntegerRegister_SetVoutLimitCount =  " 33 " ;
  const QString ShortIntegerRegister_SetVoutLimit =  " 34 " ;
  const QString ShortIntegerRegister_SetIoutLimitCount =  " 35 "; 
  const QString ShortIntegerRegister_SetIoutLimit =  " 36 " ;

  const QString ShortIntegerRegister_SetEFInputCurrentThreshold = " 39 ";
  const QString ShortIntegerRegister_IinLimit = " 40 ";

  const QString FloatRegister_DFK0 =  " 1 " ;
  const QString FloatRegister_DFK1 =  " 2 " ;
  const QString FloatRegister_DFK2 =  " 3 " ;
  const QString FloatRegister_DFK3 =  " 4 " ;
  const QString FloatRegister_TK_CUR =  " 5 "; 
  const QString FloatRegister_TK_POW =  " 6 " ;
  const QString FloatRegister_VIN_TURN_ON =  " 7 " ;
  const QString FloatRegister_VIN_SHUT_OFF =  " 8 " ;
  const QString FloatRegister_LinearCoefficientForVOut =  " 10 " ;
  const QString FloatRegister_OffsetForVOut =  " 11 " ;
  const QString FloatRegister_LinearCoefficientForPin_Vin =  " 12 "; 
  const QString FloatRegister_OffsetForPin_Vin =  " 13 " ;
  const QString FloatRegister_LinearCoefficientForIOut =  " 14 "; 
  const QString FloatRegister_OffsetForIOut =  " 15 " ;
  const QString FloatRegister_LinearCoefficientForVin_Vin2 =  " 16 "; 
  const QString FloatRegister_OffsetForVin_Vin2 =  " 17 "; 
  const QString FloatRegister_LinearCoefficientForText =  " 18 " ;
  const QString FloatRegister_OffsetForText =  " 19 " ;
  const QString FloatRegister_LinearCoefficientForTin_Iin2 =  " 20 " ;
  const QString FloatRegister_OffsetForTin_Iin2 =  " 21 " ;
  const QString FloatRegister_LinearCoefficientForIin1 =  " 22 "; 
  const QString FloatRegister_OffsetForIin1 =  " 23 " ;
  const QString FloatRegister_Vref0 =  " 24 " ;
  const QString FloatRegister_Kvref =  " 25 " ;
  const QString FloatRegister_T0 =  " 26 " ;

#endif

