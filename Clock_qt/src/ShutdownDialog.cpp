#include "ShutdownDialog.h"

ShutdownDialog::ShutdownDialog(QWidget* parent) : QDialog(parent)
{
    setWindowTitle("Shut down");
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::CustomizeWindowHint);

    setWindowOpacity(0.85);
    setFixedSize(250, 180);
    setupUi();
}

void ShutdownDialog::setupUi()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Time picker row
    QHBoxLayout* timeLayout = new QHBoxLayout();
    timeLayout->addWidget(new QLabel("Time shut down:"));
    m_timePicker = new QTimeEdit(this);
    m_timePicker->setDisplayFormat("HH:mm:ss");
    timeLayout->addWidget(m_timePicker);
    mainLayout->addLayout(timeLayout);

    // Checkboxes
    m_chkEnabled = new QCheckBox("Shut down \"Off\"", this);
    m_chkSleep = new QCheckBox("Sleep", this);
    mainLayout->addWidget(m_chkEnabled);
    mainLayout->addWidget(m_chkSleep);

    // Buttons
    QHBoxLayout* btnLayout = new QHBoxLayout();
    m_btnOk = new QPushButton("OK", this);
    m_btnCancel = new QPushButton("Cancel", this);
    btnLayout->addWidget(m_btnOk);
    btnLayout->addWidget(m_btnCancel);
    mainLayout->addLayout(btnLayout);

    // Connections
    connect(m_btnOk, &QPushButton::clicked, this, &QDialog::accept);
    connect(m_btnCancel, &QPushButton::clicked, this, &QDialog::reject);
    connect(m_chkEnabled, &QCheckBox::toggled, this, &ShutdownDialog::updateUiState);

    updateUiState();
}

void ShutdownDialog::updateUiState()
{
    bool checked = m_chkEnabled->isChecked();
    m_chkEnabled->setText(checked ? "Shut down \"On\"" : "Shut down \"Off\"");

    m_timePicker->setEnabled(checked);
    m_chkSleep->setEnabled(checked);

    if (!checked)
    {
        m_chkSleep->setChecked(false);
    }
}

void ShutdownDialog::setData(const ShutdownData& data)
{
    m_timePicker->setTime(data.time);
    m_chkEnabled->setChecked(data.isEnabled);
    m_chkSleep->setChecked(data.isSleep);
    updateUiState();
}

ShutdownDialog::ShutdownData ShutdownDialog::getData() const
{
    ShutdownData data;
    data.time = m_timePicker->time();
    data.isEnabled = m_chkEnabled->isChecked();
    data.isSleep = m_chkSleep->isChecked();
    return data;
}