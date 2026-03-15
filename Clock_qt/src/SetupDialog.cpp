#include "SetupDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>

SetupDialog::SetupDialog(QWidget* parent) : QDialog(parent)
{
    setWindowTitle("Setup");
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::CustomizeWindowHint);

    setFixedSize(550, 500);
    setupUi();
}

void SetupDialog::setupUi()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // --- Group 1: Analog Clock & Sounds ---
    QHBoxLayout* topRowLayout = new QHBoxLayout();

    QGroupBox* grpAnalog = new QGroupBox("Analog Clock", this);
    QGridLayout* gridAnalog = new QGridLayout(grpAnalog);
    chkSeconds = new QCheckBox("Seconds", grpAnalog);
    chkDay = new QCheckBox("Day", grpAnalog);
    chkDate = new QCheckBox("Date", grpAnalog);
    chkGmt = new QCheckBox("GMT", grpAnalog);
    chkTrans = new QCheckBox("Transparent", grpAnalog);
    chkSmooth = new QCheckBox("Smooth", grpAnalog);
    chkBorder = new QCheckBox("Border", grpAnalog);

    gridAnalog->addWidget(chkSeconds, 0, 0);
    gridAnalog->addWidget(chkDay, 1, 0);
    gridAnalog->addWidget(chkDate, 2, 0);
    gridAnalog->addWidget(chkGmt, 3, 0);
    gridAnalog->addWidget(chkTrans, 1, 1);
    gridAnalog->addWidget(chkSmooth, 2, 1);
    gridAnalog->addWidget(chkBorder, 3, 1);

    QGroupBox* grpSounds = new QGroupBox("Sounds", this);
    QVBoxLayout* vboxSounds = new QVBoxLayout(grpSounds);
    chkTickTack = new QCheckBox("Tick Tack", grpSounds);
    chk1530 = new QCheckBox("15-30", grpSounds);
    chkHours = new QCheckBox("Hours", grpSounds);
    vboxSounds->addWidget(chkTickTack);
    vboxSounds->addWidget(chk1530);
    vboxSounds->addWidget(chkHours);

    QGroupBox* grpModules = new QGroupBox("Modules", this);
    QGridLayout* gridModules = new QGridLayout(grpModules);
    chkDigital = new QCheckBox("Digital Clock", grpModules);
    chk24h = new QCheckBox("24 hours", grpModules);
    chkCalendar = new QCheckBox("Calendar", grpModules);
    chkSysMon = new QCheckBox("SYS monitor", grpModules);
    chkMoving = new QCheckBox("Moving", grpModules);
    chkTop = new QCheckBox("Always on top", grpModules);

    gridModules->addWidget(chkDigital, 0, 0);
    gridModules->addWidget(chk24h, 1, 0);
    gridModules->addWidget(chkCalendar, 2, 0);
    gridModules->addWidget(chkSysMon, 3, 0);
    gridModules->addWidget(chkMoving, 0, 1);
    gridModules->addWidget(chkTop, 1, 1);

    topRowLayout->addWidget(grpAnalog);
    topRowLayout->addWidget(grpSounds);
    topRowLayout->addWidget(grpModules);
    mainLayout->addLayout(topRowLayout);

    // --- Group 2: Ping ---
    QGroupBox* grpPing = new QGroupBox("Ping", this);
    QGridLayout* gridPing = new QGridLayout(grpPing);
    chkPing = new QCheckBox("Ping", grpPing);
    editPing = new QLineEdit(grpPing);
    gridPing->addWidget(chkPing, 0, 0);
    gridPing->addWidget(new QLabel("IP(DNS name)"), 1, 0);
    gridPing->addWidget(editPing, 1, 1);
    mainLayout->addWidget(grpPing);

    // --- Group 3: Weather ---
    QGroupBox* grpWeather = new QGroupBox("Weather", this);
    QGridLayout* gridWeather = new QGridLayout(grpWeather);
    chkWeather = new QCheckBox("Weather", grpWeather);
    editPlace = new QLineEdit(grpWeather);
    editUrl = new QLineEdit(grpWeather);
    QPushButton* btnLink = new QPushButton("Link", grpWeather);

    gridWeather->addWidget(chkWeather, 0, 0);
    gridWeather->addWidget(new QLabel("Place"), 1, 0);
    gridWeather->addWidget(editPlace, 1, 1);
    gridWeather->addWidget(new QLabel("API URL"), 2, 0);
    gridWeather->addWidget(editUrl, 2, 1);
    gridWeather->addWidget(btnLink, 2, 2);
    mainLayout->addWidget(grpWeather);

    // --- Group 4: Opacity ---
    QGroupBox* grpOpacity = new QGroupBox("Opacity", this);
    QHBoxLayout* hboxOpacity = new QHBoxLayout(grpOpacity);
    sliderOpacity = new QSlider(Qt::Horizontal, grpOpacity);
    sliderOpacity->setRange(20, 100);
    lblOpacityVal = new QLabel("100%", grpOpacity);
    hboxOpacity->addWidget(sliderOpacity);
    hboxOpacity->addWidget(lblOpacityVal);
    mainLayout->addWidget(grpOpacity);

    // --- Buttons ---
    QHBoxLayout* btnLayout = new QHBoxLayout();
    QPushButton* btnOk = new QPushButton("OK", this);
    QPushButton* btnCancel = new QPushButton("Cancel", this);
    btnLayout->addStretch();
    btnLayout->addWidget(btnOk);
    btnLayout->addWidget(btnCancel);
    mainLayout->addLayout(btnLayout);

    connect(btnOk, &QPushButton::clicked, this, &QDialog::accept);
    connect(btnCancel, &QPushButton::clicked, this, &QDialog::reject);
    connect(sliderOpacity, &QSlider::valueChanged, [this](int val) {
        lblOpacityVal->setText(QString::number(val) + "%");
        });
}

void SetupDialog::setSettings(const SettingsData& data)
{
    chkSeconds->setChecked(data.showSeconds);
    chkDay->setChecked(data.showDay);
    chkDate->setChecked(data.showDate);
    chkGmt->setChecked(data.isGmt);
    chkTrans->setChecked(data.isTransparent);
    chkSmooth->setChecked(data.isSmooth);
    chkBorder->setChecked(data.hasBorder);
    chkTickTack->setChecked(data.soundTickTack);
    chk1530->setChecked(data.sound1530);
    chkHours->setChecked(data.soundHours);
    chkDigital->setChecked(data.showDigital);
    chk24h->setChecked(data.is24h);
    chkCalendar->setChecked(data.showCalendar);
    chkSysMon->setChecked(data.showSysMon);
    chkMoving->setChecked(data.isMoving);
    chkTop->setChecked(data.isAlwaysOnTop);
    chkPing->setChecked(data.usePing);
    editPing->setText(data.pingAddr);
    chkWeather->setChecked(data.useWeather);
    editPlace->setText(data.weatherPlace);
    editUrl->setText(data.weatherUrl);
    sliderOpacity->setValue(data.opacity);
}

SetupDialog::SettingsData SetupDialog::getSettings() const
{
    SettingsData data;
    data.showSeconds = chkSeconds->isChecked();
    data.showDay = chkDay->isChecked();
    data.showDate = chkDate->isChecked();
    data.isGmt = chkGmt->isChecked();
    data.isTransparent = chkTrans->isChecked();
    data.isSmooth = chkSmooth->isChecked();
    data.hasBorder = chkBorder->isChecked();
    data.soundTickTack = chkTickTack->isChecked();
    data.sound1530 = chk1530->isChecked();
    data.soundHours = chkHours->isChecked();
    data.showDigital = chkDigital->isChecked();
    data.is24h = chk24h->isChecked();
    data.showCalendar = chkCalendar->isChecked();
    data.showSysMon = chkSysMon->isChecked();
    data.isMoving = chkMoving->isChecked();
    data.isAlwaysOnTop = chkTop->isChecked();
    data.usePing = chkPing->isChecked();
    data.pingAddr = editPing->text();
    data.useWeather = chkWeather->isChecked();
    data.weatherPlace = editPlace->text();
    data.weatherUrl = editUrl->text();
    data.opacity = sliderOpacity->value();
    return data;
}