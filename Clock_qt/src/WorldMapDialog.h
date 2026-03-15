#ifndef WORLDMAPDIALOG_H
#define WORLDMAPDIALOG_H

#include <QDialog>
#include <QPixmap>
#include <QTimer>
#include <QPainterPath>

class WorldMapDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WorldMapDialog(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QPixmap m_mapPixmap;
    QTimer* m_updateTimer;

    void drawDayNightMap(QPainter& p);
};

#endif