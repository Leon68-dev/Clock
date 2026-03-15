#include "CalendarDialog.h"
#include <QDate>

CalendarDialog::CalendarDialog(QWidget* parent) : QDialog(parent)
{
    setWindowTitle("Calendar");
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::CustomizeWindowHint);

    // Apply transparency (MFC used 216/255 = ~0.85)
    setWindowOpacity(0.85);

    setupUi();

    // Set current date as selected
    m_calendar->setSelectedDate(QDate::currentDate());
}

void CalendarDialog::setupUi()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    m_calendar = new QCalendarWidget(this);
    m_calendar->setGridVisible(true);
    m_calendar->setFirstDayOfWeek(Qt::Monday);
    m_calendar->setHorizontalHeaderFormat(QCalendarWidget::SingleLetterDayNames);

    m_btnOk = new QPushButton("OK", this);

    mainLayout->addWidget(m_calendar);
    mainLayout->addWidget(m_btnOk);

    connect(m_btnOk, &QPushButton::clicked, this, &QDialog::accept);
}