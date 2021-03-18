#-------------------------------------------------
#
# Project created by QtCreator 2018-02-05T10:37:49
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# LBC added 08022019

# Version updated after port to new windows laptop from 10.41. (03182021)
VERSION = 10.41.5




TARGET = AmptGUI_X
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# LBC This allows version to be accessible in C++ code
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

# LBC added to compile Dr. L's Version
# CONFIG += static

SOURCES += \
    amptIntelHexFile.cpp \
    amptutilitiesdialog.cpp \
    batchCommandsThread.cpp \
    defaultParameterBlockValues.cpp \
        main.cpp \
        amptgui_x.cpp \
    gatewayThread.cpp \
    outputLoggerThread.cpp \
    parseOTADataThread.cpp \
    receiveOTADataThread.cpp \
    amptgui_x_utilities.cpp \
    loggerThread.cpp \
    parseParameterBlockThread.cpp \
    amptTimer.cpp \
    parseGatewayParameterBlockThread.cpp \
    endDeviceParameterBlockInfoThread.cpp \
    checkGatewayCommandThread.cpp \
    configurationThread.cpp \
    gatewayValuesChangesTracked.cpp \
    powerCntrlValuesChangesTracked.cpp \
    screenshot.cpp \
    valueChangesTracked.cpp \
    linearCoeffsValueChangesTracked.cpp \
    tempCntrlValueChangesTracked.cpp \
    fineCntrlValuesChangesTracked.cpp \
    radioValueChangesTracked.cpp \
    edSettingsValuesChangesTracked.cpp \
    protections1300VValueChangesTracked.cpp \
    endDeviceValuesChangesTracked.cpp

HEADERS += \
    amptConfigurationKeys.h \
    amptIntelHexFile.h \
    amptbuildtime.h \
        amptgui_x.h \
    amptutilitiesdialog.h \
    batchCommandsThread.h \
    defaultParameterBlockValues.h \
    gatewayThread.h \
    outputLoggerThread.h \
    parseOTADataThread.h \
    receiveOTADataThread.h \
    amptgui_x_utilities.h \
    amptgui_x_status.h \
    loggerThread.h \
    amptparameterblockconstants.h \
    parseParameterBlockThread.h \
    amptTimer.h \
    parseGatewayParameterBlockThread.h \
    gatewayParameterBlockKeyNames.h \
    endDeviceParameterBlockInfoThread.h \
    checkGatewayCommandThread.h \
    parameter_block_1300V.h \
    dataTypeMappings.h \
    configurationThread.h \
    gatewayValuesChangesTracked.h \
    powerCntrlValuesChangesTracked.h \
    screenshot.h \
    valueChangesTracked.h \
    linearCoeffsValueChangesTracked.h \
    tempCntrlValueChangesTracked.h \
    fineCntrlValuesChangesTracked.h \
    radioValueChangesTracked.h \
    amptNamedIndexes.h \
    amptNamedLimits.h \
    edSettingsValuesChangesTracked.h \
    amptRegisterConstants.h \
    protections1300VValueChangesTracked.h \
    endDeviceValuesChangesTracked.h

FORMS += \
        amptgui_x.ui

# LBC added to force build time in gui title.
buildtimeTarget.target = amptbuildtime.h
buildtimeTarget.depends = FORCE
# buildtimeTarget.commands = touch $$PWD/amptbuildtime.h
PRE_TARGETDEPS += amptbuildtime.h
QMAKE_EXTRA_TARGETS += buildtimeTarget
