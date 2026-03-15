#ifndef SYSTEMMONITOR_H
#define SYSTEMMONITOR_H

#include <QtGlobal>

class SystemMonitor {
public:
    static float getCpuUsage();
    static float getRamUsage();
};

#endif