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

#include <QtWidgets>
#include <QFile>
#include <QDateTime>

#include "amptutilitiesdialog.h"

#define MESSAGE \
    AmptUtilitiesDialog::tr("<p>Message boxes have a caption, a text, " \
               "and any number of buttons, each with standard or custom texts." \
               "<p>Click a button to close the message box. Pressing the Esc button " \
               "will activate the detected escape button (if any).")
#define MESSAGE_DETAILS \
    AmptUtilitiesDialog::tr("If a message box has detailed text, the user can reveal it " \
               "by pressing the Show Details... button.")

static const QString formatIt("yyyy/MM/dd hh:mm:ss");

class DialogOptionsWidget : public QGroupBox
{
public:
    explicit DialogOptionsWidget(QWidget *parent = nullptr);

    void addCheckBox(const QString &text, int value);
    void addSpacer();
    int value() const;

private:
    typedef QPair<QCheckBox *, int> CheckBoxEntry;
    QVBoxLayout *layout;
    QList<CheckBoxEntry> checkBoxEntries;

};

DialogOptionsWidget::DialogOptionsWidget(QWidget *parent) :
    QGroupBox(parent) , layout(new QVBoxLayout)
{
    setTitle(AmptUtilitiesDialog::tr("Options"));
    setLayout(layout);
}

void DialogOptionsWidget::addCheckBox(const QString &text, int value)
{
    QCheckBox *checkBox = new QCheckBox(text);
    layout->addWidget(checkBox);
    checkBoxEntries.append(CheckBoxEntry(checkBox, value));
}

void DialogOptionsWidget::addSpacer()
{
    layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding));
}

int DialogOptionsWidget::value() const
{
    int result = 0;
    foreach (const CheckBoxEntry &checkboxEntry, checkBoxEntries)
        if (checkboxEntry.first->isChecked())
            result |= checkboxEntry.second;
    return result;
}

AmptUtilitiesDialog::AmptUtilitiesDialog(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *verticalLayout;
    if (QGuiApplication::styleHints()->showIsFullScreen() || QGuiApplication::styleHints()->showIsMaximized()) {
        QHBoxLayout *horizontalLayout = new QHBoxLayout(this);
        QGroupBox *groupBox = new QGroupBox(QGuiApplication::applicationDisplayName(), this);
        horizontalLayout->addWidget(groupBox);
        verticalLayout = new QVBoxLayout(groupBox);
    } else {
        verticalLayout = new QVBoxLayout(this);
    }
    m_outputFile = nullptr;
    m_outputTextStream = nullptr;
    m_oneValueIndex = -1; // Set to invalid or nonsensical value

    handleCreateValidBOAChannels();

    QToolBox *toolbox = new QToolBox;
    verticalLayout->addWidget(toolbox);

    errorMessageDialog = new QErrorMessage(this);

    int frameStyle = QFrame::Sunken | QFrame::Panel;

    eightKImageChannelLabel = new QLabel;
    eightKImageChannelLabel->setFrameStyle(frameStyle);
    QPushButton *eightKImageChannelButton =
            new QPushButton(tr("8K Image &Channel"));


    eightKImageGWAddressLabel = new QLabel;
    eightKImageGWAddressLabel->setFrameStyle(frameStyle);
    QPushButton *eightKImageGWAddressButton =
            new QPushButton(tr("8K Image &GW Address"));

    eightKImageEDAddressLabel = new QLabel;
    eightKImageEDAddressLabel->setFrameStyle(frameStyle);
    QPushButton *eightKImageEDAddressButton =
            new QPushButton(tr("8K Image &ED Address"));

    eightKImageMACAddressLabel = new QLabel;
    eightKImageMACAddressLabel->setFrameStyle(frameStyle);
    QPushButton *eightKImageMACAddressButton =
            new QPushButton(tr("8K Image &MAC Address"));

    try8KImageBeforeYouBuyButton = new QPushButton(tr("Send Try Before You Buy"));
    try8KImageBeforeYouBuyButton->setEnabled(false);

    try8KImageBeforeYouBuyRestartButton = new QPushButton(tr("Reset"));
    try8KImageBeforeYouBuyRestartButton->setEnabled(false);

    eightKImageProgressLog = new QPlainTextEdit;
    eightKImageProgressLog->setFrameStyle(frameStyle);


    mainImageChannelLabel = new QLabel;
    mainImageChannelLabel->setFrameStyle(frameStyle);
    QPushButton *mainImageChannelButton =
            new QPushButton(tr("Main Image &Channel"));


    mainImageGWAddressLabel = new QLabel;
    mainImageGWAddressLabel->setFrameStyle(frameStyle);
    QPushButton *mainImageGWAddressButton =
            new QPushButton(tr("Main Image &GW Address"));

    mainImageEDAddressLabel = new QLabel;
    mainImageEDAddressLabel->setFrameStyle(frameStyle);
    QPushButton *mainImageEDAddressButton =
            new QPushButton(tr("Main Image &ED Address"));

    mainImageMACAddressLabel = new QLabel;
    mainImageMACAddressLabel->setFrameStyle(frameStyle);
    QPushButton *mainImageMACAddressButton =
            new QPushButton(tr("Main Image &MAC Address"));

    tryMainImageBeforeYouBuyButton = new QPushButton(tr("Send Try Before You Buy"));
    tryMainImageBeforeYouBuyButton->setEnabled(false);

    tryMainImageBeforeYouBuyRestartButton = new QPushButton(tr("Reset"));
    tryMainImageBeforeYouBuyRestartButton->setEnabled(false);

    mainImageProgressLog = new QPlainTextEdit;
    mainImageProgressLog->setFrameStyle(frameStyle);


    ovToOutputVoltageMACAddressLabel = new QLabel;
    ovToOutputVoltageMACAddressLabel->setFrameStyle(frameStyle);
    QPushButton *ovToOutputVoltageMACAddressButton =
            new QPushButton(tr("MAC &Address"));

    ovToOutputVoltageMPPSettingLabel = new QLabel;
    ovToOutputVoltageMPPSettingLabel->setFrameStyle(frameStyle);
    QPushButton *ovToOutputVoltageMPPSettingButton =
            new QPushButton(tr("&MPP Setting"));

    ovToOutputVoltageOCSettingLabel = new QLabel;
    ovToOutputVoltageOCSettingLabel->setFrameStyle(frameStyle);
    QPushButton *ovToOutputVoltageOCSettingButton =
            new QPushButton(tr("OC &Setting"));

    ovToOutputVoltageToFileLabel = new QLabel;
    ovToOutputVoltageToFileLabel->setFrameStyle(frameStyle);
    QPushButton *ovToOutputVoltageToFileButton =
            new QPushButton(tr("Save To &File"));

    ovToOutputVoltageBeginButton = new QPushButton(tr("&Begin OV -> Output Voltage Mapping"));
    ovToOutputVoltageBeginButton->setEnabled(false);

    ovToOutputVoltageProgressLog = new QPlainTextEdit;
    ovToOutputVoltageProgressLog->setFrameStyle(frameStyle);

    ovToOutputVoltageCancelButton =  new QPushButton(tr("&Cancel Mapping Process"));
    ovToOutputVoltageCancelButton->setEnabled(false);


    ovToOutputVoltageProgressLabel = new QLabel;
    ovToOutputVoltageProgressLabel->setFrameStyle(frameStyle);



    ///////
    ocToOutputCurrentMACAddressLabel = new QLabel;
    ocToOutputCurrentMACAddressLabel->setFrameStyle(frameStyle);
    QPushButton *ocToOutputCurrentMACAddressButton =
            new QPushButton(tr("MAC &Address"));

    ocToOutputCurrentMPPSettingLabel = new QLabel;
    ocToOutputCurrentMPPSettingLabel->setFrameStyle(frameStyle);
    QPushButton *ocToOutputCurrentMPPSettingButton =
            new QPushButton(tr("&MPP Setting"));

    ocToOutputCurrentOVSettingLabel = new QLabel;
    ocToOutputCurrentOVSettingLabel->setFrameStyle(frameStyle);
    QPushButton *ocToOutputCurrentOVSettingButton =
            new QPushButton(tr("OV &Setting"));

    ocToOutputCurrentToFileLabel = new QLabel;
    ocToOutputCurrentToFileLabel->setFrameStyle(frameStyle);
    QPushButton *ocToOutputCurrentToFileButton =
            new QPushButton(tr("Save To &File"));

    ocToOutputCurrentBeginButton = new QPushButton(tr("&Begin OC -> Output Current Mapping"));
    ocToOutputCurrentBeginButton->setEnabled(false);

    ocToOutputCurrentProgressLog = new QPlainTextEdit;
    ocToOutputCurrentProgressLog->setFrameStyle(frameStyle);

    ocToOutputCurrentCancelButton =  new QPushButton(tr("&Cancel Mapping Process"));
    ocToOutputCurrentCancelButton->setEnabled(false);

    ocToOutputCurrentProgressLabel = new QLabel;
    ocToOutputCurrentProgressLabel->setFrameStyle(frameStyle);
    ///////
    boaMACsToBOAFileLabel = new QLabel;
    boaMACsToBOAFileLabel->setFrameStyle(frameStyle);
    QPushButton *boaMACsToBOAFilePushButton = new QPushButton(tr ("MACs to BOA file"));

    boaMainImageChannelLabel = new QLabel;
    boaMainImageChannelLabel->setFrameStyle(frameStyle);
    boaMainImageChannelLabel->setText(boaMainImageChannel);
    QPushButton *boaMainImageChannelButton = new QPushButton(tr ("Main Image &Channel"));

    boa8KImageChannelLabel = new QLabel;
    boa8KImageChannelLabel->setFrameStyle(frameStyle);
    boa8KImageChannelLabel->setText(boa8KImageChannel);
    QPushButton *boa8KImageChannelButton = new QPushButton(tr("8K Image &Channel"));

    boaIntelHexFileLabel = new QLabel;
    boaIntelHexFileLabel->setFrameStyle(frameStyle);
    QPushButton * boaIntelHexFileButton = new QPushButton(tr ("Main Image Hex File"));

    boaIntelHexFileVersionSuffixLabel = new QLabel;
    boaIntelHexFileVersionSuffixLabel->setFrameStyle(frameStyle);
    QPushButton * boaIntelHexFileVersionSuffixButton = new QPushButton("Main Image Version Suffix");

    boaParametersToSetAfterSuccessLabel = new QLabel;
    boaParametersToSetAfterSuccessLabel->setFrameStyle(frameStyle);
    QPushButton * boaParametersToSetAfterSuccessButton = new QPushButton(tr ("Parameters to Set After BOA File"));

    boaBeginButton = new QPushButton(tr("&Begin BOA Process"));
    boaBeginButton->setEnabled(false);

    boaCancelButton =  new QPushButton(tr("&Cancel BOA Process"));
    boaCancelButton->setEnabled(false);

    boaProgressLog = new QPlainTextEdit;
    boaProgressLog->setEnabled(false);

    boaProgressLabel = new QLabel;
    boaProgressLabel->setFrameStyle(frameStyle);


    ///////

    colorLabel = new QLabel;
    colorLabel->setFrameStyle(frameStyle);
    QPushButton *colorButton = new QPushButton(tr("QColorAmptUtilitiesDialog::get&Color()"));

    fontLabel = new QLabel;
    fontLabel->setFrameStyle(frameStyle);
    QPushButton *fontButton = new QPushButton(tr("QFontAmptUtilitiesDialog::get&Font()"));

    directoryLabel = new QLabel;
    directoryLabel->setFrameStyle(frameStyle);
    QPushButton *directoryButton =
            new QPushButton(tr("QFileAmptUtilitiesDialog::getE&xistingDirectory()"));

    openFileNameLabel = new QLabel;
    openFileNameLabel->setFrameStyle(frameStyle);
    QPushButton *openFileNameButton =
            new QPushButton(tr("QFileAmptUtilitiesDialog::get&OpenFileName()"));

    openFileNamesLabel = new QLabel;
    openFileNamesLabel->setFrameStyle(frameStyle);
    QPushButton *openFileNamesButton =
            new QPushButton(tr("QFileAmptUtilitiesDialog::&getOpenFileNames()"));

    saveFileNameLabel = new QLabel;
    saveFileNameLabel->setFrameStyle(frameStyle);
    QPushButton *saveFileNameButton =
            new QPushButton(tr("QFileAmptUtilitiesDialog::get&SaveFileName()"));

    criticalLabel = new QLabel;
    criticalLabel->setFrameStyle(frameStyle);
    QPushButton *criticalButton =
            new QPushButton(tr("QMessageBox::critica&l()"));

    informationLabel = new QLabel;
    informationLabel->setFrameStyle(frameStyle);
    QPushButton *informationButton =
            new QPushButton(tr("QMessageBox::i&nformation()"));

    questionLabel = new QLabel;
    questionLabel->setFrameStyle(frameStyle);
    QPushButton *questionButton =
            new QPushButton(tr("QMessageBox::&question()"));

    warningLabel = new QLabel;
    warningLabel->setFrameStyle(frameStyle);
    QPushButton *warningButton = new QPushButton(tr("QMessageBox::&warning()"));

    errorLabel = new QLabel;
    errorLabel->setFrameStyle(frameStyle);
    QPushButton *errorButton =
            new QPushButton(tr("QErrorMessage::showM&essage()"));

    connect(eightKImageChannelButton, &QAbstractButton::clicked, this, &AmptUtilitiesDialog::set8KImageChannel);
    connect(eightKImageGWAddressButton, &QAbstractButton::clicked, this, &AmptUtilitiesDialog::set8KImageGWAddress);
    connect(eightKImageEDAddressButton, &QAbstractButton::clicked, this, &AmptUtilitiesDialog::set8KImageEDAddress);
    connect(eightKImageMACAddressButton, &QAbstractButton::clicked, this, &AmptUtilitiesDialog::set8KImageMACAddress);

    connect(try8KImageBeforeYouBuyButton, &QAbstractButton::clicked, this, &AmptUtilitiesDialog::send8KImageTryBeforeYouBuy);

    connect(try8KImageBeforeYouBuyRestartButton, &QAbstractButton::clicked, this, &AmptUtilitiesDialog::send8KImageRestartCommand);

    connect(mainImageChannelButton, &QAbstractButton::clicked, this, &AmptUtilitiesDialog::setMainImageChannel);
    connect(mainImageGWAddressButton, &QAbstractButton::clicked, this, &AmptUtilitiesDialog::setMainImageGWAddress);
    connect(mainImageEDAddressButton, &QAbstractButton::clicked, this, &AmptUtilitiesDialog::setMainImageEDAddress);
    connect(mainImageMACAddressButton, &QAbstractButton::clicked, this, &AmptUtilitiesDialog::setMainImageMACAddress);

    connect(tryMainImageBeforeYouBuyButton, &QAbstractButton::clicked, this, &AmptUtilitiesDialog::sendMainImageTryBeforeYouBuy);
    connect(tryMainImageBeforeYouBuyRestartButton, &QAbstractButton::clicked, this, &AmptUtilitiesDialog::sendMainImageRestartCommand);

    connect(ovToOutputVoltageMPPSettingButton, &QAbstractButton::clicked, this, &AmptUtilitiesDialog::setOVToOutputVoltageMPPSetting);
    connect(ovToOutputVoltageMACAddressButton, &QAbstractButton::clicked, this, &AmptUtilitiesDialog::setOVToOutputVoltageMACAddress);
    connect(ovToOutputVoltageOCSettingButton,  &QAbstractButton::clicked, this, &AmptUtilitiesDialog::setOVToOutputVoltageOCSetting);
    connect(ovToOutputVoltageToFileButton, &QAbstractButton::clicked, this, &AmptUtilitiesDialog::setOVToOutputVoltageFileName);

    connect(ovToOutputVoltageBeginButton, &QAbstractButton::clicked, this, &AmptUtilitiesDialog::sendBeginOVToOutputVoltage);
    connect(ovToOutputVoltageCancelButton, &QAbstractButton::clicked, this, &AmptUtilitiesDialog::sendCancelOVToOutputVoltage);

    ///////
    connect(ocToOutputCurrentMPPSettingButton, &QAbstractButton::clicked, this, &AmptUtilitiesDialog::setOCToOutputCurrentMPPSetting);
    connect(ocToOutputCurrentMACAddressButton, &QAbstractButton::clicked, this, &AmptUtilitiesDialog::setOCToOutputCurrentMACAddress);
    connect(ocToOutputCurrentOVSettingButton,  &QAbstractButton::clicked, this, &AmptUtilitiesDialog::setOCToOutputCurrentOVSetting);
    connect(ocToOutputCurrentToFileButton, &QAbstractButton::clicked, this, &AmptUtilitiesDialog::setOCToOutputCurrentFileName);

    connect(ocToOutputCurrentBeginButton, &QAbstractButton::clicked, this, &AmptUtilitiesDialog::sendBeginOCToOutputCurrent);
    connect(ocToOutputCurrentCancelButton, &QAbstractButton::clicked, this, &AmptUtilitiesDialog::sendCancelOCToOutputCurrent);

    ///////
    ///////

    connect(boaIntelHexFileButton, &QAbstractButton::clicked, this, &AmptUtilitiesDialog::setBOAIntelHexFile);
    connect(boaIntelHexFileVersionSuffixButton, &QAbstractButton::clicked, this, &AmptUtilitiesDialog::setBOAIntelHexFileVersion);
    connect(boaParametersToSetAfterSuccessButton, &QAbstractButton::clicked, this, &AmptUtilitiesDialog::setBOAParametersToSetAfterSuccessFile);
    connect(boaMACsToBOAFilePushButton, &QAbstractButton::clicked, this, &AmptUtilitiesDialog::setMACsToBOAFile);
    connect(boaMainImageChannelButton, &QAbstractButton::clicked, this, &AmptUtilitiesDialog::setBOAMainImageChannel);
    connect(boa8KImageChannelButton, &QAbstractButton::clicked, this, &AmptUtilitiesDialog::setBOA8KImageChannel);

    connect(boaBeginButton, &QAbstractButton::clicked, this, &AmptUtilitiesDialog::sendBeginBOA);
    connect(boaCancelButton, &QAbstractButton::clicked, this, &AmptUtilitiesDialog::sendCancelBOA);

    ///////
    ///////

    connect(colorButton, &QAbstractButton::clicked, this, &AmptUtilitiesDialog::setColor);
    connect(fontButton, &QAbstractButton::clicked, this, &AmptUtilitiesDialog::setFont);
    connect(directoryButton, &QAbstractButton::clicked,
            this, &AmptUtilitiesDialog::setExistingDirectory);
    connect(openFileNameButton, &QAbstractButton::clicked,
            this, &AmptUtilitiesDialog::setOpenFileName);
    connect(openFileNamesButton, &QAbstractButton::clicked,
            this, &AmptUtilitiesDialog::setOpenFileNames);
    connect(saveFileNameButton, &QAbstractButton::clicked,
            this, &AmptUtilitiesDialog::setSaveFileName);
    connect(criticalButton, &QAbstractButton::clicked, this, &AmptUtilitiesDialog::criticalMessage);
    connect(informationButton, &QAbstractButton::clicked,
            this, &AmptUtilitiesDialog::informationMessage);
    connect(questionButton, &QAbstractButton::clicked, this, &AmptUtilitiesDialog::questionMessage);
    connect(warningButton, &QAbstractButton::clicked, this, &AmptUtilitiesDialog::warningMessage);
    connect(errorButton, &QAbstractButton::clicked, this, &AmptUtilitiesDialog::errorMessage);


    QWidget *page = new QWidget;
    QGridLayout *layout = new QGridLayout(page);
    layout->setColumnStretch(1, 1);
    layout->setColumnMinimumWidth(1, 1180);

    layout->addWidget(eightKImageChannelButton, 0, 0);
    layout->addWidget(eightKImageChannelLabel, 0, 1);
    layout->addWidget(eightKImageGWAddressButton, 1, 0);
    layout->addWidget(eightKImageGWAddressLabel, 1, 1);
    layout->addWidget(eightKImageEDAddressButton, 2, 0);
    layout->addWidget(eightKImageEDAddressLabel, 2, 1);
    layout->addWidget(eightKImageMACAddressButton, 3, 0);
    layout->addWidget(eightKImageMACAddressLabel, 3, 1);
    layout->addWidget(try8KImageBeforeYouBuyButton,4,0);
    layout->addWidget(try8KImageBeforeYouBuyRestartButton,5,0);

    layout->addWidget(eightKImageProgressLog, 4, 1);
    layout->addItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding), 7, 0);
    toolbox->addItem(page, tr("Try Before You Buy (Main Image to 8K Image)"));
    toolbox->setFixedWidth(720); // LBC this done so one can 'always see button and output text...

    const QString doNotUseNativeDialog = tr("Do not use native dialog");

    page = new QWidget;
    QGridLayout *mainLayout = new QGridLayout(page);
    mainLayout->setColumnStretch(1, 1);
    mainLayout->setColumnMinimumWidth(1, 550);
    mainLayout->addWidget(mainImageChannelButton, 0, 0);
    mainLayout->addWidget(mainImageChannelLabel, 0, 1);
    mainLayout->addWidget(mainImageGWAddressButton, 1, 0);
    mainLayout->addWidget(mainImageGWAddressLabel, 1, 1);
    mainLayout->addWidget(mainImageEDAddressButton, 2, 0);
    mainLayout->addWidget(mainImageEDAddressLabel, 2, 1);
    mainLayout->addWidget(mainImageMACAddressButton, 3, 0);
    mainLayout->addWidget(mainImageMACAddressLabel, 3, 1);
    mainLayout->addWidget(tryMainImageBeforeYouBuyButton,4,0);
    mainLayout->addWidget(tryMainImageBeforeYouBuyRestartButton,5,0);

    mainLayout->addWidget(mainImageProgressLog, 4, 1);
    mainLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding), 7, 0);
    toolbox->addItem(page, tr("Try Before You Buy (8K Image to Main Image)"));

    page = new QWidget;
    layout = new QGridLayout(page);
    layout->setColumnStretch(1, 1);
    layout->setColumnMinimumWidth(1, 550);
    layout->addWidget(ovToOutputVoltageMACAddressButton, 0, 0);
    layout->addWidget(ovToOutputVoltageMACAddressLabel, 0, 1);
    layout->addWidget(ovToOutputVoltageMPPSettingButton, 1, 0);
    layout->addWidget(ovToOutputVoltageMPPSettingLabel, 1, 1);
    layout->addWidget(ovToOutputVoltageOCSettingButton, 2,0);
    layout->addWidget(ovToOutputVoltageOCSettingLabel, 2, 1);
    layout->addWidget(ovToOutputVoltageToFileButton, 3, 0);
    layout->addWidget(ovToOutputVoltageToFileLabel, 3, 1);
    layout->addWidget(ovToOutputVoltageBeginButton, 4, 0);
    layout->addWidget(ovToOutputVoltageProgressLog, 4, 1);
    layout->addWidget(ovToOutputVoltageCancelButton, 5, 0);
    layout->addWidget(ovToOutputVoltageProgressLabel, 5, 1);

    mainLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding), 7, 0);
    toolbox->addItem(page, tr("Generate OV Settings -> Measured Output Voltage "));

    page = new QWidget;
    layout = new QGridLayout(page);
    layout->setColumnStretch(1, 1);
    layout->setColumnMinimumWidth(1, 550);
    layout->addWidget(ocToOutputCurrentMACAddressButton, 0, 0);
    layout->addWidget(ocToOutputCurrentMACAddressLabel, 0, 1);
    layout->addWidget(ocToOutputCurrentMPPSettingButton, 1, 0);
    layout->addWidget(ocToOutputCurrentMPPSettingLabel, 1, 1);
    layout->addWidget(ocToOutputCurrentOVSettingButton, 2,0);
    layout->addWidget(ocToOutputCurrentOVSettingLabel, 2, 1);
    layout->addWidget(ocToOutputCurrentToFileButton, 3, 0);
    layout->addWidget(ocToOutputCurrentToFileLabel, 3, 1);
    layout->addWidget(ocToOutputCurrentBeginButton, 4, 0);
    layout->addWidget(ocToOutputCurrentProgressLog, 4, 1);
    layout->addWidget(ocToOutputCurrentCancelButton, 5, 0);
    layout->addWidget(ocToOutputCurrentProgressLabel, 5, 1);

    mainLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding), 7, 0);
    toolbox->addItem(page, tr("Generate OC Settings -> Measured Output Current "));

    page = new QWidget;
    layout = new QGridLayout(page);
    layout->setColumnStretch(1,1);
    layout->setColumnMinimumWidth(1,550);
    layout->addWidget(boaMACsToBOAFilePushButton, 0, 0);
    layout->addWidget(boaMACsToBOAFileLabel, 0, 1);
    layout->addWidget(boaMainImageChannelButton, 1, 0);
    layout->addWidget(boaMainImageChannelLabel, 1, 1);
    layout->addWidget(boa8KImageChannelButton, 2, 0);
    layout->addWidget(boa8KImageChannelLabel, 2, 1);
    layout->addWidget(boaIntelHexFileButton, 3, 0);
    layout->addWidget(boaIntelHexFileLabel, 3, 1);
    layout->addWidget(boaIntelHexFileVersionSuffixButton, 4, 0);
    layout->addWidget(boaIntelHexFileVersionSuffixLabel, 4, 1);
    layout->addWidget(boaParametersToSetAfterSuccessButton, 5, 0);
    layout->addWidget(boaParametersToSetAfterSuccessLabel, 5, 1);
    layout->addWidget(boaBeginButton, 6, 0);
    layout->addWidget(boaProgressLog, 6, 1);
    layout->addWidget(boaCancelButton, 7, 0);
    layout->addWidget(boaProgressLabel, 7, 1);

    mainLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding), 8, 0);
    toolbox->addItem(page, tr("Boot Over the Air "));

    page = new QWidget;
    layout = new QGridLayout(page);
    layout->setColumnStretch(1, 1);
    layout->addWidget(colorButton, 0, 0);
    layout->addWidget(colorLabel, 0, 1);
    colorDialogOptionsWidget = new DialogOptionsWidget;
    colorDialogOptionsWidget->addCheckBox(doNotUseNativeDialog, QColorDialog::DontUseNativeDialog);
    colorDialogOptionsWidget->addCheckBox(tr("Show alpha channel") , QColorDialog::ShowAlphaChannel);
    colorDialogOptionsWidget->addCheckBox(tr("No buttons") , QColorDialog::NoButtons);
    layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding), 1, 0);
    layout->addWidget(colorDialogOptionsWidget, 2, 0, 1 ,2);

    toolbox->addItem(page, tr("Color Dialog"));

    page = new QWidget;
    layout = new QGridLayout(page);
    layout->setColumnStretch(1, 1);
    layout->addWidget(fontButton, 0, 0);
    layout->addWidget(fontLabel, 0, 1);
    fontDialogOptionsWidget = new DialogOptionsWidget;
    fontDialogOptionsWidget->addCheckBox(doNotUseNativeDialog, QFontDialog::DontUseNativeDialog);
    fontDialogOptionsWidget->addCheckBox(tr("Show scalable fonts"), QFontDialog::ScalableFonts);
    fontDialogOptionsWidget->addCheckBox(tr("Show non scalable fonts"), QFontDialog::NonScalableFonts);
    fontDialogOptionsWidget->addCheckBox(tr("Show monospaced fonts"), QFontDialog::MonospacedFonts);
    fontDialogOptionsWidget->addCheckBox(tr("Show proportional fonts"), QFontDialog::ProportionalFonts);
    fontDialogOptionsWidget->addCheckBox(tr("No buttons") , QFontDialog::NoButtons);
    layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding), 1, 0);
    layout->addWidget(fontDialogOptionsWidget, 2, 0, 1 ,2);
    toolbox->addItem(page, tr("Font Dialog"));

    page = new QWidget;
    layout = new QGridLayout(page);
    layout->setColumnStretch(1, 1);
    layout->addWidget(directoryButton, 0, 0);
    layout->addWidget(directoryLabel, 0, 1);
    layout->addWidget(openFileNameButton, 1, 0);
    layout->addWidget(openFileNameLabel, 1, 1);
    layout->addWidget(openFileNamesButton, 2, 0);
    layout->addWidget(openFileNamesLabel, 2, 1);
    layout->addWidget(saveFileNameButton, 3, 0);
    layout->addWidget(saveFileNameLabel, 3, 1);
    fileDialogOptionsWidget = new DialogOptionsWidget;
    fileDialogOptionsWidget->addCheckBox(doNotUseNativeDialog, QFileDialog::DontUseNativeDialog);
    fileDialogOptionsWidget->addCheckBox(tr("Show directories only"), QFileDialog::ShowDirsOnly);
    fileDialogOptionsWidget->addCheckBox(tr("Do not resolve symlinks"), QFileDialog::DontResolveSymlinks);
    fileDialogOptionsWidget->addCheckBox(tr("Do not confirm overwrite"), QFileDialog::DontConfirmOverwrite);
    fileDialogOptionsWidget->addCheckBox(tr("Do not use sheet"), QFileDialog::DontUseSheet);
    fileDialogOptionsWidget->addCheckBox(tr("Readonly"), QFileDialog::ReadOnly);
    fileDialogOptionsWidget->addCheckBox(tr("Hide name filter details"), QFileDialog::HideNameFilterDetails);
    fileDialogOptionsWidget->addCheckBox(tr("Do not use custom directory icons (Windows)"), QFileDialog::DontUseCustomDirectoryIcons);
    layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding), 4, 0);
    layout->addWidget(fileDialogOptionsWidget, 5, 0, 1 ,2);
    toolbox->addItem(page, tr("File Dialogs"));

    page = new QWidget;
    layout = new QGridLayout(page);
    layout->setColumnStretch(1, 1);
    layout->addWidget(criticalButton, 0, 0);
    layout->addWidget(criticalLabel, 0, 1);
    layout->addWidget(informationButton, 1, 0);
    layout->addWidget(informationLabel, 1, 1);
    layout->addWidget(questionButton, 2, 0);
    layout->addWidget(questionLabel, 2, 1);
    layout->addWidget(warningButton, 3, 0);
    layout->addWidget(warningLabel, 3, 1);
    layout->addWidget(errorButton, 4, 0);
    layout->addWidget(errorLabel, 4, 1);
    layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding), 5, 0);
    toolbox->addItem(page, tr("Message Boxes"));

    setWindowTitle(QGuiApplication::applicationDisplayName());

    emit AmptUtilitiesDialogRequestAllKnownMACs();
}

void AmptUtilitiesDialog::handleCreateValidBOAChannels( void )
{
    validChannelsStringList.push_back("0");
    validChannelsStringList.push_back("1");
    validChannelsStringList.push_back("2");
    validChannelsStringList.push_back("3");
    validChannelsStringList.push_back("4");
    validChannelsStringList.push_back("5");
    validChannelsStringList.push_back("6");
    validChannelsStringList.push_back("7");
    validChannelsStringList.push_back("8");
    validChannelsStringList.push_back("9");
    validChannelsStringList.push_back("10");
    validChannelsStringList.push_back("11");
    validChannelsStringList.push_back("12");
    validChannelsStringList.push_back("13");
    validChannelsStringList.push_back("14");
    validChannelsStringList.push_back("15");
    validChannelsStringList.push_back("248");
    validChannelsStringList.push_back("249");
    validChannelsStringList.push_back("250");
    validChannelsStringList.push_back("251");
    validChannelsStringList.push_back("252");
    validChannelsStringList.push_back("253");

}

void AmptUtilitiesDialog::handlePublishAllKnownMACs(QStringList s)
{
    qDebug() << Q_FUNC_INFO << " INFO: entering ...";

    int sizeOfMACList = s.size();

    for (int i = 0; i < sizeOfMACList; i++)
    {
        qDebug() << Q_FUNC_INFO << " INFO: element " << QString::number(i) << " in MAC list is " << s.at(i);
    }
    knownMACs = s;
}

bool AmptUtilitiesDialog::allEightKImageTryBeforeBuyParametersSet( void )
{
    bool retValue = false;

    if ((eightKImageChannelLabel->text() != "") && (eightKImageGWAddressLabel->text() != "") &&
            (eightKImageEDAddressLabel->text() != "") && (eightKImageMACAddressLabel->text() != ""))
    {
        retValue = true;
    }
    try8KImageBeforeYouBuyButton->setEnabled(retValue);

    return retValue;
}

void AmptUtilitiesDialog::set8KImageChannel( void )
{
//! [0]
    bool ok;
    int i = QInputDialog::getInt(this, tr("8K Channel"),
                                 tr("Channel (decimal):"), 0, 0, 255, 1, &ok);
    if (ok)
    {
        eightKImageChannelLabel->setText(tr("%1").arg(i));
        QString toProgressLog("8K Image expected to be found on channel ");
        toProgressLog += eightKImageChannelLabel->text();
        eightKImageProgressLog->appendPlainText(toProgressLog);
        allEightKImageTryBeforeBuyParametersSet();
    }
//! [0]
}

void AmptUtilitiesDialog::set8KImageGWAddress( void )
{
//! [1]
    bool ok;
    int i = QInputDialog::getInt(this, tr("8K GW Address"),
                                       tr("GW Address (decimal):"), 1, 1, 254, 1, &ok);
    if (ok)
    {
        eightKImageGWAddressLabel->setText(QString("%1").arg(i));
        QString toProgressLog("8K Image expected to be using GW Address ");
        toProgressLog += eightKImageGWAddressLabel->text();
        eightKImageProgressLog->appendPlainText(toProgressLog);
        allEightKImageTryBeforeBuyParametersSet();
    }
//! [1]
}

void AmptUtilitiesDialog::set8KImageEDAddress( void )
{
//! [1]
    bool ok;
    int i = QInputDialog::getInt(this, tr("8K ED Address"),
                                       tr("ED Address (decimal):"), 2, 2, 255, 1, &ok);
    if (ok)
    {
        eightKImageEDAddressLabel->setText(QString("%1").arg(i));
        QString toProgressLog("8K Image expected to be using ED Address ");
        toProgressLog += eightKImageEDAddressLabel->text();
        eightKImageProgressLog->appendPlainText(toProgressLog);
        allEightKImageTryBeforeBuyParametersSet();
    }
//! [1]
}

void AmptUtilitiesDialog::set8KImageMACAddress()
{
//! [2]
    bool ok;
    QString item = QInputDialog::getItem(this, tr("MAC Address"),
                                         tr("MAC:"), knownMACs, 0, false, &ok);
    if (ok && !item.isEmpty())
    {
        eightKImageMACAddressLabel->setText(item);
        QString toProgressLog("Try before buy to 8K Image for unit with MAC Address ");
        toProgressLog += eightKImageMACAddressLabel->text();
        eightKImageProgressLog->appendPlainText(toProgressLog);
        allEightKImageTryBeforeBuyParametersSet();
    }
//! [2]
}

void AmptUtilitiesDialog::send8KImageTryBeforeYouBuy( void )
{
    qDebug() << Q_FUNC_INFO << " INFO: Entering ...";
    QString toProgressLog("\n***\n\nAttempting Try before buy to 8K Image for unit with MAC Address ");
    toProgressLog += eightKImageMACAddressLabel->text();
    eightKImageProgressLog->appendPlainText(toProgressLog);
    toProgressLog = "8K Image expected on channel:" + eightKImageChannelLabel->text() + "   GW Address:" + eightKImageGWAddressLabel->text() +
            "   ED Address:" + eightKImageEDAddressLabel->text();
    eightKImageProgressLog->appendPlainText(toProgressLog);
    // Construct command to try before buy to send to end unit
    QString command("s m");
    command += eightKImageMACAddressLabel->text();
    command += " 13 H603F\r\n";
    toProgressLog = "Sending command " + command + " to gateway...";
    eightKImageProgressLog->appendPlainText(toProgressLog);
    emit AmptUtilitiesDialogCommandToSendToGateway(command);

    // Construct commands to set gateway to turn Hopping off, go to correct channel, gw, and end device//

    command = "H 0\r\n";
    toProgressLog = "Sending command " + command + " to gateway...";
    eightKImageProgressLog->appendPlainText(toProgressLog);
    emit AmptUtilitiesDialogCommandToSendToGateway(command);

    command = "h " + eightKImageChannelLabel->text() + "\r\n";
    toProgressLog = "Sending command " + command + " to gateway...";
    eightKImageProgressLog->appendPlainText(toProgressLog);
    emit AmptUtilitiesDialogCommandToSendToGateway(command);

    command = "B ";

    command += QString::number(eightKImageGWAddressLabel->text().toInt(),16).toUpper();
    int edAddrAsHex = eightKImageEDAddressLabel->text().toInt();

    if (edAddrAsHex < 16)
    {
        command += "0";
    }
    command += QString::number(eightKImageEDAddressLabel->text().toInt(),16).toUpper() + "\r\n";

    toProgressLog = "Sending command " + command + " to gateway...";
    eightKImageProgressLog->appendPlainText(toProgressLog);
    emit AmptUtilitiesDialogCommandToSendToGateway(command);

    toProgressLog = "\n***\n\nAttempt Try before buy to 8K Image for unit with MAC Address ";
    toProgressLog += eightKImageMACAddressLabel->text();
    toProgressLog += " finished.";

    eightKImageProgressLog->appendPlainText(toProgressLog);
    try8KImageBeforeYouBuyRestartButton->setEnabled(true);

}

void AmptUtilitiesDialog::send8KImageRestartCommand( void )
{
    qDebug() << Q_FUNC_INFO << " INFO: Entering ...";
    QString toProgressLog("\n***\n\nAttempting Try reset for unit with MAC Address ");

    QString command("r m");
    command += eightKImageMACAddressLabel->text() + "\r\n";
    toProgressLog = "Sending command " + command + " to gateway...";
    eightKImageProgressLog->appendPlainText(toProgressLog);
    emit AmptUtilitiesDialogCommandToSendToGateway(command);
    toProgressLog = "\n***\n\nAttempt restart/reset 8K Image to Main Image for unit with MAC Address ";
    toProgressLog += eightKImageMACAddressLabel->text();

    eightKImageProgressLog->appendPlainText(toProgressLog);
}


bool AmptUtilitiesDialog::allMainImageTryBeforeBuyParametersSet( void )
{
    bool retValue = false;

    if ((mainImageChannelLabel->text() != "") && (mainImageGWAddressLabel->text() != "") &&
            (mainImageEDAddressLabel->text() != "") && (mainImageMACAddressLabel->text() != ""))
    {
        retValue = true;
    }
    tryMainImageBeforeYouBuyButton->setEnabled(retValue);

    return retValue;
}

void AmptUtilitiesDialog::setMainImageChannel( void )
{
//! [0]
    bool ok;
    int i = QInputDialog::getInt(this, tr("Main Image Channel"),
                                 tr("Channel (decimal):"), 0, 0, 255, 1, &ok);
    if (ok)
    {
        mainImageChannelLabel->setText(tr("%1").arg(i));
        QString toProgressLog("Main Image expected to be found on channel ");
        toProgressLog += mainImageChannelLabel->text();
        mainImageProgressLog->appendPlainText(toProgressLog);
        allMainImageTryBeforeBuyParametersSet();
    }
//! [0]
}

void AmptUtilitiesDialog::setMainImageGWAddress( void )
{
//! [1]
    bool ok;
    int i = QInputDialog::getInt(this, tr("Main Image GW Address"),
                                       tr("GW Address (decimal):"), 1, 1, 254, 1, &ok);
    if (ok)
    {
        mainImageGWAddressLabel->setText(QString("%1").arg(i));
        QString toProgressLog("Main Image expected to be using GW Address ");
        toProgressLog += mainImageGWAddressLabel->text();
        mainImageProgressLog->appendPlainText(toProgressLog);
        allMainImageTryBeforeBuyParametersSet();
    }
//! [1]
}

void AmptUtilitiesDialog::setMainImageEDAddress( void )
{
//! [1]
    bool ok;
    int i = QInputDialog::getInt(this, tr("Main Image ED Address"),
                                       tr("ED Address (decimal):"), 2, 2, 255, 1, &ok);
    if (ok)
    {
        mainImageEDAddressLabel->setText(QString("%1").arg(i));
        QString toProgressLog("Main Image expected to be using ED Address ");
        toProgressLog += mainImageEDAddressLabel->text();
        mainImageProgressLog->appendPlainText(toProgressLog);
        allMainImageTryBeforeBuyParametersSet();
    }
//! [1]
}

void AmptUtilitiesDialog::setMainImageMACAddress()
{
//! [2]
    //QStringList items;
    // LBC Loop through known MACs to populate.
    //items << tr("Spring") << tr("Summer") << tr("Fall") << tr("Winter");

    bool ok;
    QString item = QInputDialog::getItem(this, tr("MAC Address"),
                                         tr("MAC:"), knownMACs, 0, false, &ok);
    if (ok && !item.isEmpty())
    {
        mainImageMACAddressLabel->setText(item);
        QString toProgressLog("Try before buy to Main Image for unit with MAC Address ");
        toProgressLog += mainImageMACAddressLabel->text();
        mainImageProgressLog->appendPlainText(toProgressLog);
        allMainImageTryBeforeBuyParametersSet();
    }
//! [2]
}

void AmptUtilitiesDialog::sendMainImageTryBeforeYouBuy( void )
{
    qDebug() << Q_FUNC_INFO << " INFO: Entering ...";
    QString toProgressLog("\n***\n\nAttempting Try before buy to Main Image for unit with MAC Address ");
    toProgressLog += mainImageMACAddressLabel->text();
    mainImageProgressLog->appendPlainText(toProgressLog);
    toProgressLog = "Main Image expected on channel:" + mainImageChannelLabel->text() + "   GW Address:" + mainImageGWAddressLabel->text() +
            "   ED Address:" + mainImageEDAddressLabel->text();
    mainImageProgressLog->appendPlainText(toProgressLog);
    // Construct command to try before buy to send to end unit
    QString command("s m");
    command += mainImageMACAddressLabel->text();
    command += " 13 H83F\r\n";
    toProgressLog = "Sending command " + command + " to gateway...";
    mainImageProgressLog->appendPlainText(toProgressLog);
    emit AmptUtilitiesDialogCommandToSendToGateway(command);


    // Construct commands to set gateway to turn Hopping off, go to correct channel, gw, and end device//

    command = "H 0\r\n";
    toProgressLog = "Sending command " + command + " to gateway...";
    mainImageProgressLog->appendPlainText(toProgressLog);
    emit AmptUtilitiesDialogCommandToSendToGateway(command);

    command = "h " + mainImageChannelLabel->text() + "\r\n";
    toProgressLog = "Sending command " + command + " to gateway...";
    mainImageProgressLog->appendPlainText(toProgressLog);
    emit AmptUtilitiesDialogCommandToSendToGateway(command);

    command = "B ";

    command += QString::number(mainImageGWAddressLabel->text().toInt(),16).toUpper();
    int edAddrAsHex = mainImageEDAddressLabel->text().toInt();

    if (edAddrAsHex < 16)
    {
        command += "0";
    }
    command += QString::number(mainImageEDAddressLabel->text().toInt(),16).toUpper() + "\r\n";

    toProgressLog = "Sending command " + command + " to gateway...";
    mainImageProgressLog->appendPlainText(toProgressLog);
    emit AmptUtilitiesDialogCommandToSendToGateway(command);

    toProgressLog = "\n***\n\nAttempt Try before buy to Main Image for unit with MAC Address ";
    toProgressLog += mainImageMACAddressLabel->text();
    toProgressLog += " finished.";

    mainImageProgressLog->appendPlainText(toProgressLog);
    tryMainImageBeforeYouBuyRestartButton->setEnabled(true);

}

void AmptUtilitiesDialog::sendMainImageRestartCommand( void )
{
    qDebug() << Q_FUNC_INFO << " INFO: Entering ...";
    QString toProgressLog("\n***\n\nAttempting Try reset for unit with MAC Address ");

    QString command("r m");
    command += mainImageMACAddressLabel->text() + "\r\n";
    toProgressLog = "Sending command " + command + " to gateway...";
    mainImageProgressLog->appendPlainText(toProgressLog);
    emit AmptUtilitiesDialogCommandToSendToGateway(command);
    toProgressLog = "\n***\n\nAttempt restart/reset Main Image to 8K Image for unit with MAC Address ";
    toProgressLog += mainImageMACAddressLabel->text();

    mainImageProgressLog->appendPlainText(toProgressLog);
}

bool AmptUtilitiesDialog::allOVToOutputVoltageParametersSet( void )
{
    bool retValue = false;

    if ((ovToOutputVoltageMPPSettingLabel->text() != "") && (ovToOutputVoltageMACAddressLabel->text() != "") &&
            (ovToOutputVoltageOCSettingLabel->text() != "") && (ovToOutputVoltageToFileLabel->text() != ""))
    {
        retValue = true;
    }
    ovToOutputVoltageBeginButton->setEnabled(retValue);
    ovToOutputVoltageCancelButton->setEnabled(retValue);
    // LBC MAKE SURE CANCEL ENDS any running mapping and on successful end, disable cancel ...

    return retValue;
}

void AmptUtilitiesDialog::setOVToOutputVoltageMPPSetting( void )
{
    qDebug() << Q_FUNC_INFO << " Entering ...";
    QStringList items;
    items << tr("Off") << tr("On");

    bool ok;
    QString item = QInputDialog::getItem(this, tr("MPP Setting"),
                                         tr("MPP:"), items, 0, false, &ok);
    if (ok && !item.isEmpty())
    {
        ovToOutputVoltageMPPSettingLabel->setText(item);
        QString toProgressLog("OV to Output Voltage will use MPP:");
        toProgressLog += ovToOutputVoltageMPPSettingLabel->text();
        ovToOutputVoltageProgressLog->appendPlainText(toProgressLog);
        allOVToOutputVoltageParametersSet();
    }

}

void AmptUtilitiesDialog::setOVToOutputVoltageOCSetting( void )
{
    bool ok;
    int i = QInputDialog::getInt(this, tr("OC Setting"),
                                 tr("OC (decimal):"), 0, 0, 255, 1, &ok);
    if (ok)
    {
        ovToOutputVoltageOCSettingLabel->setText(tr("%1").arg(i));
        QString toProgressLog("OC Setting for the OV to Output Voltage mapping will use ");
        toProgressLog += ovToOutputVoltageOCSettingLabel->text();
        ovToOutputVoltageProgressLog->appendPlainText(toProgressLog);
        allOVToOutputVoltageParametersSet();
    }
}

void AmptUtilitiesDialog::setOVToOutputVoltageMACAddress( void )
{
    bool ok;
    QString item = QInputDialog::getItem(this, tr("MAC Address"),
                                         tr("MAC:"), knownMACs, 0, false, &ok);
    if (ok && !item.isEmpty())
    {
        ovToOutputVoltageMACAddressLabel->setText(item);
        QString toProgressLog("OV to Output Voltage for unit with MAC Address ");
        toProgressLog += ovToOutputVoltageMACAddressLabel->text();
        ovToOutputVoltageProgressLog->appendPlainText(toProgressLog);
        allOVToOutputVoltageParametersSet();
    }
}

void AmptUtilitiesDialog::setOVToOutputVoltageFileName( void )
{
    const QFileDialog::Options options = QFlag(fileDialogOptionsWidget->value());
    QString selectedFilter;
    QString fileName = QFileDialog::getSaveFileName(this,
                                tr("QFileDialog::getSaveFileName()"),
                                ovToOutputVoltageToFileLabel->text(),
                                tr("All Files (*);;Text Files (*.txt)"),
                                &selectedFilter,
                                options);
    if (!fileName.isEmpty())
    {
        ovToOutputVoltageToFileLabel->setText(fileName);
        QString toProgressLog("OV to Output Voltage information will be saved at ");
        toProgressLog += ovToOutputVoltageToFileLabel->text();
        ovToOutputVoltageProgressLog->appendPlainText(toProgressLog);
        allOVToOutputVoltageParametersSet();
    }
}

void AmptUtilitiesDialog::sendBeginOVToOutputVoltage( void )
{
    qDebug() << Q_FUNC_INFO << " INFO: Entering ...";
    QString toProgressLog("\n***\n\nAttempting mapping OV settings to Output Voltage for Optimizer with MAC ");
    toProgressLog +=  ovToOutputVoltageMACAddressLabel->text();
    ovToOutputVoltageProgressLog->appendPlainText(toProgressLog);
    toProgressLog = "OC setting fixed at:" + ovToOutputVoltageOCSettingLabel->text() + "   MPP fixed " + ovToOutputVoltageMPPSettingLabel->text() +
            "  Results found in file :" + ovToOutputVoltageToFileLabel->text();
    ovToOutputVoltageProgressLog->appendPlainText(toProgressLog);

    ovToOutputVoltageBeginButton->setEnabled(false);

    oneValueReached = false;

    QString command("");
    QString commandPrefix("s m");
    commandPrefix += ovToOutputVoltageMACAddressLabel->text();
    QString commandArgs("");


    // Open file for output, if successful, continue, other error out...

    // QFile  outputFile(ovToOutputVoltageToFileLabel->text());
    m_outputFile = new QFile(ovToOutputVoltageToFileLabel->text());

    if ( !m_outputFile->open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QString errString(Q_FUNC_INFO);
        QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
        errString += " ERROR: " + CurrentDateTime + " failed to open file " + ovToOutputVoltageToFileLabel->text() + ", not saving ov to Output Voltage info";
        emit publishAmptUtilitiesDialogError(errString);
        qDebug() << errString;
    }
    else
    {
        m_outputTextStream = new QTextStream(m_outputFile);
        *m_outputTextStream << "MAC,Time,Vin1,Vin2,Vout,Iin1,Iin2,Iout,PwrDisp,Temp,Status,OV,OC,Module,MPP" << Qt::endl;

        toProgressLog = "\n **** Begin OV to Output Voltage Mapping ****\n";
        ovToOutputVoltageProgressLog->appendPlainText(toProgressLog);

        toProgressLog = "Output file " + ovToOutputVoltageToFileLabel->text() + " sucessfully opened.";
        ovToOutputVoltageProgressLog->appendPlainText(toProgressLog);

        // Set OC
        commandArgs += " 23 b" + ovToOutputVoltageOCSettingLabel->text();
        command = commandPrefix + commandArgs;
        toProgressLog = "Sending command " + command + " to gateway...";
        ovToOutputVoltageProgressLog->appendPlainText(toProgressLog);
        emit AmptUtilitiesDialogCommandToSendToGateway(command);

        // Set MPP
        commandArgs = " 4 b";
        if (ovToOutputVoltageMPPSettingLabel->text() == "Off")
        {
            commandArgs += "0";
        }
        else
        {
            commandArgs += "1";
        }
        command = commandPrefix + commandArgs;
        toProgressLog = "Sending command " + command + " to gateway...";
        ovToOutputVoltageProgressLog->appendPlainText(toProgressLog);
        emit AmptUtilitiesDialogCommandToSendToGateway(command);

        // Set OV to initial value (i.e., 0)
        m_ovValue = 0;
        m_oneValueIndex = 11; // OTA index for OV
        commandArgs = " 22 b" + QString::number(m_ovValue);
        command = commandPrefix + commandArgs;
        toProgressLog = "Sending command " + command + " to gateway...";
        ovToOutputVoltageProgressLog->appendPlainText(toProgressLog);
        emit AmptUtilitiesDialogCommandToSendToGateway(command);

        toProgressLog = "\nReady to being parsing OTA values for MAC:" + ovToOutputVoltageMACAddressLabel->text() + "\n";
        ovToOutputVoltageProgressLog->appendPlainText(toProgressLog);

        emit AmptUtilitiesDialogRequestMACOTAData(ovToOutputVoltageMACAddressLabel->text());

    }
}

void AmptUtilitiesDialog::sendCancelOVToOutputVoltage( void )
{
    qDebug() << Q_FUNC_INFO << " INFO: Entering ...";
    QString toProgressLog = "\n**** Cancelled OV to Output Voltage mapping... ***\n";
    ovToOutputVoltageProgressLog->appendPlainText(toProgressLog);
    ovToOutputVoltageProgressLabel->setText("Cancelled ...");

    *m_outputTextStream << "User Cancelled OV to Output Voltage mapping!" << Qt::endl;

    toProgressLog = "\n***\n\nAttempting Try reset for unit with MAC Address ";

    QString command("r m");
    command += ovToOutputVoltageMACAddressLabel->text() + "\r\n";
    toProgressLog = "Sending command " + command + " to gateway...";
    ovToOutputVoltageProgressLog->appendPlainText(toProgressLog);
    emit AmptUtilitiesDialogCommandToSendToGateway(command);
    toProgressLog = "\n***\n\nAttempt restart/reset unit with MAC Address ";
    toProgressLog += ovToOutputVoltageMACAddressLabel->text();

    ovToOutputVoltageProgressLog->appendPlainText(toProgressLog);
    m_oneValueIndex = -1; // Reset to nonsensical value

    m_outputTextStream->flush();
    m_outputFile->flush();
    m_outputFile->close();
    ovToOutputVoltageCancelButton->setEnabled(false);
    emit AmptUtilitiesDialogEndRequestMACOTAData();
}



///
bool AmptUtilitiesDialog::allOCToOutputCurrentParametersSet( void )
{
    bool retValue = false;

    if ((ocToOutputCurrentMPPSettingLabel->text() != "") && (ocToOutputCurrentMACAddressLabel->text() != "") &&
            (ocToOutputCurrentOVSettingLabel->text() != "") && (ocToOutputCurrentToFileLabel->text() != ""))
    {
        retValue = true;
    }
    ocToOutputCurrentBeginButton->setEnabled(retValue);
    ocToOutputCurrentCancelButton->setEnabled(retValue);
    // LBC MAKE SURE CANCEL ENDS any running mapping and on successful end, disable cancel ...

    return retValue;
}

bool AmptUtilitiesDialog::allBOAParametersSet( void )
{
    bool retValue = false;
    qDebug() << Q_FUNC_INFO << " Entering ...";

    if ((boa8KImageChannelLabel->text() != "") && (boaMainImageChannelLabel->text() != "") &&
            (boaIntelHexFileLabel->text() != ""))
    {
        // Check Image File validity
        // Check Mac file vaidity
        // check parameter file validity
        retValue = true;
        boaBeginButton->setEnabled(true);
        boaCancelButton->setEnabled(true);
        // MAKE SURE CANCEL ENDS any BOA process and "informs" state of optimizers?
    }

    return retValue;
}

void AmptUtilitiesDialog::setOCToOutputCurrentMPPSetting( void )
{
    qDebug() << Q_FUNC_INFO << " Entering ...";
    QStringList items;
    items << tr("Off") << tr("On");

    bool ok;
    QString item = QInputDialog::getItem(this, tr("MPP Setting"),
                                         tr("MPP:"), items, 0, false, &ok);
    if (ok && !item.isEmpty())
    {
        ocToOutputCurrentMPPSettingLabel->setText(item);
        QString toProgressLog("OC to Output Current will use MPP:");
        toProgressLog += ocToOutputCurrentMPPSettingLabel->text();
        ocToOutputCurrentProgressLog->appendPlainText(toProgressLog);
        allOCToOutputCurrentParametersSet();
    }

}

void AmptUtilitiesDialog::setOCToOutputCurrentOVSetting( void )
{
    bool ok;
    int i = QInputDialog::getInt(this, tr("OV Setting"),
                                 tr("OV (decimal):"), 0, 0, 255, 1, &ok);
    if (ok)
    {
        ocToOutputCurrentOVSettingLabel->setText(tr("%1").arg(i));
        QString toProgressLog("OV Setting for the OC to Output Current mapping will use ");
        toProgressLog += ovToOutputVoltageOCSettingLabel->text();
        ocToOutputCurrentProgressLog->appendPlainText(toProgressLog);
        allOCToOutputCurrentParametersSet();
    }
}

void AmptUtilitiesDialog::setOCToOutputCurrentMACAddress( void )
{
    bool ok;
    QString item = QInputDialog::getItem(this, tr("MAC Address"),
                                         tr("MAC:"), knownMACs, 0, false, &ok);
    if (ok && !item.isEmpty())
    {
        ocToOutputCurrentMACAddressLabel->setText(item);
        QString toProgressLog("OC to Output Current for unit with MAC Address ");
        toProgressLog += ocToOutputCurrentMACAddressLabel->text();
        ocToOutputCurrentProgressLog->appendPlainText(toProgressLog);
        allOCToOutputCurrentParametersSet();
    }
}

void AmptUtilitiesDialog::setOCToOutputCurrentFileName( void )
{
    const QFileDialog::Options options = QFlag(fileDialogOptionsWidget->value());
    QString selectedFilter;
    QString fileName = QFileDialog::getSaveFileName(this,
                                tr("QFileDialog::getSaveFileName()"),
                                ovToOutputVoltageToFileLabel->text(),
                                tr("All Files (*);;Text Files (*.txt)"),
                                &selectedFilter,
                                options);
    if (!fileName.isEmpty())
    {
        ocToOutputCurrentToFileLabel->setText(fileName);
        QString toProgressLog("OC to Output Current information will be saved at ");
        toProgressLog += ocToOutputCurrentToFileLabel->text();
        ocToOutputCurrentProgressLog->appendPlainText(toProgressLog);
        allOCToOutputCurrentParametersSet();
    }
}

void AmptUtilitiesDialog::sendBeginOCToOutputCurrent( void )
{
    qDebug() << Q_FUNC_INFO << " INFO: Entering ...";
    QString toProgressLog("\n***\n\nAttempting mapping OC settings to Output Current for Optimizer with MAC ");
    toProgressLog +=  ocToOutputCurrentMACAddressLabel->text();
    ocToOutputCurrentProgressLog->appendPlainText(toProgressLog);
    toProgressLog = "OV setting fixed at:" + ocToOutputCurrentOVSettingLabel->text() + "   MPP fixed " + ocToOutputCurrentMPPSettingLabel->text() +
            "  Results found in file :" + ocToOutputCurrentToFileLabel->text();
    ocToOutputCurrentProgressLog->appendPlainText(toProgressLog);

    ocToOutputCurrentBeginButton->setEnabled(false);

    oneValueReached = false;

    QString command("");
    QString commandPrefix("s m");
    commandPrefix += ocToOutputCurrentMACAddressLabel->text();
    QString commandArgs("");


    // Open file for output, if successful, continue, other error out...

    // QFile  outputFile(ovToOutputVoltageToFileLabel->text());
    m_outputFile = new QFile(ocToOutputCurrentToFileLabel->text());

    if ( !m_outputFile->open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QString errString(Q_FUNC_INFO);
        QString CurrentDateTime = (QDateTime::currentDateTime()).toString(formatIt);
        errString += " ERROR: " + CurrentDateTime + " failed to open file " + ocToOutputCurrentToFileLabel->text() + ", not saving oc to Output Current info";
        emit publishAmptUtilitiesDialogError(errString);
        qDebug() << errString;
    }
    else
    {
        m_outputTextStream = new QTextStream(m_outputFile);
        *m_outputTextStream << "MAC,Time,Vin1,Vin2,Vout,Iin1,Iin2,Iout,PwrDisp,Temp,Status,OV,OC,Module,MPP" << Qt::endl;

        toProgressLog = "\n **** Begin OC to Output Current Mapping ****\n";
        ocToOutputCurrentProgressLog->appendPlainText(toProgressLog);

        toProgressLog = "Output file " + ocToOutputCurrentToFileLabel->text() + " sucessfully opened.";
        ocToOutputCurrentProgressLog->appendPlainText(toProgressLog);

        // Set OC
        commandArgs += " 22 b" + ocToOutputCurrentOVSettingLabel->text();
        command = commandPrefix + commandArgs;
        toProgressLog = "Sending command " + command + " to gateway...";
        ocToOutputCurrentProgressLog->appendPlainText(toProgressLog);
        emit AmptUtilitiesDialogCommandToSendToGateway(command);

        // Set MPP
        commandArgs = " 4 b";
        if (ocToOutputCurrentMPPSettingLabel->text() == "Off")
        {
            commandArgs += "0";
        }
        else
        {
            commandArgs += "1";
        }
        command = commandPrefix + commandArgs;
        toProgressLog = "Sending command " + command + " to gateway...";
        ocToOutputCurrentProgressLog->appendPlainText(toProgressLog);
        emit AmptUtilitiesDialogCommandToSendToGateway(command);

        // Set OV to initial value (i.e., 0)
        m_ocValue = 0;
        m_oneValueIndex = 12; // Set to OTA index for oc

        commandArgs = " 23 b" + QString::number(m_ocValue);
        command = commandPrefix + commandArgs;
        toProgressLog = "Sending command " + command + " to gateway...";
        ocToOutputCurrentProgressLog->appendPlainText(toProgressLog);
        emit AmptUtilitiesDialogCommandToSendToGateway(command);

        toProgressLog = "\nReady to being parsing OTA values for MAC:" + ocToOutputCurrentMACAddressLabel->text() + "\n";
        ocToOutputCurrentProgressLog->appendPlainText(toProgressLog);

        emit AmptUtilitiesDialogRequestMACOTAData(ocToOutputCurrentMACAddressLabel->text());

    }
}

void AmptUtilitiesDialog::sendCancelOCToOutputCurrent( void )
{
    qDebug() << Q_FUNC_INFO << " INFO: Entering ...";
    QString toProgressLog = "\n**** Cancelled OC to Output Current mapping... ***\n";
    ocToOutputCurrentProgressLog->appendPlainText(toProgressLog);
    ocToOutputCurrentProgressLabel->setText("Cancelled ...");

    *m_outputTextStream << "User Cancelled OC to Output Current mapping!" << Qt::endl;

    toProgressLog = "\n***\n\nAttempting Try reset for unit with MAC Address ";

    QString command("r m");
    command += ocToOutputCurrentMACAddressLabel->text() + "\r\n";
    toProgressLog = "Sending command " + command + " to gateway...";
    ocToOutputCurrentProgressLog->appendPlainText(toProgressLog);
    emit AmptUtilitiesDialogCommandToSendToGateway(command);
    toProgressLog = "\n***\n\nAttempt restart/reset unit with MAC Address ";
    toProgressLog += ocToOutputCurrentMACAddressLabel->text();

    ocToOutputCurrentProgressLog->appendPlainText(toProgressLog);

    m_oneValueIndex = -1; // Reset to nonsensical value

    m_outputTextStream->flush();
    m_outputFile->flush();
    m_outputFile->close();
    ocToOutputCurrentCancelButton->setEnabled(false);
    emit AmptUtilitiesDialogEndRequestMACOTAData();
}

void AmptUtilitiesDialog::setMACsToBOAFile( void )
{
    qDebug() << Q_FUNC_INFO << " INFO: Entering ...";
    allBOAParametersSet();
}

void AmptUtilitiesDialog::setBOAIntelHexFile( void )
{
    qDebug() << Q_FUNC_INFO << " INFO: Entering ...";
    const QFileDialog::Options options = QFlag(fileDialogOptionsWidget->value());
    QString selectedFilter = tr("HEX (*.hex)");
    QString fileName = QFileDialog::getOpenFileName(this,
                                tr("Main Image Hex file to BOA"),
                                boaIntelHexFileLabel->text(),
                                                    tr("(Hex files (*.hex)"),
                                //tr("All Files (*);;Text Files (*.txt)"),
                                &selectedFilter,
                                options);
    if (!fileName.isEmpty())
    {
        qDebug() << Q_FUNC_INFO << " hex file name: " << fileName;
        boaIntelHexFileName = fileName;
        boaIntelHexFileLabel->setText(fileName);
        QString toProgressLog("Main Image Hex File set to ");
        toProgressLog += boaIntelHexFileLabel->text();
        boaProgressLog->appendPlainText(toProgressLog);
    }
    else
    {
        qDebug() << Q_FUNC_INFO << " ERROR file name is empty ...";
    }
    allBOAParametersSet();
}

void AmptUtilitiesDialog::setBOAIntelHexFileVersion( void )
{
    QStringList empty;
     qDebug() << Q_FUNC_INFO << " INFO: Entering ...";
     bool ok;
     QString item = QInputDialog::getItem(this, tr("Main Image Hex File Version"),
                                          tr("Version:"), empty, 0, false, &ok);
     if (ok && !item.isEmpty())
     {
         QString toProgressLog("Main Image Hex File Version set to ");
         boaIntelHexFileVersionSuffixLabel->setText(item);
         toProgressLog += boaIntelHexFileVersionSuffixLabel->text();
         boaProgressLog->appendPlainText(toProgressLog);
         allBOAParametersSet();
     }
}

void AmptUtilitiesDialog::setBOAParametersToSetAfterSuccessFile( void )
{
    qDebug() << Q_FUNC_INFO << " INFO: Entering ...";
    const QFileDialog::Options options = QFlag(fileDialogOptionsWidget->value());
    QString selectedFilter;
    QString fileName = QFileDialog::getOpenFileName(this,
                                tr("Parameters to set after sucessful BOA file"),
                                boaParametersToSetAfterSuccessLabel->text(),
                                tr("All Files (*);;Text Files (*.txt)"),
                                &selectedFilter,
                                options);
    if (!fileName.isEmpty())
    {
        boaParametersToSetAfterSuccessLabel->setText(fileName);
    }

    allBOAParametersSet();
}

void AmptUtilitiesDialog::setBOAMainImageChannel( void )
{
    qDebug() << Q_FUNC_INFO << " INFO: Entering ...";

    bool ok;
    QString item = QInputDialog::getItem(this, tr("Main Image Channel"),
                                         tr("Channel:"), validChannelsStringList, 0, false, &ok);
    if (ok && !item.isEmpty())
    {
        QString toProgressLog("Main Image Channel set to ");

        boaMainImageChannelLabel->setText(item);
        toProgressLog += boaMainImageChannelLabel->text();
        boaProgressLog->appendPlainText(toProgressLog);
        allBOAParametersSet();
    }
}

void AmptUtilitiesDialog::setBOA8KImageChannel( void )
{
    qDebug() << Q_FUNC_INFO << " INFO: Entering ...";

    bool ok;
    QString item = QInputDialog::getItem(this, tr("8K Image Channel"),
                                         tr("Channel:"), validChannelsStringList, 0, false, &ok);
    if (ok && !item.isEmpty())
    {
        QString toProgressLog("8K Image Channel set to ");

        boa8KImageChannelLabel->setText(item);
        toProgressLog += boa8KImageChannelLabel->text();
        boaProgressLog->appendPlainText(toProgressLog);
        allBOAParametersSet();
    }
}

void AmptUtilitiesDialog::sendBeginBOA( void )
{
    qDebug() << Q_FUNC_INFO << " INFO: Entering ...";
    QString toProgressLog("\n***\n\nAttempting BOA ...\n\nFirst, validating hex file ...");
    boaProgressLog->appendPlainText(toProgressLog);
    //toProgressLog = "OV setting fixed at:" + ocToOutputCurrentOVSettingLabel->text() + "   MPP fixed " + ocToOutputCurrentMPPSettingLabel->text() +
    //        "  Results found in file :" + ocToOutputCurrentToFileLabel->text();
    //boaProgressLog->appendPlainText(toProgressLog);



    boaHexFile = new AmptIntelHexFile(boaIntelHexFileName);

    boaHexFile->ValidAmptIntelHexFile();

    // IS hex file valid?
    // If valid, is there a MAC file, if so validate it
    // If valid, is there a parameter file
    // if valid, begin boa ...
    boaBeginButton->setEnabled(false);
    boaCancelButton->setEnabled(true);

    // Make sure hopping is off.
    //
}

void AmptUtilitiesDialog::sendCancelBOA( void )
{
    qDebug() << Q_FUNC_INFO << " INFO: Entering ...";
    QString toProgressLog("\n***\n\nCancelling BOA ...");
    boaProgressLog->appendPlainText(toProgressLog);
    // Set Gateway back to flash settings
    boaCancelButton->setEnabled(false);
}

//////
void AmptUtilitiesDialog::handlePublishOneMACOTAOVData(QStringList s)
{
    qDebug() << Q_FUNC_INFO << " Entering with MAC " << s.at(0) << " length is " << s.length() << " OTA index " << m_oneValueIndex;
    static QTime timeOneValueReached;

    if ((oneValueReached == false) && ((s.at(m_oneValueIndex)).toInt() == m_ovValue))
    {
        oneValueReached = true;
        timeOneValueReached.start();
    }
    else if ((oneValueReached == true) && (timeOneValueReached.elapsed() > 3))
    {
        for (int i = 0; i < 15;i++)
        {
            *m_outputTextStream << s.at(i);
            if (i < 14)
            {
                *m_outputTextStream << ",";
            }
        }
        *m_outputTextStream << Qt::endl;
        oneValueReached = false;

        m_ovValue++;
        QString toProgressLog;
        if (m_ovValue < 256)
        {
            QString command("s m");
            command += ovToOutputVoltageMACAddressLabel->text();
            command += " 22 b" + QString::number(m_ovValue);
            toProgressLog = "Sending command " + command + " to gateway...";
            ovToOutputVoltageProgressLog->appendPlainText(toProgressLog);
            emit AmptUtilitiesDialogCommandToSendToGateway(command);
            int percentDone = static_cast<int>((m_ovValue / 256.0) * 100);
            QString percentDoneQStr;
            percentDoneQStr += QString::number(percentDone) + "% complete...";
            ovToOutputVoltageProgressLabel->setText(percentDoneQStr);
        }
        else
        {
            toProgressLog = "\n**** Finished OV to Output Voltage mapping... ***\n";
            ovToOutputVoltageProgressLog->appendPlainText(toProgressLog);

            // *m_outputTextStream << " Cancelled." << Qt::endl;
            m_outputTextStream->flush();
            m_outputFile->flush();
            m_outputFile->close();
            ovToOutputVoltageCancelButton->setEnabled(false);
            ovToOutputVoltageProgressLabel->setText("100% complete.");
            oneValueReached = false;

            emit AmptUtilitiesDialogEndRequestMACOTAData();
        }
    }
    //qDebug() << Q_FUNC_INFO << "2 oneValueReached " << oneValueReached << " s11 " << s.at(11) << " ovvalue " << m_ovValue;
}

void AmptUtilitiesDialog::handlePublishOneMACOTAOCData(QStringList s)
{
    qDebug() << Q_FUNC_INFO << " Entering with MAC " << s.at(0) << " length is " << s.length() << " OTA index " << m_oneValueIndex;
    static QTime timeOneValueReached;

    if ((oneValueReached == false) && ((s.at(m_oneValueIndex)).toInt() == m_ocValue))
    {
        oneValueReached = true;
        timeOneValueReached.start();
    }
    else if ((oneValueReached == true) && (timeOneValueReached.elapsed() > 3))
    {
        for (int i = 0; i < 15;i++)
        {
            *m_outputTextStream << s.at(i);
            if (i < 14)
            {
                *m_outputTextStream << ",";
            }
        }
        *m_outputTextStream << Qt::endl;
        oneValueReached = false;

        m_ocValue++;
        QString toProgressLog;
        if (m_ocValue < 256)
        {
            QString command("s m");
            command += ocToOutputCurrentMACAddressLabel->text();
            command += " 23 b" + QString::number(m_ocValue);
            toProgressLog = "Sending command " + command + " to gateway...";
            ocToOutputCurrentProgressLog->appendPlainText(toProgressLog);
            emit AmptUtilitiesDialogCommandToSendToGateway(command);
            int percentDone = static_cast<int>((m_ocValue / 256.0) * 100);
            QString percentDoneQStr;
            percentDoneQStr += QString::number(percentDone) + "% complete...";
            ocToOutputCurrentProgressLabel->setText(percentDoneQStr);
        }
        else
        {
            toProgressLog = "\n**** Finished OC to Output Current mapping... ***\n";
            ocToOutputCurrentProgressLog->appendPlainText(toProgressLog);

            // *m_outputTextStream << " Cancelled." << Qt::endl;
            m_outputTextStream->flush();
            m_outputFile->flush();
            m_outputFile->close();
            ocToOutputCurrentCancelButton->setEnabled(false);
            ocToOutputCurrentProgressLabel->setText("100% complete.");
            oneValueReached = false;

            emit AmptUtilitiesDialogEndRequestMACOTAData();
        }
    }
    //qDebug() << Q_FUNC_INFO << "2 oneValueReached " << oneValueReached << " s11 " << s.at(11) << " ovvalue " << m_ovValue;
}

void AmptUtilitiesDialog::handlePublishOneMACOTAData(QStringList s)
{
    qDebug() << Q_FUNC_INFO << " Entering with MAC " << s.at(0) << " length is " << s.length() << " OTA index " << m_oneValueIndex;

    if (s.length() == 22)
    {
        if (m_oneValueIndex == 11)
        {
           handlePublishOneMACOTAOVData(s);
        }
        else if (m_oneValueIndex == 12)
        {
           handlePublishOneMACOTAOCData(s);
        }
        else
        {
            QString errString(Q_FUNC_INFO);
            errString += "ERROR: unknown OTA index of  " + QString::number(m_oneValueIndex) + ", ending attempt ...";
            emit publishAmptUtilitiesDialogError(errString);
            m_outputTextStream->flush();
            m_outputFile->flush();
            m_outputFile->close();
            ocToOutputCurrentCancelButton->setEnabled(false);
            ocToOutputCurrentProgressLabel->setText("");
            ovToOutputVoltageCancelButton->setEnabled(false);
            ovToOutputVoltageProgressLabel->setText("");
            emit AmptUtilitiesDialogEndRequestMACOTAData();
            // Need to cancel everything ...
        }
    }
    else
    {
        QString errString(Q_FUNC_INFO);
        errString += "ERROR: received arguement size of " + QString::number(s.length()) + " instead of expected size of 22.";
        emit publishAmptUtilitiesDialogError(errString);
        qDebug() << errString;
    }
}

void AmptUtilitiesDialog::setColor()
{
    const QColorDialog::ColorDialogOptions options = QFlag(colorDialogOptionsWidget->value());
    const QColor color = QColorDialog::getColor(Qt::green, this, "Select Color", options);

    if (color.isValid()) {
        colorLabel->setText(color.name());
        colorLabel->setPalette(QPalette(color));
        colorLabel->setAutoFillBackground(true);
    }
}

void AmptUtilitiesDialog::setFont()
{
    const QFontDialog::FontDialogOptions options = QFlag(fontDialogOptionsWidget->value());
    bool ok;
    QFont font = QFontDialog::getFont(&ok, QFont(fontLabel->text()), this, "Select Font", options);
    if (ok) {
        fontLabel->setText(font.key());
        fontLabel->setFont(font);
    }
}

void AmptUtilitiesDialog::setExistingDirectory()
{
    QFileDialog::Options options = QFlag(fileDialogOptionsWidget->value());
    options |= QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
    QString directory = QFileDialog::getExistingDirectory(this,
                                tr("QFileDialog::getExistingDirectory()"),
                                directoryLabel->text(),
                                options);
    if (!directory.isEmpty())
        directoryLabel->setText(directory);
}

void AmptUtilitiesDialog::setOpenFileName()
{
    const QFileDialog::Options options = QFlag(fileDialogOptionsWidget->value());
    QString selectedFilter;
    QString fileName = QFileDialog::getOpenFileName(this,
                                tr("QFileDialog::getOpenFileName()"),
                                openFileNameLabel->text(),
                                tr("All Files (*);;Text Files (*.txt)"),
                                &selectedFilter,
                                options);
    if (!fileName.isEmpty())
        openFileNameLabel->setText(fileName);
}

void AmptUtilitiesDialog::setOpenFileNames()
{
    const QFileDialog::Options options = QFlag(fileDialogOptionsWidget->value());
    QString selectedFilter;
    QStringList files = QFileDialog::getOpenFileNames(
                                this, tr("QFileDialog::getOpenFileNames()"),
                                openFilesPath,
                                tr("All Files (*);;Text Files (*.txt)"),
                                &selectedFilter,
                                options);
    if (files.count()) {
        openFilesPath = files[0];
        openFileNamesLabel->setText(QString("[%1]").arg(files.join(", ")));
    }
}

void AmptUtilitiesDialog::setSaveFileName()
{
    const QFileDialog::Options options = QFlag(fileDialogOptionsWidget->value());
    QString selectedFilter;
    QString fileName = QFileDialog::getSaveFileName(this,
                                tr("QFileDialog::getSaveFileName()"),
                                saveFileNameLabel->text(),
                                tr("All Files (*);;Text Files (*.txt)"),
                                &selectedFilter,
                                options);
    if (!fileName.isEmpty())
        saveFileNameLabel->setText(fileName);
}

void AmptUtilitiesDialog::criticalMessage()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::critical(this, tr("QMessageBox::critical()"),
                                    MESSAGE,
                                    QMessageBox::Abort | QMessageBox::Retry | QMessageBox::Ignore);
    if (reply == QMessageBox::Abort)
        criticalLabel->setText(tr("Abort"));
    else if (reply == QMessageBox::Retry)
        criticalLabel->setText(tr("Retry"));
    else
        criticalLabel->setText(tr("Ignore"));
}

void AmptUtilitiesDialog::informationMessage()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::information(this, tr("QMessageBox::information()"), MESSAGE);
    if (reply == QMessageBox::Ok)
        informationLabel->setText(tr("OK"));
    else
        informationLabel->setText(tr("Escape"));
}

void AmptUtilitiesDialog::questionMessage()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("QMessageBox::question()"),
                                    MESSAGE,
                                    QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    if (reply == QMessageBox::Yes)
        questionLabel->setText(tr("Yes"));
    else if (reply == QMessageBox::No)
        questionLabel->setText(tr("No"));
    else
        questionLabel->setText(tr("Cancel"));
}

void AmptUtilitiesDialog::warningMessage()
{
    QMessageBox msgBox(QMessageBox::Warning, tr("QMessageBox::warning()"),
                       MESSAGE, nullptr, this);
    msgBox.setDetailedText(MESSAGE_DETAILS);
    msgBox.addButton(tr("Save &Again"), QMessageBox::AcceptRole);
    msgBox.addButton(tr("&Continue"), QMessageBox::RejectRole);
    if (msgBox.exec() == QMessageBox::AcceptRole)
        warningLabel->setText(tr("Save Again"));
    else
        warningLabel->setText(tr("Continue"));

}

void AmptUtilitiesDialog::errorMessage()
{
    errorMessageDialog->showMessage(
            tr("This dialog shows and remembers error messages. "
               "If the checkbox is checked (as it is by default), "
               "the shown message will be shown again, "
               "but if the user unchecks the box the message "
               "will not appear again if QErrorMessage::showMessage() "
               "is called with the same message."));
    errorLabel->setText(tr("If the box is unchecked, the message "
                           "won't appear again."));
}

void AmptUtilitiesDialog::closeEvent(QCloseEvent *event)
{
    qDebug() << Q_FUNC_INFO << " INFO: event:" << event->type();

    if (m_outputTextStream != nullptr)
    {
        m_outputTextStream->flush();
        delete m_outputTextStream;
    }
    if (m_outputFile != nullptr)
    {
        m_outputFile->flush();
        m_outputFile->close();
        delete m_outputFile;
    }
    emit AmptUtilitiesDialogEndRequestMACOTAData();
    emit AmptUtilitiesDialogClosingSignal();
}
