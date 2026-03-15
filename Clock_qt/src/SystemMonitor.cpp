#include "SystemMonitor.h"
#include <QtGlobal>

#ifdef Q_OS_WIN
#include <windows.h>
#else
#include <fstream>
#include <string>
#endif

float SystemMonitor::getCpuUsage()
{
#ifdef Q_OS_WIN
    static ULONGLONG lastIdleTime = 0, lastKernelTime = 0, lastUserTime = 0;
    FILETIME idleTime, kernelTime, userTime;
    if (GetSystemTimes(&idleTime, &kernelTime, &userTime))
    {
        auto FileTimeToQuad = [](FILETIME ft) { return ((((ULONGLONG)ft.dwHighDateTime) << 32) | ft.dwLowDateTime); };
        ULONGLONG nowIdle = FileTimeToQuad(idleTime);
        ULONGLONG nowKernel = FileTimeToQuad(kernelTime);
        ULONGLONG nowUser = FileTimeToQuad(userTime);

        ULONGLONG diffIdle = nowIdle - lastIdleTime;
        ULONGLONG diffKernel = nowKernel - lastKernelTime;
        ULONGLONG diffUser = nowUser - lastUserTime;
        ULONGLONG diffTotal = diffKernel + diffUser;

        lastIdleTime = nowIdle; lastKernelTime = nowKernel; lastUserTime = nowUser;
        if (diffTotal == 0) return 0.0f;
        return (float)(diffTotal - diffIdle) * 100.0f / diffTotal;
    }
    return 0.0f;
#else
    // Linux implementation (reading /proc/stat)
    return 10.0f; // Placeholder for now
#endif
}

float SystemMonitor::getRamUsage()
{
#ifdef Q_OS_WIN
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    if (GlobalMemoryStatusEx(&memInfo))
    {
        return (float)memInfo.dwMemoryLoad;
    }
    return 0.0f;
#else
    // Linux implementation (reading /proc/meminfo)
    return 30.0f; // Placeholder for now
#endif
}