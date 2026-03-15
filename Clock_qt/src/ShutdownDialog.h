#ifndef SHUTDOWNDIALOG_H
#define SHUTDOWNDIALOG_H

#include <QDialog>
#include <QTimeEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class ShutdownDialog : public QDialog
{
    Q_OBJECT

public:
    struct ShutdownData
    {
        QTime time;
        bool isEnabled;
        bool isSleep;
    };

    explicit ShutdownDialog(QWidget* parent = nullptr);

    void setData(const ShutdownData& data);
    ShutdownData getData() const;

private slots:
    void updateUiState();

private:
    QTimeEdit* m_timePicker;
    QCheckBox* m_chkEnabled;
    QCheckBox* m_chkSleep;
    QPushButton* m_btnOk;
    QPushButton* m_btnCancel;

    void setupUi();
};

#endif