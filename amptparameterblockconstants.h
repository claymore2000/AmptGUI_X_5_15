#ifndef AMPTPARAMETERBLOCKCONSTANTS_H
#define AMPTPARAMETERBLOCKCONSTANTS_H
#include <QString>

static const int ParametersReadFromUnknown = -1;
static const int ParametersReadFromMemory = 0;
static const int ParametersReadFromFlash  = 1;
static const int ParametersReadFromGateway = 3;
static const int ParametersReadFromTimeout = 4;

static const QString Family600V("600V");
static const QString Family1000V("1000V");
static const QString Family1300V("1300V");
static const QString Family1300V_2nd("1300V-2nd");
static const QString Family1500V("1500V");
static const QString Family1500V_2nd("1500V-2nd");
static const QString Family1500V_30("1500V-30");
static const QString Family600V_V2("600V-V2");
static const QString Family600V_V2_2nd("600V-V2-2nd");

static const QString ReadFromFlash("Flash");
static const QString ReadFromMemory("Memory");

static const int Family600V_Shunt = 0;
static const int Family1000V_Shunt = 20;
static const int Family1300V_Shunt = 26;
static const int Family1300V_2nd_Shunt = 27; // (Just for AMPT GUI)
static const int Family1500V_Shunt = 30;
static const int Family1500V_2nd_Shunt = 31; // (Just for AMPT GUI)
static const int Family600V_V2_Shunt = 12;
static const int Family600V_V2_2nd_Shunt = 13; // (Just for AMPT GUI)
static const int Family1500V_30_Shunt = 33;

#endif // AMPTPARAMETERBLOCKCONSTANTS_H
