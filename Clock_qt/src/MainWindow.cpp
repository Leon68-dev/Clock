#include <QDateTime>
#include <QMouseEvent>
#include <QFontDatabase>
#include <QProcess>
#include "MainWindow.h"
#include "SetupDialog.h"
#include "CalendarDialog.h"
#include "ShutdownDialog.h"
#include "WorldMapDialog.h"
#include "AboutDialog.h"

MainWindow::MainWindow(QWidget* parent) : QWidget(parent)
{
    // 1. Initialize pointers to nullptr first
    timer = nullptr;
    networkManager = nullptr;

    // 2. Create objects BEFORE applying settings
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::onTimerTick);

    this->setWindowIcon(QIcon(":/Clock_qt.ico"));

    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::onWeatherReceived);

    // 3. Window settings
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground);

    // 4. Now it is safe to load and apply settings
    loadSettings();
    applySettings();
    
    createTrayIcon();

    setFixedWidth(122);
    setFixedHeight(530);

    // Load custom digital font from resources
    int fontId = QFontDatabase::addApplicationFont(":/digital_7italic.ttf");
    if (fontId != -1)
    {
        m_digitalFontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    }

    updateWeather(); // Initial update

    // Initialize sounds from resources
    m_soundTick.setSource(QUrl("qrc:/_TickTack.wav"));
    m_sound15.setSource(QUrl("qrc:/_15.wav"));
    m_sound30.setSource(QUrl("qrc:/_30.wav"));
    m_soundBoom.setSource(QUrl("qrc:/_Boom.wav"));

    // Set default volumes
    m_soundTick.setVolume(0.5f);
    m_soundBoom.setVolume(0.8f);
}

void MainWindow::onTimerTick()
{
    QDateTime now = m_bGMT ? QDateTime::currentDateTimeUtc() : QDateTime::currentDateTime();
    QTime time = now.time();

    if (m_isShutdownEnabled && !m_alreadyExecuted)
    {
        // Compare hours and minutes
        if (time.hour() == m_shutdownTime.hour() &&
            time.minute() == m_shutdownTime.minute())
        {
            m_alreadyExecuted = true;
            executeShutdown();
        }
    }

    // Logic that runs strictly ONCE PER SECOND
    static int lastSec = -1;
    if (time.second() != lastSec)
    {
        lastSec = time.second();

        QString tip = now.toString("dddd - HH:mm");
        if (m_bGMT)
            tip += " GMT";
        m_trayIcon->setToolTip(tip);

        // 1. Match MFC logic: Update metrics and ping every 3 seconds
        if (time.second() % 3 == 0)
        {
            updatePing();
            updateThemeColor();
            currentCpu = SystemMonitor::getCpuUsage();
            currentRam = SystemMonitor::getRamUsage();
        }

        // 2. Weather update
        if ((time.minute() % 5 == 0) && time.second() == 0)
        {
            updateWeather();
        }

        // 3. Sound Logic
        if (m_bHours && time.minute() == 0 && time.second() == 0)
        {
            playHourlyChime(time.hour());
        }

        if (m_b1530 && time.second() == 0)
        {
            if (time.minute() == 15 || time.minute() == 45)
                m_sound15.play();
            else if (time.minute() == 30)
                m_sound30.play();
        }

        if (m_bTickTack && time.second() % 2 == 0)
        {
            // Don't interrupt long chimes
            if (!m_soundBoom.isPlaying() && !m_sound15.isPlaying() && !m_sound30.isPlaying())
            {
                m_soundTick.play();
            }
        }

    }

    // Repaint happens every timer tick (200ms) for smooth hands
    update();
}

void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    // 1. Draw Global Glass Background (Only visible on Hover)
    int glassAlpha = m_bMouseOver ? 160 : 1;
    float cornerRadius = 8.0f; // Reduced from 15 to 8

    QPainterPath fullPath;
    fullPath.addRoundedRect(rect().adjusted(1, 1, -1, -1), cornerRadius, cornerRadius);
    p.fillPath(fullPath, QColor(20, 20, 20, glassAlpha));

    if (m_bBorder)
    {
        int borderAlpha = m_bMouseOver ? 80 : 20;
        p.setPen(QPen(QColor(255, 255, 255, borderAlpha), 1));
        p.drawPath(fullPath);
    }

    // 2. Calculate where modules start
    int modulesYStart = 120;
    if (m_bDigitalClock)
    {
        modulesYStart += 50;
    }

    // 3. Draw Modules Background (Gray underlay)
    if (m_bCalendar || m_bSysMon || m_bPing || m_bWeather)
    {
        QRectF modulesRect(0, modulesYStart, width(), height() - modulesYStart);
        QPainterPath modulesPath;
        // Use the same reduced radius here
        modulesPath.addRoundedRect(modulesRect.adjusted(1, 0, -1, -1), cornerRadius, cornerRadius);

        p.fillPath(modulesPath, QColor(60, 60, 60, 100));
        p.setPen(QPen(QColor(255, 255, 255, 50), 1));
        p.drawPath(modulesPath);
    }

    // 4. Draw Content
    int currentY = 0;
    drawAnalogClock(p);
    currentY = 120;

    if (m_bDigitalClock)
    {
        drawDigitalClock(p, currentY);
        currentY += 50;
    }

    if (m_bCalendar)
    {
        drawCalendar(p, currentY);
        currentY += 105;
    }

    if (m_bSysMon)
    {
        drawSystemMonitor(p, currentY);
        currentY += 65;
    }

    if (m_bPing)
    {
        drawPing(p, currentY);
        currentY += 25;
    }

    if (m_bWeather)
    {
        drawWeather(p, currentY);
        currentY += 45;
    }

    // Dynamic height adjustment
    if (height() != currentY + 10)
    {
        setFixedHeight(currentY + 10);
    }
}

void MainWindow::drawAnalogClock(QPainter& p)
{
    p.save();
    p.setRenderHint(QPainter::Antialiasing);

    float xCenter = width() / 2.0f;
    float yCenter = 60.0f;
    float radius = 54.0f;
    float borderThickness = 5.0f;
    float innerRadius = radius - borderThickness - 1.0f;

    // 1. Face background - Check m_bTransparent
    if (!m_bTransparent)
    {
        p.setPen(Qt::NoPen);
        p.setBrush(QColor(242, 238, 225));
        p.drawEllipse(QPointF(xCenter, yCenter), radius, radius);
    }

    // 2. Borders - Check m_bBorder
    if (m_bBorder)
    {
        p.setBrush(Qt::NoBrush);
        p.setPen(QPen(Qt::black, borderThickness));
        p.drawEllipse(QPointF(xCenter, yCenter), radius - borderThickness / 2.0f, radius - borderThickness / 2.0f);
        p.setPen(QPen(Qt::gray, 1.5f));
        p.drawEllipse(QPointF(xCenter, yCenter), radius - borderThickness / 2.0f, radius - borderThickness / 2.0f);
    }

    // 3. Marks (Always drawn)
    for (int i = 0; i < 60; ++i)
    {
        p.save();
        p.translate(xCenter, yCenter);
        p.rotate(i * 6.0);

        if (i % 5 == 0)
        {
            // Hour marks (Black lines)
            p.setPen(QPen(Qt::black, (i % 15 == 0) ? 3.5f : 1.8f));
            p.drawLine(0, -innerRadius + 8, 0, -innerRadius - 2);

            // THE DOTS (Small dots at the inner end of the hour lines)
            // We use the face color to create the "hole" effect like in MFC
            p.setPen(Qt::NoPen);
            p.setBrush(QColor(242, 238, 225));
            p.drawEllipse(QRectF(-1.5, -innerRadius + 6.5, 3.0, 3.0));
        }
        else
        {
            // Minute dots (Small black dots between hours)
            p.setBrush(Qt::black);
            p.setPen(Qt::NoPen);
            p.drawEllipse(QRectF(-1.1, -innerRadius - 1.2, 2.2, 2.2));
        }
        p.restore();
    }

    // 4. Text elements - Check GMT, Day, Date
    QDateTime now = m_bGMT ? QDateTime::currentDateTimeUtc() : QDateTime::currentDateTime();

    // LAN
    QFont fontLan("Arial", 10);
    fontLan.setItalic(true);
    fontLan.setUnderline(true);
    p.setFont(fontLan);
    p.setPen(QColor(240, 128, 128));
    p.drawText(QRectF(xCenter - 25, yCenter - 3 - innerRadius * 0.62, 50, 15), Qt::AlignCenter, "LAN");

    // C++(Qt)
    QFont fontCpp("Arial", 6, QFont::Bold);
    p.setFont(fontCpp);
    p.setPen(Qt::gray);
    p.drawText(QRectF(xCenter - 25, yCenter - innerRadius * 0.42, 50, 12), Qt::AlignCenter, "C++");

    // Day - Check m_bDay
    if (m_bDay)
    {
        bool isWeekend = (now.date().dayOfWeek() == 6 || now.date().dayOfWeek() == 7);
        p.setPen(isWeekend ? QColor(240, 128, 128) : Qt::gray);
        p.drawText(QRectF(xCenter - 25, yCenter + innerRadius * 0.10, 50, 12), Qt::AlignCenter, now.toString("ddd").toUpper());
    }

    // Date - Check m_bDate
    if (m_bDate)
    {
        p.setPen(Qt::gray);
        p.drawText(QRectF(xCenter - 35, yCenter + innerRadius * 0.35, 70, 12), Qt::AlignCenter, now.toString("dd-MM-yy"));
    }

    // 5. Hands - Check Smooth and Seconds
    QTime time = now.time();
    float fSeconds = m_bSmooth ? (time.second() + time.msec() / 1000.0f) : (float)time.second();
    float fMinutes = time.minute() + fSeconds / 60.0f;
    float fHours = (time.hour() % 12 + fMinutes / 60.0f) * 5.0f;

    drawHandHelper(p, xCenter, yCenter, fHours * 6.0f, innerRadius * 0.55f, 5.5f, true);
    drawHandHelper(p, xCenter, yCenter, fMinutes * 6.0f, innerRadius * 0.82f, 3.8f, true);

    if (m_bSeconds)
    {
        p.save();
        p.translate(xCenter, yCenter);
        p.rotate(fSeconds * 6.0f);
        p.setPen(QPen(Qt::red, 1.2f));
        p.drawLine(0, 8, 0, -innerRadius * 0.92f);
        p.restore();
    }

    p.setBrush(Qt::black);
    p.setPen(Qt::NoPen);
    p.drawEllipse(QPointF(xCenter, yCenter), 3.5, 3.5);
    p.restore();
}

void MainWindow::drawHandHelper(QPainter& p, float x, float y, float angle, float len, float width, bool hasWhiteLine)
{
    p.save();
    p.translate(x, y);
    p.rotate(angle);

    // Black part of the hand
    p.setPen(QPen(Qt::black, width, Qt::SolidLine, Qt::RoundCap));
    p.drawLine(0, 0, 0, -len);

    // White line inside
    if (hasWhiteLine)
    {
        p.setPen(QPen(Qt::white, width / 2.2f, Qt::SolidLine, Qt::RoundCap));
        p.drawLine(0, 0, 0, -len);
    }

    p.restore();
}

void MainWindow::drawDigitalClock(QPainter& p, int yStart)
{
    p.save();

    float xCenter = width() / 2.0f;
    float lcdW = 108.0f;
    float lcdH = 42.0f;
    float lcdX = xCenter - (lcdW / 2.0f);
    float lcdY = yStart + 2.0f;

    // 1. Draw LCD background and border
    QPainterPath lcdPath;
    lcdPath.addRoundedRect(lcdX, lcdY, lcdW, lcdH, 4.0f, 4.0f);

    p.setPen(QPen(QColor(0, 0, 0, 100), 1));
    p.setBrush(QColor(170, 185, 165));
    p.drawPath(lcdPath);

    // 2. Prepare fonts
    QFont digFontLarge(m_digitalFontFamily, 18);
    QFont digFontSmall(m_digitalFontFamily, 11);
    QFont fontIndicator("Arial", 6, QFont::Bold);

    // GMT Logic: Get correct time based on setting
    QDateTime now = m_bGMT ? QDateTime::currentDateTimeUtc() : QDateTime::currentDateTime();
    QTime time = now.time();

    // 12/24 Hours Logic
    int displayHour = time.hour();
    QString strAMPM = "";

    if (!m_b24Hours)
    {
        strAMPM = (displayHour >= 12) ? "PM" : "AM";
        displayHour = displayHour % 12;
        if (displayHour == 0)
            displayHour = 12;

        // Draw AM/PM indicator (top left of LCD)
        p.setPen(Qt::black);
        p.setFont(fontIndicator);
        p.drawText(QRectF(lcdX + 3, lcdY + 2, 20, 10), Qt::AlignLeft, strAMPM);
    }

    // Your coordinates
    float p_H1 = xCenter - 32.0f;
    float p_H2 = xCenter - 16.0f;
    float p_Colon = xCenter - 10.5f;
    float p_M1 = xCenter + 6.0f;
    float p_M2 = xCenter + 22.0f;
    float p_Day = xCenter + 2.0f;
    float p_Date = xCenter + 42.0f;
    float p_S1 = xCenter + 36.0f;
    float p_S2 = xCenter + 48.0f;

    float topRowY = lcdY + 2.0f;
    float bottomRowY = lcdY + 12.0f;

    auto drawDigit = [&](const QRectF& rect, const QString& text, Qt::Alignment align = Qt::AlignRight)
        {
            p.drawText(rect, align | Qt::AlignVCenter, text);
        };

    // 3. Draw background "shadow" digits (88:88 88)
    p.setPen(QColor(0, 0, 0, 20));

    p.setFont(digFontSmall);
    drawDigit(QRectF(p_Day - 20, topRowY, 35, 15), "88");
    drawDigit(QRectF(p_Date - 20, topRowY, 18, 15), "88");

    p.setFont(digFontLarge);
    if (m_b24Hours || displayHour >= 10)
        drawDigit(QRectF(p_H1 - 20, bottomRowY, 20, 30), "8");

    drawDigit(QRectF(p_H2 - 20, bottomRowY, 20, 30), "8");
    drawDigit(QRectF(p_Colon - 10, bottomRowY, 20, 30), ":", Qt::AlignCenter);
    drawDigit(QRectF(p_M1 - 20, bottomRowY, 20, 30), "8");
    drawDigit(QRectF(p_M2 - 20, bottomRowY, 20, 30), "8");

    p.setFont(digFontSmall);
    drawDigit(QRectF(p_S1 - 15, bottomRowY + 7, 15, 20), "8");
    drawDigit(QRectF(p_S2 - 15, bottomRowY + 7, 15, 20), "8");

    // 4. Draw actual time data
    p.setPen(Qt::black);

    // Day of week
    p.setFont(digFontSmall);
    QString dayStr = now.toString("ddd").left(2).toUpper();
    drawDigit(QRectF(p_Day - 20, topRowY, 35, 15), dayStr);

    // Date
    drawDigit(QRectF(p_Date - 20, topRowY, 18, 15), now.toString("dd"));

    // Hours (using displayHour instead of time.hour())
    p.setFont(digFontLarge);
    if (displayHour >= 10)
    {
        drawDigit(QRectF(p_H1 - 20, bottomRowY, 20, 30), QString::number(displayHour / 10));
    }
    drawDigit(QRectF(p_H2 - 20, bottomRowY, 20, 30), QString::number(displayHour % 10));

    // Colon
    drawDigit(QRectF(p_Colon - 10, bottomRowY, 20, 30), ":", Qt::AlignCenter);

    // Minutes
    drawDigit(QRectF(p_M1 - 20, bottomRowY, 20, 30), QString::number(time.minute() / 10));
    drawDigit(QRectF(p_M2 - 20, bottomRowY, 20, 30), QString::number(time.minute() % 10));

    // Seconds
    p.setFont(digFontSmall);
    drawDigit(QRectF(p_S1 - 15, bottomRowY + 7, 15, 20), QString::number(time.second() / 10));
    drawDigit(QRectF(p_S2 - 15, bottomRowY + 7, 15, 20), QString::number(time.second() % 10));

    p.restore();
}

void MainWindow::drawCalendar(QPainter& p, int yStart)
{
    p.save();

    float xCenter = width() / 2.0f;
    float calW = width() - 20.0f;
    float calX = 10.0f;
    float calY = yStart + 2.0f;

    QDate today = QDate::currentDate();
    QDate firstDayOfMonth(today.year(), today.month(), 1);

    int startDay = firstDayOfMonth.dayOfWeek() - 1;
    int daysInMonth = today.daysInMonth();

    // Adaptive weekend color
    QColor weekendColor = (m_dynamicColor == Qt::black) ? QColor(200, 0, 0) : QColor(240, 128, 128);

    // 1. Draw Header (Month Year)
    QFont fontHeader("Arial", 8, QFont::Bold);
    p.setFont(fontHeader);
    p.setPen(m_dynamicColor);
    p.drawText(QRectF(0, calY + 2, width(), 15), Qt::AlignCenter, today.toString("MMMM yyyy"));

    // 2. Draw Day Names
    QFont fontDays("Arial", 6);
    p.setFont(fontDays);
    const QStringList dayNames = { "M", "T", "W", "T", "F", "S", "S" };
    float cellW = calW / 7.0f;

    for (int i = 0; i < 7; ++i)
    {
        if (i >= 5)
            p.setPen(weekendColor);
        else
            p.setPen(m_dynamicColor);

        p.drawText(QRectF(calX + i * cellW, calY + 18, cellW, 12), Qt::AlignCenter, dayNames[i]);
    }

    // 3. Draw Dates Grid
    int row = 0;
    for (int d = 1; d <= daysInMonth; ++d)
    {
        int col = (startDay + d - 1) % 7;
        if (d > 1 && col == 0)
            row++;

        float x = calX + col * cellW;
        float y = calY + 32 + row * 12;

        if (d == today.day())
        {
            p.setPen(Qt::NoPen);
            // Highlight background also adapts slightly
            p.setBrush(QColor(m_dynamicColor.red(), m_dynamicColor.green(), m_dynamicColor.blue(), 40));
            p.drawRoundedRect(QRectF(x + 2, y - 1, cellW - 4, 12), 2, 2);
        }

        if (col >= 5)
            p.setPen(weekendColor);
        else
            p.setPen(m_dynamicColor);

        p.drawText(QRectF(x, y, cellW, 12), Qt::AlignCenter, QString::number(d));
    }

    p.restore();
}

void MainWindow::drawSystemMonitor(QPainter& p, int yStart)
{
    p.save();

    float margin = 10.0f;
    float barW = (float)width() - (margin * 2.0f);
    float barH = 10.0f;
    float monY = (float)yStart + 5.0f;

    // 1. Draw Adaptive Separator line
    p.setPen(QPen(QColor(m_dynamicColor.red(), m_dynamicColor.green(), m_dynamicColor.blue(), 50), 1));
    p.drawLine(QPointF(margin, monY), QPointF((float)width() - margin, monY));

    QFont fontLabel("Arial", 7);
    QFont fontValue("Arial", 7);
    p.setPen(m_dynamicColor);

    // 2. CPU Section
    p.setFont(fontLabel);
    p.drawText(QRectF(margin, monY + 5, 40, 12), Qt::AlignLeft, "CPU");
    p.setFont(fontValue);
    p.drawText(QRectF((float)width() - margin - 40, monY + 5, 40, 12), Qt::AlignRight, QString::number((int)currentCpu) + "%");

    QRectF cpuRect(margin, monY + 18, barW, barH);
    p.setBrush(QColor(0, 0, 0, 100));
    p.setPen(QPen(QColor(255, 255, 255, 40), 1));
    p.drawRect(cpuRect);

    if (currentCpu > 0)
    {
        float cpuFill = (barW * currentCpu) / 100.0f;
        p.setPen(Qt::NoPen);
        p.setBrush(QColor(80, 220, 80));
        p.drawRect(QRectF(margin + 1, monY + 19, cpuFill - 1, barH - 2));
    }

    // 3. RAM Section
    p.setPen(m_dynamicColor);
    p.setFont(fontLabel);
    p.drawText(QRectF(margin, monY + 35, 40, 12), Qt::AlignLeft, "RAM");
    p.setFont(fontValue);
    p.drawText(QRectF((float)width() - margin - 40, monY + 35, 40, 12), Qt::AlignRight, QString::number((int)currentRam) + "%");

    QRectF ramRect(margin, monY + 48, barW, barH);
    p.setBrush(QColor(0, 0, 0, 100));
    p.setPen(QPen(QColor(255, 255, 255, 40), 1));
    p.drawRect(ramRect);

    if (currentRam > 0)
    {
        float ramFill = (barW * currentRam) / 100.0f;
        p.setPen(Qt::NoPen);
        p.setBrush(QColor(70, 130, 230));
        p.drawRect(QRectF(margin + 1, monY + 49, ramFill - 1, barH - 2));
    }

    p.restore();
}

void MainWindow::drawPing(QPainter& p, int yStart)
{
    p.save();

    float margin = 10.0f;
    float pingY = (float)yStart + 5.0f;

    // 1. Draw Adaptive Separator line
    p.setPen(QPen(QColor(m_dynamicColor.red(), m_dynamicColor.green(), m_dynamicColor.blue(), 50), 1));
    p.drawLine(QPointF(margin, pingY), QPointF((float)width() - margin, pingY));

    QFont fontLabel("Arial", 7);
    QFont fontValue("Arial", 7);

    // 2. Draw Label
    p.setPen(m_dynamicColor);
    p.setFont(fontLabel);
    QString label = "Ping: " + m_strPingAddress;

    QFontMetrics fm(fontLabel);
    QString elidedLabel = fm.elidedText(label, Qt::ElideRight, width() - 50);
    p.drawText(QRectF(margin, pingY + 8, width() - 50, 15), Qt::AlignLeft, elidedLabel);

    // 3. Draw Value
    QString valStr = (m_pingValue == -1) ? "Error" : QString::number(m_pingValue) + " ms";
    QColor valColor;
    
    if (m_pingValue == -1) 
        valColor = QColor(240, 128, 128);
    else if (m_pingValue < 100) 
        valColor = QColor(80, 220, 80);
    else if (m_pingValue < 250) 
        valColor = Qt::yellow;
    else 
        valColor = QColor(240, 128, 128);

    p.setPen(valColor);
    p.setFont(fontValue);
    p.drawText(QRectF((float)width() - margin - 40, pingY + 8, 40, 15), Qt::AlignRight, valStr);

    p.restore();
}

void MainWindow::updatePing()
{
    if (!m_bPing)
        return;

    if (m_isPingInProgress)
        return;

    m_isPingInProgress = true;

    QProcess* pingProcess = new QProcess(this);

    QStringList parameters;
#ifdef Q_OS_WIN
    parameters << "-n" << "1" << "-w" << "1000" << m_strPingAddress;
#else
    // Linux parameters: -c 1 (count 1), -W 1 (timeout 1 second)
    parameters << "-c" << "1" << "-W" << "1" << m_strPingAddress;
#endif

    connect(pingProcess, &QProcess::finished, [this, pingProcess](int exitCode)
        {
            QString output = QString::fromLocal8Bit(pingProcess->readAllStandardOutput());
            int resultTime = -1;

            if (exitCode == 0)
            {
#ifdef Q_OS_WIN
                // Windows parsing: looks for "time=XXms"
                int index = output.indexOf("time=");
                if (index != -1)
                {
                    int start = index + 5;
                    int end = output.indexOf("ms", start);
                    if (end != -1)
                    {
                        resultTime = output.mid(start, end - start).trimmed().toInt();
                    }
                }
#else
                // Linux parsing: looks for "time=XX.X ms" or "time<XX.X ms"
                int index = output.indexOf("time=");
                if (index == -1)
                {
                    index = output.indexOf("time<");
                }

                if (index != -1)
                {
                    int start = index + 5;
                    int end = output.indexOf(" ms", start);
                    if (end != -1)
                    {
                        // Read the float value (e.g., 22.5) and convert to int
                        QString timeStr = output.mid(start, end - start).trimmed();
                        resultTime = timeStr.toDouble() * 1000; // Convert ms to integer ms for consistency, or just use toInt() if it's already integer
                        resultTime = timeStr.toDouble(); // Keep it as double/int for now
                    }
                }
#endif
            }

            // Final assignment
            m_pingValue = (resultTime > 0) ? resultTime : -1;
            m_isPingInProgress = false;
            pingProcess->deleteLater();
        });

    pingProcess->start("ping", parameters);
}

void MainWindow::drawWeather(QPainter& p, int yStart)
{
    p.save();

    float margin = 10.0f;
    float weaY = (float)yStart + 5.0f;

    // 1. Draw Adaptive Separator line
    p.setPen(QPen(QColor(m_dynamicColor.red(), m_dynamicColor.green(), m_dynamicColor.blue(), 50), 1));
    p.drawLine(QPointF(margin, weaY), QPointF((float)width() - margin, weaY));

    // 2. Draw City Name
    QFont fontCity("Arial", 6);
    p.setFont(fontCity);
    p.setPen(m_dynamicColor);
    p.drawText(QRectF(margin, weaY + 4, width() - 20, 15), Qt::AlignLeft, m_strWeatherCity);

    // 3. Draw Temperature
    QFont fontTemp("Arial", 11, QFont::Bold);
    p.setFont(fontTemp);
    p.drawText(QRectF(0, weaY + 10, width(), 25), Qt::AlignCenter, m_weatherTemp);

    // 4. Draw Description
    QFont fontDesc("Arial", 6);
    p.setFont(fontDesc);
    p.drawText(QRectF(0, weaY + 28
        , width(), 15), Qt::AlignCenter, m_weatherDesc);

    p.restore();
}

void MainWindow::updateWeather()
{
    if (!m_bWeather)
        return;

    if (networkManager)
    {
        networkManager->get(QNetworkRequest(QUrl(m_strWeatherUrl)));
    }
}

void MainWindow::onWeatherReceived(QNetworkReply* reply)
{
    if (!m_bWeather)
        return;

    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray data = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject root = doc.object();

        if (root.contains("current"))
        {
            QJsonObject current = root["current"].toObject();

            double temp = current["temperature_2m"].toDouble();
            // Use \u00B0 for the degree symbol
            m_weatherTemp = QString::number(temp, 'f', 1) + "\u00B0C";

            int code = current["weather_code"].toInt();
            if (code == 0)
                m_weatherDesc = "Clear sky";
            else if (code >= 1 && code <= 3)
                m_weatherDesc = "Partly cloudy";
            else if (code >= 45 && code <= 48)
                m_weatherDesc = "Foggy";
            else if (code >= 51 && code <= 67)
                m_weatherDesc = "Rainy";
            else if (code >= 71 && code <= 77)
                m_weatherDesc = "Snowy";
            else
                m_weatherDesc = "Cloudy";
        }
    }
    else
    {
        m_weatherDesc = "Offline";
        m_weatherTemp = "?\u00B0C";
    }

    reply->deleteLater();
    update();
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
        dragPos = event->pos();
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton)
        move(event->globalPosition().toPoint() - dragPos);
}

void MainWindow::contextMenuEvent(QContextMenuEvent* event)
{
    QMenu menu(this);

    // Create actions
    QAction* setupAct = menu.addAction("Setup...");
    QAction* hideAct = menu.addAction("Hide");
    QAction* startPosAct = menu.addAction("Start position");
    menu.addSeparator();
    QAction* calendarAct = menu.addAction("Calendar...");
    QAction* shutdownAct = menu.addAction("Set Shut Down PC...");
    QAction* worldMapAct = menu.addAction("World Map...");
    menu.addSeparator();
    QAction* aboutAct = menu.addAction("About...");
    menu.addSeparator();
    QAction* exitAct = menu.addAction("Exit");

    // Connect actions to slots
    connect(setupAct, &QAction::triggered, this, &MainWindow::onMenuSetup);
    connect(hideAct, &QAction::triggered, this, &MainWindow::onMenuHide);
    connect(startPosAct, &QAction::triggered, this, &MainWindow::onMenuStartPosition);
    connect(calendarAct, &QAction::triggered, this, &MainWindow::onMenuCalendar);
    connect(shutdownAct, &QAction::triggered, this, &MainWindow::onMenuShutdown);
    connect(worldMapAct, &QAction::triggered, this, &MainWindow::onMenuWorldMap);
    connect(aboutAct, &QAction::triggered, this, &MainWindow::onMenuAbout);
    connect(exitAct, &QAction::triggered, this, &MainWindow::onMenuExit);

    // Show menu at mouse position
    menu.exec(event->globalPos());
}

void MainWindow::onTrayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::DoubleClick)
    {
        if (isVisible())
        {
            hide();
        }
        else
        {
            show();
            activateWindow();
        }
    }
}

void MainWindow::onMenuHide()
{
    if (isVisible())
    {
        hide();
    }
    else
    {
        show();
        activateWindow();
    }
}

void MainWindow::onMenuStartPosition()
{
    // Move window to top-right corner (standard behavior)
    if (auto* screen = QGuiApplication::primaryScreen())
    {
        QRect screenRect = screen->availableGeometry();
        int x = screenRect.right() - width() - 20;
        int y = screenRect.top() + 20;
        move(x, y);
    }
}

void MainWindow::onMenuCalendar()
{
    CalendarDialog dlg(this);
    dlg.exec(); // Show as modal dialog
}

void MainWindow::onMenuShutdown()
{
    ShutdownDialog dlg(this);

    ShutdownDialog::ShutdownData data;
    data.time = m_shutdownTime;
    data.isEnabled = m_isShutdownEnabled;
    data.isSleep = m_isSleepMode;

    dlg.setData(data);

    if (dlg.exec() == QDialog::Accepted)
    {
        ShutdownDialog::ShutdownData newData = dlg.getData();
        m_shutdownTime = newData.time;
        m_isShutdownEnabled = newData.isEnabled;
        m_isSleepMode = newData.isSleep;
        m_alreadyExecuted = false; // Reset trigger

        saveSettings(); // Don't forget to add these to save/loadSettings
    }
}

void MainWindow::onMenuWorldMap()
{
    // We create it on heap but with 'this' as parent so it's managed
    // Or just use a local variable for a modal dialog
    WorldMapDialog dlg(this);
    dlg.exec();
}

void MainWindow::onMenuAbout()
{
    AboutDialog dlg(this);
    dlg.exec();
}

void MainWindow::onMenuExit()
{
    saveSettings();
    qApp->quit();
}

void MainWindow::loadSettings()
{
    // QSettings handles INI format automatically
    QSettings settings("clock_qt.ini", QSettings::IniFormat);

    settings.beginGroup("Settings");
    m_bSeconds = settings.value("chkSeconds", true).toBool();
    m_bGMT = settings.value("chkGMT", false).toBool();
    m_bDate = settings.value("chkDate", true).toBool();
    m_bDay = settings.value("chkDay", true).toBool();
    m_bMoving = settings.value("chkMoving", true).toBool();
    m_bTopMost = settings.value("chkAlwaysOnTop", false).toBool();
    m_bTransparent = settings.value("chkTransparent", false).toBool();
    m_bBorder = settings.value("chkBorder", true).toBool();
    m_bSmooth = settings.value("chkSmooth", true).toBool();
    m_bTickTack = settings.value("chkTickTack", false).toBool();
    m_b1530 = settings.value("chk1530", false).toBool();
    m_bHours = settings.value("chkHours", false).toBool();
    m_bDigitalClock = settings.value("chkDigitalClock", true).toBool();
    m_b24Hours = settings.value("chk24Hours", true).toBool();
    m_bCalendar = settings.value("chkCalendar", true).toBool();
    m_bSysMon = settings.value("chkSysMon", true).toBool();
    m_bPing = settings.value("chkPing", true).toBool();
    m_bWeather = settings.value("chkWeather", false).toBool();
    m_nOpacity = settings.value("frmOpacity", 80).toInt();

    m_strPingAddress = settings.value("pingAddr", "8.8.8.8").toString();
    m_strWeatherCity = settings.value("weatherCity", "Odesa,UA").toString();
    m_strWeatherUrl = settings.value("weatherUrl", "").toString();

    // Load position
    int x = settings.value("deskX", -1).toInt();
    int y = settings.value("deskY", -1).toInt();
    if (x != -1 && y != -1)
    {
        move(x, y);
    }
    settings.endGroup();
}

void MainWindow::saveSettings()
{
    QSettings settings("clock_qt.ini", QSettings::IniFormat);

    settings.beginGroup("Settings");
    settings.setValue("chkSeconds", m_bSeconds);
    settings.setValue("chkGMT", m_bGMT);
    settings.setValue("chkDate", m_bDate);
    settings.setValue("chkDay", m_bDay);
    settings.setValue("chkMoving", m_bMoving);
    settings.setValue("chkAlwaysOnTop", m_bTopMost);
    settings.setValue("chkTransparent", m_bTransparent);
    settings.setValue("chkBorder", m_bBorder);
    settings.setValue("chkSmooth", m_bSmooth);
    settings.setValue("chkTickTack", m_bTickTack);
    settings.setValue("chk1530", m_b1530);
    settings.setValue("chkHours", m_bHours);
    settings.setValue("chkDigitalClock", m_bDigitalClock);
    settings.setValue("chk24Hours", m_b24Hours);
    settings.setValue("chkCalendar", m_bCalendar);
    settings.setValue("chkSysMon", m_bSysMon);
    settings.setValue("chkPing", m_bPing);
    settings.setValue("chkWeather", m_bWeather);
    settings.setValue("frmOpacity", m_nOpacity);
    settings.setValue("pingAddr", m_strPingAddress);
    settings.setValue("weatherCity", m_strWeatherCity);
    settings.setValue("weatherUrl", m_strWeatherUrl);

    // Save position
    settings.setValue("deskX", x());
    settings.setValue("deskY", y());
    settings.endGroup();
}

void MainWindow::applySettings()
{
    // 1. Opacity
    setWindowOpacity(m_nOpacity / 100.0);

    // 2. Always on Top
    Qt::WindowFlags flags = windowFlags();
    if (m_bTopMost)
    {
        flags |= Qt::WindowStaysOnTopHint;
    }
    else
    {
        flags &= ~Qt::WindowStaysOnTopHint;
    }

    // 3. Tool window (no taskbar icon)
    flags |= Qt::Tool;
    flags |= Qt::FramelessWindowHint;

    if (windowFlags() != flags)
    {
        setWindowFlags(flags);
        show(); // Required to re-apply flags in Qt
    }

    // 4. Smooth movement (Timer interval)
    if (timer)
    {
        timer->stop();
        timer->start(m_bSmooth ? 200 : 1000);
    }

}

void MainWindow::onMenuSetup()
{
    SetupDialog dlg(this);

    // Fill dialog with current MainWindow values
    SetupDialog::SettingsData data;
    data.showSeconds = m_bSeconds;
    data.showDay = m_bDay;
    data.showDate = m_bDate;
    data.isGmt = m_bGMT;
    data.isTransparent = m_bTransparent;
    data.isSmooth = m_bSmooth;
    data.hasBorder = m_bBorder;
    data.soundTickTack = m_bTickTack;
    data.sound1530 = m_b1530;
    data.soundHours = m_bHours;
    data.showDigital = m_bDigitalClock;
    data.is24h = m_b24Hours;
    data.showCalendar = m_bCalendar;
    data.showSysMon = m_bSysMon;
    data.isMoving = m_bMoving;
    data.isAlwaysOnTop = m_bTopMost;
    data.usePing = m_bPing;
    data.pingAddr = m_strPingAddress;
    data.useWeather = m_bWeather;
    data.weatherPlace = m_strWeatherCity;
    data.weatherUrl = m_strWeatherUrl;
    data.opacity = m_nOpacity;

    dlg.setSettings(data);

    if (dlg.exec() == QDialog::Accepted)
    {
        SetupDialog::SettingsData newData = dlg.getSettings();

        // Update MainWindow variables
        m_bSeconds = newData.showSeconds;
        m_bDay = newData.showDay;
        m_bDate = newData.showDate;
        m_bGMT = newData.isGmt;
        m_bTransparent = newData.isTransparent;
        m_bSmooth = newData.isSmooth;
        m_bBorder = newData.hasBorder;
        m_bTickTack = newData.soundTickTack;
        m_b1530 = newData.sound1530;
        m_bHours = newData.soundHours;
        m_bDigitalClock = newData.showDigital;
        m_b24Hours = newData.is24h;
        m_bCalendar = newData.showCalendar;
        m_bSysMon = newData.showSysMon;
        m_bMoving = newData.isMoving;
        m_bTopMost = newData.isAlwaysOnTop;
        m_bPing = newData.usePing;
        m_strPingAddress = newData.pingAddr;
        m_bWeather = newData.useWeather;
        m_strWeatherCity = newData.weatherPlace;
        m_strWeatherUrl = newData.weatherUrl;
        m_nOpacity = newData.opacity;

        applySettings();
        saveSettings();
        update();
    }
}

void MainWindow::enterEvent(QEnterEvent* event)
{
    m_bMouseOver = true;
    update(); // Redraw to show glass effect
}

void MainWindow::leaveEvent(QEvent* event)
{
    m_bMouseOver = false;
    update(); // Redraw to hide glass effect
}

void MainWindow::updateThemeColor()
{
    // 1. If mouse is over, background is dark glass (Alpha 160), so text MUST be white
    if (m_bMouseOver)
    {
        m_dynamicColor = Qt::white;
        return;
    }

    // 2. Analyze background under the window
    QScreen* screen = QGuiApplication::primaryScreen();
    if (!screen) return;

    // Grab the area where the window is located
    // Note: grabWindow(0, ...) grabs the desktop content
    QPixmap screenshot = screen->grabWindow(0, x(), y(), width(), height());
    QImage img = screenshot.toImage();

    if (img.isNull()) return;

    // Sample 5 points like in your MFC code (center + 4 corners)
    QList<QPoint> points = 
    {
        QPoint(width() / 2, height() / 2),
        QPoint(10, 10),
        QPoint(width() - 10, 10),
        QPoint(10, height() - 10),
        QPoint(width() - 10, height() - 10)
    };

    double totalLuminance = 0;
    int validPoints = 0;

    for (const QPoint& pt : points)
    {
        if (img.valid(pt))
        {
            QRgb rgb = img.pixel(pt);
            // Standard luminance formula: 0.299*R + 0.587*G + 0.114*B
            totalLuminance += (0.299 * qRed(rgb) + 0.587 * qGreen(rgb) + 0.114 * qBlue(rgb));
            validPoints++;
        }
    }

    double avgLuminance = (validPoints > 0) ? (totalLuminance / validPoints) : 0;

    // If background is light (> 128) -> Black text, else -> White text
    m_dynamicColor = (avgLuminance > 128) ? Qt::black : Qt::white;
}

void MainWindow::playHourlyChime(int hours)
{
    int count = hours % 12;
    if (count == 0)
        count = 12;

    // In Qt, we can set how many times to repeat the sound
    // count is the total number of plays
    m_soundBoom.setLoopCount(count);
    m_soundBoom.play();
}

void MainWindow::createTrayIcon()
{
    m_trayIcon = new QSystemTrayIcon(this);

    // Set icon from your resources
    m_trayIcon->setIcon(QIcon(":/Clock_qt.ico"));

    // Create context menu for tray
    QMenu* trayMenu = new QMenu(this);

    QAction* setupAct = trayMenu->addAction("Setup...");
    QAction* hideAct = trayMenu->addAction("Hide");
    trayMenu->addSeparator();
    QAction* aboutAct = trayMenu->addAction("About...");
    trayMenu->addSeparator();
    QAction* exitAct = trayMenu->addAction("Exit");

    connect(setupAct, &QAction::triggered, this, &MainWindow::onMenuSetup);
    connect(hideAct, &QAction::triggered, this, &MainWindow::onMenuHide);
    connect(aboutAct, &QAction::triggered, this, &MainWindow::onMenuAbout);
    connect(exitAct, &QAction::triggered, this, &MainWindow::onMenuExit);

    m_trayIcon->setContextMenu(trayMenu);

    // Handle double click on tray icon
    connect(m_trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::onTrayIconActivated);

    m_trayIcon->show();
}

void MainWindow::executeShutdown()
{
    saveSettings();

#ifdef Q_OS_WIN
    QString cmd = m_isSleepMode ? "rundll32.exe powrprof.dll,SetSuspendState 0,1,0"
        : "shutdown /s /f /t 0";
#else
    QString cmd = m_isSleepMode ? "systemctl suspend"
        : "shutdown -h now";
#endif
    QProcess::startDetached(cmd);
}

