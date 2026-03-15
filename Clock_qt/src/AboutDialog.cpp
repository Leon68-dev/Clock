#include "AboutDialog.h"
#include <QDateTime>
#include <QSysInfo>
#include <QPixmap>
#include <QHBoxLayout>

#ifdef Q_OS_WIN
#include <windows.h>
#endif

AboutDialog::AboutDialog(QWidget* parent) : QDialog(parent)
{
    setWindowTitle("About");
    setFixedSize(320, 200);
    setWindowOpacity(0.85);
    setupUi();
}

void AboutDialog::setupUi()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Top section: Image and Version info
    QHBoxLayout* topLayout = new QHBoxLayout();

    QLabel* lblImg = new QLabel(this);
    QPixmap pix(":/bitmap2.bmp");
    lblImg->setPixmap(pix.scaled(120, 90, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    topLayout->addWidget(lblImg);

    QVBoxLayout* infoLayout = new QVBoxLayout();
    infoLayout->addWidget(new QLabel("C++", this));
    infoLayout->addWidget(new QLabel("Clock Version 2.1.0", this));

    int year = QDate::currentDate().year();
    infoLayout->addWidget(new QLabel(QString("Copyright (C) 1998-%1").arg(year), this));

    topLayout->addLayout(infoLayout);
    mainLayout->addLayout(topLayout);

    // System info section
    QFrame* line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    mainLayout->addWidget(line);

    QLabel* lblOs = new QLabel(getOsVersion(), this);
    lblOs->setWordWrap(true);
    mainLayout->addWidget(lblOs);

    QLabel* lblMem = new QLabel(getMemoryInfo(), this);
    mainLayout->addWidget(lblMem);

    mainLayout->addStretch();

    // OK Button
    QPushButton* btnOk = new QPushButton("OK", this);
    btnOk->setFixedWidth(80);
    mainLayout->addWidget(btnOk, 0, Qt::AlignRight);

    connect(btnOk, &QPushButton::clicked, this, &QDialog::accept);

    this->adjustSize();
}

QString AboutDialog::getOsVersion()
{
    // QSysInfo works on both Windows and Ubuntu
    return QSysInfo::prettyProductName();
}

QString AboutDialog::getMemoryInfo()
{
    QString info;
#ifdef Q_OS_WIN
    MEMORYSTATUSEX memStatus;
    memStatus.dwLength = sizeof(memStatus);
    if (GlobalMemoryStatusEx(&memStatus))
    {
        double totalGB = memStatus.ullTotalPhys / (1024.0 * 1024.0 * 1024.0);
        double availGB = memStatus.ullAvailPhys / (1024.0 * 1024.0 * 1024.0);
        info = QString("Total Physical Memory: %1 GB\nAvailable Physical Memory: %2 GB")
            .arg(totalGB, 0, 'f', 1)
            .arg(availGB, 0, 'f', 1);
    }
#else
    // Basic Linux implementation (can be expanded by reading /proc/meminfo)
    info = "Memory info available in System Monitor";
#endif
    return info;
}