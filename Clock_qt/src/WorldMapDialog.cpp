#include "WorldMapDialog.h"
#include <QPainter>
#include <QDateTime>
#include <cmath>

WorldMapDialog::WorldMapDialog(QWidget* parent) : QDialog(parent)
{
    setWindowTitle("World Day/Night Map");
    setFixedSize(1000, 500);

    // Load map from resources
    m_mapPixmap = QPixmap(":/world_map.jpg");

    // Update every minute
    m_updateTimer = new QTimer(this);
    connect(m_updateTimer, &QTimer::timeout, this, QOverload<>::of(&WorldMapDialog::update));
    m_updateTimer->start(60000);
}

void WorldMapDialog::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    if (m_mapPixmap.isNull())
    {
        p.drawText(rect(), Qt::AlignCenter, "Map image not found!");
        return;
    }

    // 1. Draw the world map
    p.drawPixmap(rect(), m_mapPixmap);

    // 2. Calculate Sun and Shadow (UTC)
    QDateTime now = QDateTime::currentDateTimeUtc();
    int dayOfYear = now.date().dayOfYear();
    double hourUTC = now.time().hour() + now.time().minute() / 60.0 + now.time().second() / 3600.0;

    const double PI = 3.14159265358979323846;

    // Sun declination (latitude)
    double sunLat = 23.44 * std::sin(2.0 * PI * (dayOfYear - 81.0) / 365.25);
    // Sun longitude
    double sunLon = (12.0 - hourUTC) * 15.0;

    // 3. Build Terminator Path
    QPainterPath shadowPath;
    QPolygonF points;
    float w = (float)width();
    float h = (float)height();

    for (float x = 0; x <= w; x += 2)
    {
        double lon = (x / w) * 360.0 - 180.0;
        // Terminator formula from your MFC code
        double latRad = std::atan(-std::cos((lon - sunLon) * PI / 180.0) / std::tan(sunLat * PI / 180.0));
        double lat = latRad * 180.0 / PI;
        points.append(QPointF(x, (float)((90.0 - lat) / 180.0 * h)));
    }

    // Close the polygon to fill the night area
    if (sunLat > 0)
    {
        points.append(QPointF(w, h));
        points.append(QPointF(0, h));
    }
    else
    {
        points.append(QPointF(w, 0));
        points.append(QPointF(0, 0));
    }
    shadowPath.addPolygon(points);

    // 4. Draw Shadow (Night)
    // Color: Dark blue/black with transparency (MFC: 215, 5, 5, 20 -> let's use standard semi-transparent)
    p.fillPath(shadowPath, QColor(0, 0, 20, 120));

    // 5. Draw Sun
    float sx = (float)((sunLon + 180.0) / 360.0 * w);
    float sy = (float)((90.0 - sunLat) / 180.0 * h);

    p.setBrush(Qt::yellow);
    // Use QColor for orange instead of Qt::orange
    p.setPen(QPen(QColor(255, 165, 0), 1));
    p.drawEllipse(QPointF(sx, sy), 5, 5);

}