#include "MainWindow.h"
#include <QDateTime>
#include <QMouseEvent>
#include <QFontDatabase>

MainWindow::MainWindow(QWidget* parent) : QWidget(parent)
{
    // Window settings
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground);
    
    setFixedWidth(122);
    setFixedHeight(530); // Height will be dynamic later

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::onTimerTick);
    timer->start(200);

    // Load custom digital font from resources
    int fontId = QFontDatabase::addApplicationFont(":/digital_7italic.ttf");
    if (fontId != -1)
    {
        m_digitalFontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    }

    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::onWeatherReceived);
    updateWeather(); // Initial update
}

void MainWindow::onTimerTick()
{
    // Update system metrics
    currentCpu = SystemMonitor::getCpuUsage();
    currentRam = SystemMonitor::getRamUsage();

    if (m_bTickTack)
    {
        tickSound.play();
    }

    // Update ping every 5 seconds
    static int pingCounter = 0;
    if (pingCounter++ % 25 == 0) // 200ms * 25 = 5 seconds
    {
        updatePing();
    }

    static int weatherCounter = 0;
    if (weatherCounter++ % 9000 == 0) // 200ms * 9000 = 30 minutes
    {
        updateWeather();
    }

    // Trigger repaint
    update();
}

void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    // Draw panel background
    QPainterPath path;
    path.addRoundedRect(rect().adjusted(1, 1, -1, -1), 15, 15);

    QColor bgColor(20, 20, 20, 160);
    p.fillPath(path, bgColor);
    p.setPen(QPen(QColor(255, 255, 255, 50), 1));
    p.drawPath(path);

    drawAnalogClock(p);
    drawDigitalClock(p, 125);
    drawCalendar(p, 175);
    drawSystemMonitor(p, 285);
    drawPing(p, 355);
    drawWeather(p, 380);
}

void MainWindow::drawAnalogClock(QPainter& p)
{
    p.save();

    p.setRenderHint(QPainter::Antialiasing);
    p.setRenderHint(QPainter::TextAntialiasing);

    // Adjusted dimensions to match the smaller look
    float xCenter = width() / 2.0f; // 75.0f
    float yCenter = 65.0f;          // Moved slightly up
    float radius = 54.0f;           // Reduced radius
    float borderThickness = 5.0f;   // Slightly thinner border
    float innerRadius = radius - borderThickness - 1.0f;

    // 1. Face background
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(242, 238, 225));
    p.drawEllipse(QPointF(xCenter, yCenter), radius, radius);

    // 2. Borders (Black and Gray)
    p.setBrush(Qt::NoBrush);
    p.setPen(QPen(Qt::black, borderThickness));
    p.drawEllipse(QPointF(xCenter, yCenter), radius - borderThickness / 2.0f, radius - borderThickness / 2.0f);

    p.setPen(QPen(Qt::gray, 1.5f));
    p.drawEllipse(QPointF(xCenter, yCenter), radius - borderThickness / 2.0f, radius - borderThickness / 2.0f);

    // 3. Marks (Hours and Minutes)
    for (int i = 0; i < 60; ++i)
    {
        p.save();
        p.translate(xCenter, yCenter);
        p.rotate(i * 6.0);

        if (i % 5 == 0)
        {
            // Hour marks
            p.setPen(QPen(Qt::black, (i % 15 == 0) ? 3.5f : 1.8f));
            p.drawLine(0, -innerRadius + 8, 0, -innerRadius - 2);
        }
        else
        {
            // Minute dots
            p.setBrush(Qt::black);
            p.setPen(Qt::NoPen);
            p.drawEllipse(QRectF(-1.1, -innerRadius - 1.2, 2.2, 2.2));
        }
        p.restore();
    }

    // 4. Text elements (Scaled to fit smaller radius)
    QDateTime now = QDateTime::currentDateTime();

    // LAN - Moved up (multiplier changed from 0.55 to 0.62)
    QFont fontLan("Arial", 10);
    fontLan.setItalic(true);    // Italic font
    fontLan.setUnderline(true); // Underlined
    p.setFont(fontLan);
    p.setPen(QColor(240, 128, 128));
    p.drawText(QRectF(xCenter - 25, yCenter - 3 - innerRadius * 0.62, 50, 15), Qt::AlignCenter, "LAN");

    // C++ - Moved up (multiplier changed from 0.32 to 0.42)
    QFont fontCpp("Arial", 6, QFont::Bold);
    p.setFont(fontCpp);
    p.setPen(Qt::gray);
    p.drawText(QRectF(xCenter - 25, yCenter - innerRadius * 0.42, 50, 12), Qt::AlignCenter, "C++");

    // Day - Position remains the same
    bool isWeekend = (now.date().dayOfWeek() == 6 || now.date().dayOfWeek() == 7);
    p.setPen(isWeekend ? QColor(240, 128, 128) : Qt::gray);
    p.drawText(QRectF(xCenter - 25, yCenter + innerRadius * 0.10, 50, 12), Qt::AlignCenter, now.toString("ddd").toUpper());

    // Date - Position remains the same
    p.setPen(Qt::gray);
    p.drawText(QRectF(xCenter - 35, yCenter + innerRadius * 0.35, 70, 12), Qt::AlignCenter, now.toString("dd-MM-yy"));
    // 5. Hands
    QTime time = now.time();

    // Hour hand
    float hourAngle = 30.0f * (time.hour() % 12 + time.minute() / 60.0f);
    drawHandHelper(p, xCenter, yCenter, hourAngle, innerRadius * 0.55f, 5.5f, true);

    // Minute hand
    float minuteAngle = 6.0f * (time.minute() + time.second() / 60.0f);
    drawHandHelper(p, xCenter, yCenter, minuteAngle, innerRadius * 0.82f, 3.8f, true);

    // Second hand
    p.save();
    p.translate(xCenter, yCenter);
    p.rotate(time.second() * 6.0f);
    p.setPen(QPen(Qt::red, 1.2f));
    p.drawLine(0, 8, 0, -innerRadius * 0.92f);
    p.restore();

    // Center cap
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

    QDateTime now = QDateTime::currentDateTime();
    QTime time = now.time();

    // Your coordinates (used as Right boundaries)
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

    // Helper lambda to draw right-aligned text like in MFC sfRight
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
    drawDigit(QRectF(p_H1 - 20, bottomRowY, 20, 30), "8");
    drawDigit(QRectF(p_H2 - 20, bottomRowY, 20, 30), "8");
    drawDigit(QRectF(p_Colon - 10, bottomRowY, 20, 30), ":", Qt::AlignCenter);
    drawDigit(QRectF(p_M1 - 20, bottomRowY, 20, 30), "8");
    drawDigit(QRectF(p_M2 - 20, bottomRowY, 20, 30), "8");

    p.setFont(digFontSmall);
    drawDigit(QRectF(p_S1 - 15, bottomRowY + 8, 15, 20), "8");
    drawDigit(QRectF(p_S2 - 15, bottomRowY + 8, 15, 20), "8");

    // 4. Draw actual time data
    p.setPen(Qt::black);

    // Day of week
    p.setFont(digFontSmall);
    QString dayStr = now.toString("ddd").left(2).toUpper();
    drawDigit(QRectF(p_Day - 20, topRowY, 35, 15), dayStr);

    // Date
    drawDigit(QRectF(p_Date - 20, topRowY, 18, 15), now.toString("dd"));

    // Hours
    p.setFont(digFontLarge);
    int hh = time.hour();
    if (hh >= 10)
    {
        drawDigit(QRectF(p_H1 - 20, bottomRowY, 20, 30), QString::number(hh / 10));
    }
    drawDigit(QRectF(p_H2 - 20, bottomRowY, 20, 30), QString::number(hh % 10));

    // Colon
    drawDigit(QRectF(p_Colon - 10, bottomRowY, 20, 30), ":", Qt::AlignCenter);

    // Minutes
    drawDigit(QRectF(p_M1 - 20, bottomRowY, 20, 30), QString::number(time.minute() / 10));
    drawDigit(QRectF(p_M2 - 20, bottomRowY, 20, 30), QString::number(time.minute() % 10));

    // Seconds
    p.setFont(digFontSmall);
    drawDigit(QRectF(p_S1 - 15, bottomRowY + 8, 15, 20), QString::number(time.second() / 10));
    drawDigit(QRectF(p_S2 - 15, bottomRowY + 8, 15, 20), QString::number(time.second() % 10));

    p.restore();
}

void MainWindow::drawCalendar(QPainter& p, int yStart)
{
    p.save();

    float xCenter = width() / 2.0f;
    float calW = width() - 20.0f;
    float calX = 10.0f;
    float calY = yStart + 2.0f; // Moved slightly up

    QDate today = QDate::currentDate();
    QDate firstDayOfMonth(today.year(), today.month(), 1);

    // Determine the starting column (0 = Monday, 6 = Sunday)
    int startDay = firstDayOfMonth.dayOfWeek() - 1;
    int daysInMonth = today.daysInMonth();

    // 1. Draw Header (Month Year)
    QFont fontHeader("Arial", 8, QFont::Bold);
    p.setFont(fontHeader);
    p.setPen(Qt::white);
    p.drawText(QRectF(0, calY, width(), 15), Qt::AlignCenter, today.toString("MMMM yyyy"));

    // 2. Draw Day Names (M T W T F S S)
    QFont fontDays("Arial", 6);
    p.setFont(fontDays);
    const QStringList dayNames = { "M", "T", "W", "T", "F", "S", "S" };
    float cellW = calW / 7.0f;

    for (int i = 0; i < 7; ++i)
    {
        // Highlight weekends in red/coral
        if (i >= 5)
        {
            p.setPen(QColor(240, 128, 128));
        }
        else
        {
            p.setPen(Qt::white);
        }
        // Moved up from +25 to +18
        p.drawText(QRectF(calX + i * cellW, calY + 18, cellW, 12), Qt::AlignCenter, dayNames[i]);
    }

    // 3. Draw Dates Grid
    int row = 0;
    for (int d = 1; d <= daysInMonth; ++d)
    {
        int col = (startDay + d - 1) % 7;
        if (d > 1 && col == 0)
        {
            row++;
        }

        float x = calX + col * cellW;
        // Moved up from +45 to +32, and reduced row spacing from 15 to 12
        float y = calY + 32 + row * 12;

        // Highlight current day background
        if (d == today.day())
        {
            p.setPen(Qt::NoPen);
            p.setBrush(QColor(255, 255, 255, 60));
            // Adjusted highlight rectangle size
            p.drawRoundedRect(QRectF(x + 2, y - 1, cellW - 4, 12), 2, 2);
        }

        // Set text color (weekend vs weekday)
        if (col >= 5)
        {
            p.setPen(QColor(240, 128, 128));
        }
        else
        {
            p.setPen(Qt::white);
        }

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

    // 1. Draw Separator line
    p.setPen(QPen(QColor(255, 255, 255, 30), 1));
    p.drawLine(QPointF(margin, monY), QPointF((float)width() - margin, monY));

    QFont fontLabel("Arial", 7, QFont::Bold);
    QFont fontValue("Arial", 7);

    // 2. CPU Section
    p.setPen(Qt::white); // Ensure color is white
    p.setFont(fontLabel);
    p.drawText(QRectF(margin, monY + 5, 40, 12), Qt::AlignLeft, "CPU");

    p.setFont(fontValue);
    p.drawText(QRectF((float)width() - margin - 40, monY + 5, 40, 12), Qt::AlignRight, QString::number((int)currentCpu) + "%");

    // CPU Bar background
    QRectF cpuRect(margin, monY + 18, barW, barH);
    p.setBrush(QColor(0, 0, 0, 100));
    p.setPen(QPen(QColor(255, 255, 255, 40), 1));
    p.drawRect(cpuRect);

    // CPU Bar fill (Green)
    if (currentCpu > 0)
    {
        float cpuFill = (barW * currentCpu) / 100.0f;
        p.setPen(Qt::NoPen);
        p.setBrush(QColor(80, 220, 80));
        p.drawRect(QRectF(margin + 1, monY + 19, cpuFill - 1, barH - 2));
    }

    // 3. RAM Section
    p.setPen(Qt::white); // Re-set pen to white for RAM label
    p.setFont(fontLabel);
    // Draw RAM label at monY + 35
    p.drawText(QRectF(margin, monY + 35, 40, 12), Qt::AlignLeft, "RAM");

    p.setFont(fontValue);
    p.drawText(QRectF((float)width() - margin - 40, monY + 35, 40, 12), Qt::AlignRight, QString::number((int)currentRam) + "%");

    // RAM Bar background
    QRectF ramRect(margin, monY + 48, barW, barH);
    p.setBrush(QColor(0, 0, 0, 100));
    p.setPen(QPen(QColor(255, 255, 255, 40), 1));
    p.drawRect(ramRect);

    // RAM Bar fill (Blue)
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

    // 1. Draw Separator line
    p.setPen(QPen(QColor(255, 255, 255, 30), 1));
    p.drawLine(QPointF(margin, pingY), QPointF((float)width() - margin, pingY));

    QFont fontLabel("Arial", 7, QFont::Bold);
    QFont fontValue("Arial", 7, QFont::StyleItalic);

    // 2. Draw Label (Left)
    p.setPen(Qt::white);
    p.setFont(fontLabel);
    QString label = "Ping: " + m_pingAddress;

    // Truncate label if it's too long
    QFontMetrics fm(fontLabel);
    QString elidedLabel = fm.elidedText(label, Qt::ElideRight, width() - 50);
    p.drawText(QRectF(margin, pingY + 8, width() - 50, 15), Qt::AlignLeft, elidedLabel);

    // 3. Draw Value (Right)
    QString valStr;
    QColor valColor;

    if (m_pingValue == -1)
    {
        valStr = "Error";
        valColor = QColor(240, 128, 128); // Reddish
    }
    else
    {
        valStr = QString::number(m_pingValue) + " ms";
        // Color based on latency
        if (m_pingValue < 100)
            valColor = QColor(80, 220, 80);  // Green
        else if (m_pingValue < 250)
            valColor = Qt::yellow;
        else
            valColor = QColor(240, 128, 128); // Red
    }

    p.setPen(valColor);
    p.setFont(fontValue);
    p.drawText(QRectF((float)width() - margin - 40, pingY + 8, 40, 15), Qt::AlignRight, valStr);

    p.restore();
}

void MainWindow::updatePing()
{
    if (m_isPingInProgress)
    {
        return;
    }

    m_isPingInProgress = true;

    QProcess* pingProcess = new QProcess(this);

    QStringList parameters;
#ifdef Q_OS_WIN
    parameters << "-n" << "1" << "-w" << "1000" << m_pingAddress;
#else
    parameters << "-c" << "1" << "-W" << "1" << m_pingAddress;
#endif

    connect(pingProcess, &QProcess::finished, [this, pingProcess](int exitCode)
        {
            if (exitCode == 0)
            {
                QString output = QString::fromLocal8Bit(pingProcess->readAllStandardOutput());

                // Parse "time=XXms" or "час=XXмс"
                int index = output.indexOf("time=");
                if (index == -1)
                    index = output.indexOf("time<"); // For very fast pings on Windows

                if (index != -1)
                {
                    int start = index + 5;
                    int end = output.indexOf("ms", start);
                    if (end != -1)
                    {
                        m_pingValue = output.mid(start, end - start).trimmed().toInt();
                    }
                }
                else
                {
                    m_pingValue = -1;
                }
            }
            else
            {
                m_pingValue = -1;
            }

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
    float xCenter = width() / 2.0f;

    // 1. Draw Separator line
    p.setPen(QPen(QColor(255, 255, 255, 30), 1));
    p.drawLine(QPointF(margin, weaY), QPointF((float)width() - margin, weaY));

    // 2. Draw City Name (Top Left)
    QFont fontCity("Arial", 7, QFont::Bold);
    p.setFont(fontCity);
    p.setPen(Qt::white);
    p.drawText(QRectF(margin, weaY + 8, width() - 20, 15), Qt::AlignLeft, m_weatherCity);

    // 3. Draw Temperature (Center, Large)
    QFont fontTemp("Arial", 12, QFont::Bold);
    p.setFont(fontTemp);
    p.drawText(QRectF(0, weaY + 18, width(), 25), Qt::AlignCenter, m_weatherTemp);

    // 4. Draw Description (Center, below temperature)
    QFont fontDesc("Arial", 7);
    p.setFont(fontDesc);
    p.drawText(QRectF(0, weaY + 40, width(), 15), Qt::AlignCenter, m_weatherDesc);

    p.restore();
}

void MainWindow::updateWeather()
{
    if (networkManager)
    {
        networkManager->get(QNetworkRequest(QUrl(m_weatherUrl)));
    }
}

void MainWindow::onWeatherReceived(QNetworkReply* reply)
{
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

void MainWindow::onMenuSetup()
{
    SetupDialog dlg(this);

    // Fill dialog with current values
    SetupDialog::SettingsData data;
    data.showSeconds = true; // Replace with your actual variables
    // ... fill all other fields ...
    dlg.setSettings(data);

    if (dlg.exec() == QDialog::Accepted)
    {
        SetupDialog::SettingsData newData = dlg.getSettings();
        // Apply new settings to MainWindow
        // this->m_bSeconds = newData.showSeconds;
        // ...
        update();
    }
}

void MainWindow::onMenuHide()
{
    this->hide();
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
    // Placeholder for Calendar dialog
}

void MainWindow::onMenuShutdown()
{
    // Placeholder for Shutdown dialog
}

void MainWindow::onMenuWorldMap()
{
    // Placeholder for World Map dialog
}

void MainWindow::onMenuAbout()
{
    // Placeholder for About dialog
}

void MainWindow::onMenuExit()
{
    qApp->quit();
}

