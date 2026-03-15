#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTimer>
#include <QPoint>
#include <QPainter>
#include <QPainterPath>
#include <QSoundEffect>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDate>
#include <QTime>
#include <QProcess>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QContextMenuEvent>
#include <QMenu>
#include <QAction>
#include <QSettings>
#include "SystemMonitor.h"
#include "SetupDialog.h"


class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void contextMenuEvent(QContextMenuEvent* event) override;
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;

private slots:
    void onTimerTick();
    void onWeatherReceived(QNetworkReply* reply);
    void onMenuSetup();
    void onMenuHide();
    void onMenuStartPosition();
    void onMenuCalendar();
    void onMenuShutdown();
    void onMenuWorldMap();
    void onMenuAbout();
    void onMenuExit();

private:
    QTimer* timer = nullptr; // Initialize with nullptr
    QPoint dragPos;

    void drawAnalogClock(QPainter& p);
    void drawHandHelper(QPainter& p, float x, float y, float angle, float len, float width, bool hasWhiteLine);
    void drawDigitalClock(QPainter& p, int yStart);
    void drawCalendar(QPainter& p, int yStart);
    void drawSystemMonitor(QPainter& p, int yStart);
    void drawPing(QPainter& p, int yStart);
    void drawWeather(QPainter& p, int yStart);

    void updateWeather();
    void updatePing();

    // Display data
    float currentCpu = 0.0f;
    float currentRam = 0.0f;
    int currentPing = -1;
    QString weatherTemp = "?°C";

    QSoundEffect tickSound;
    QSoundEffect hourSound;
    QNetworkAccessManager* networkManager = nullptr;

    QString m_digitalFontFamily; // To store the loaded font name

    QString m_strPingAddress = "8.8.8.8"; // Default address
    int m_pingValue = -1;              // -1 means no response
    bool m_isPingInProgress = false;
    
    QString m_strWeatherCity = "Odesa,UA";
    QString m_weatherTemp = "?°C";
    QString m_weatherDesc = "Loading...";
    QString m_strWeatherUrl = "https://api.open-meteo.com/v1/forecast?latitude=46.48&longitude=30.72&current=temperature_2m,weather_code";

    bool m_bSeconds = true;
    bool m_bGMT = false;
    bool m_bDate = true;
    bool m_bDay = true;
    bool m_bMoving = true;
    bool m_bTopMost = false;
    bool m_bTransparent = false;
    bool m_bBorder = true;
    bool m_bSmooth = true;
    bool m_bTickTack = false;
    bool m_b1530 = false;
    bool m_bHours = false;
    bool m_bDigitalClock = true;
    bool m_b24Hours = true;
    bool m_bCalendar = true;
    bool m_bSysMon = true;
    bool m_bPing = true;
    bool m_bWeather = false;
    int m_nOpacity = 80;
    bool m_bMouseOver = false; // To track hover state

    void loadSettings();
    void saveSettings();
    void applySettings();


};

#endif