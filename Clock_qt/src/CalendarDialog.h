#ifndef CALENDARDIALOG_H
#define CALENDARDIALOG_H

#include <QDialog>
#include <QCalendarWidget>
#include <QPushButton>
#include <QVBoxLayout>

class CalendarDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CalendarDialog(QWidget* parent = nullptr);

private:
    QCalendarWidget* m_calendar;
    QPushButton* m_btnOk;

    void setupUi();
};

#endif