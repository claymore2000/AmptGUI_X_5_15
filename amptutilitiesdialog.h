/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef AMPTUTILITIESDIALOG_H
#define AMPTUTILITIESDIALOG_H

#include <QWidget>
#include "amptIntelHexFile.h"


QT_BEGIN_NAMESPACE
class QCheckBox;
class QLabel;
class QErrorMessage;
class QPushButton;
class QPlainTextEdit;
class QFile;
class QTextStream;
class QComboBox;
QT_END_NAMESPACE

class DialogOptionsWidget;

class AmptUtilitiesDialog : public QWidget
{
    Q_OBJECT

public:
    AmptUtilitiesDialog(QWidget *parent = nullptr);
    void closeEvent(QCloseEvent *event);
signals:
    void publishAmptUtilitiesDialogError( const QString s);
    void AmptUtilitiesDialogClosingSignal( void );
    void AmptUtilitiesDialogRequestAllKnownMACs( void );
    void AmptUtilitiesDialogCommandToSendToGateway( const QString s);
    void AmptUtilitiesDialogRequestMACOTAData(const QString mac);
    void AmptUtilitiesDialogEndRequestMACOTAData(void);

public slots:
    void handlePublishOneMACOTAData(QStringList s);


private slots:
    void set8KImageChannel( void );
    void set8KImageGWAddress( void );
    void set8KImageEDAddress( void );
    void set8KImageMACAddress( void );
    void send8KImageTryBeforeYouBuy( void );

    void setMainImageChannel( void );
    void setMainImageGWAddress( void );
    void setMainImageEDAddress( void );
    void setMainImageMACAddress( void );
    void sendMainImageTryBeforeYouBuy( void );

    void send8KImageRestartCommand( void );
    void sendMainImageRestartCommand( void );

    void setOVToOutputVoltageMPPSetting( void );
    void setOVToOutputVoltageOCSetting( void );
    void setOVToOutputVoltageMACAddress( void );
    void setOVToOutputVoltageFileName( void );

    void sendBeginOVToOutputVoltage( void );
    void sendCancelOVToOutputVoltage( void );

    void setOCToOutputCurrentMPPSetting( void );
    void setOCToOutputCurrentOVSetting( void );
    void setOCToOutputCurrentMACAddress( void );
    void setOCToOutputCurrentFileName( void );

    void sendBeginOCToOutputCurrent( void );
    void sendCancelOCToOutputCurrent( void );

    void setBOAIntelHexFile( void );
    void setBOAIntelHexFileVersion( void );
    void setBOAMainImageChannel( void );
    void setBOA8KImageChannel( void );
    void setBOAParametersToSetAfterSuccessFile( void );
    void setMACsToBOAFile( void );
    void handleCreateValidBOAChannels( void );

    void sendBeginBOA( void );
    void sendCancelBOA( void );




    // LBC void setText();
    // void setMultiLineText();
    void setColor();
    void setFont();
    void setExistingDirectory();
    void setOpenFileName();
    void setOpenFileNames();
    void setSaveFileName();
    void criticalMessage();
    void informationMessage();
    void questionMessage();
    void warningMessage();
    void errorMessage();

    void handlePublishAllKnownMACs(QStringList s);

private:
    void handlePublishOneMACOTAOVData(QStringList s);
    void handlePublishOneMACOTAOCData(QStringList s);

    QPushButton *try8KImageBeforeYouBuyButton;
    QPushButton *tryMainImageBeforeYouBuyButton;
    QPushButton *try8KImageBeforeYouBuyRestartButton;
    QPushButton *tryMainImageBeforeYouBuyRestartButton;

    QPushButton *ovToOutputVoltageBeginButton;
    QPushButton *ovToOutputVoltageCancelButton;

    QPushButton *ocToOutputCurrentBeginButton;
    QPushButton *ocToOutputCurrentCancelButton;

    QPushButton *boaBeginButton;
    QPushButton *boaCancelButton;

    bool allEightKImageTryBeforeBuyParametersSet( void );
    bool allMainImageTryBeforeBuyParametersSet( void );
    bool allOVToOutputVoltageParametersSet( void );
    bool allOCToOutputCurrentParametersSet( void );

    bool allBOAParametersSet( void );

    QLabel *eightKImageChannelLabel;
    QLabel *eightKImageGWAddressLabel;
    QLabel *eightKImageEDAddressLabel;
    QLabel *eightKImageMACAddressLabel;

    QLabel *mainImageChannelLabel;
    QLabel *mainImageGWAddressLabel;
    QLabel *mainImageEDAddressLabel;
    QLabel *mainImageMACAddressLabel;

    QLabel *ovToOutputVoltageMACAddressLabel;
    QLabel *ovToOutputVoltageMPPSettingLabel;
    QLabel *ovToOutputVoltageOCSettingLabel;
    QLabel *ovToOutputVoltageToFileLabel;
    QLabel *ovToOutputVoltageProgressLabel;
    int m_ovValue;

    QLabel *ocToOutputCurrentMACAddressLabel;
    QLabel *ocToOutputCurrentMPPSettingLabel;
    QLabel *ocToOutputCurrentOVSettingLabel;
    QLabel *ocToOutputCurrentToFileLabel;
    QLabel *ocToOutputCurrentProgressLabel;
    int m_ocValue;
    int m_oneValueIndex; // indicates whether OC or OV is being checked

    QLabel *boaMACsToBOAFileLabel;
    QLabel *boaMainImageChannelLabel;
    QLabel *boa8KImageChannelLabel;
    QLabel *boaIntelHexFileLabel;
    QLabel *boaIntelHexFileVersionSuffixLabel;
    QLabel *boaParametersToSetAfterSuccessLabel;
    QLabel *boaProgressLabel;

    AmptIntelHexFile *boaHexFile;
    QString boaIntelHexFileName;


    QFile *m_outputFile;
    QTextStream *m_outputTextStream;

    bool oneValueReached;

    QStringList knownMACs;
    // QLabel *eightKImageSendTryBeforeYouBuyLabel;
    // LBC QLabel *textLabel;
    //QLabel *multiLineTextLabel;
    QPlainTextEdit *eightKImageProgressLog;
    QPlainTextEdit *mainImageProgressLog;
    QPlainTextEdit *ovToOutputVoltageProgressLog;
    QPlainTextEdit *ocToOutputCurrentProgressLog;
    QPlainTextEdit *boaProgressLog;;

    QString boaMainImageChannel{"0"};
    QString boa8KImageChannel{"0"};

    QStringList validChannelsStringList;


    QLabel *colorLabel;
    QLabel *fontLabel;
    QLabel *directoryLabel;
    QLabel *openFileNameLabel;
    QLabel *openFileNamesLabel;
    QLabel *saveFileNameLabel;
    QLabel *criticalLabel;
    QLabel *informationLabel;
    QLabel *questionLabel;
    QLabel *warningLabel;
    QLabel *errorLabel;
    QErrorMessage *errorMessageDialog;
    DialogOptionsWidget *fileDialogOptionsWidget;
    DialogOptionsWidget *colorDialogOptionsWidget;
    DialogOptionsWidget *fontDialogOptionsWidget;
    QString openFilesPath;
};

#endif
