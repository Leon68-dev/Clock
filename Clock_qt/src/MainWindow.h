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
#include "SystemMonitor.h"


class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private slots:
    void onTimerTick();
    void onWeatherReceived(QNetworkReply* reply);

private:
    QTimer* timer;
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
    bool m_bTickTack = false;

    QSoundEffect tickSound;
    QSoundEffect hourSound;
    QNetworkAccessManager* networkManager = nullptr;

    QString m_digitalFontFamily; // To store the loaded font name

    QString m_pingAddress = "8.8.8.8"; // Default address
    int m_pingValue = -1;              // -1 means no response
    bool m_isPingInProgress = false;
    
    QString m_weatherCity = "Odesa,UA";
    QString m_weatherTemp = "?°C";
    QString m_weatherDesc = "Loading...";
    QString m_weatherUrl = "https://api.open-meteo.com/v1/forecast?latitude=46.48&longitude=30.72&current=temperature_2m,weather_code";

};

#endif