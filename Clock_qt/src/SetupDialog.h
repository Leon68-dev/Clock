#ifndef SETUPDIALOG_H
#define SETUPDIALOG_H

#include <QDialog>
#include <QCheckBox>
#include <QLineEdit>
#include <QSlider>
#include <QPushButton>
#include <QLabel>

class SetupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetupDialog(QWidget* parent = nullptr);

    // Structure to hold all settings
    struct SettingsData
    {
        bool showSeconds, showDay, showDate, isGmt, isTransparent, isSmooth, hasBorder;
        bool soundTickTack, sound1530, soundHours;
        bool showDigital, is24h, showCalendar, showSysMon, isMoving, isAlwaysOnTop;
        bool usePing;
        QString pingAddr;
        bool useWeather;
        QString weatherPlace, weatherUrl;
        int opacity;
    };

    void setSettings(const SettingsData& data);
    SettingsData getSettings() const;

private:
    // UI Elements
    QCheckBox* chkSeconds, * chkDay, * chkDate, * chkGmt, * chkTrans, * chkSmooth, * chkBorder;
    QCheckBox* chkTickTack, * chk1530, * chkHours;
    QCheckBox* chkDigital, * chk24h, * chkCalendar, * chkSysMon, * chkMoving, * chkTop;
    QCheckBox* chkPing, * chkWeather;
    QLineEdit* editPing, * editPlace, * editUrl;
    QSlider* sliderOpacity;
    QLabel* lblOpacityVal;

    void setupUi();
};

#endif