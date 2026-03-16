#include "SystemMonitor.h"
#include <QtGlobal>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#ifdef Q_OS_WIN
#include <windows.h> // Цей рядок обов'язковий для FILETIME та GetSystemTimes
#endif

#ifdef Q_OS_LINUX
#include <unistd.h>
#endif

float SystemMonitor::getCpuUsage()
{
#ifdef Q_OS_WIN
    // Ваш існуючий код для Windows
    static ULONGLONG lastIdleTime = 0, lastKernelTime = 0, lastUserTime = 0;
    FILETIME idleTime, kernelTime, userTime;
    if (GetSystemTimes(&idleTime, &kernelTime, &userTime))
    {
        auto FileTimeToQuad = [](FILETIME ft) 
            { 
                return ((((ULONGLONG)ft.dwHighDateTime) << 32) | ft.dwLowDateTime); 
            };
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
    // Linux implementation
    static long long prevIdle = 0, prevTotal = 0;
    std::ifstream file("/proc/stat");
    std::string line;
    std::getline(file, line);
    std::istringstream ss(line);
    std::string cpu;
    long long user, nice, system, idle, iowait, irq, softirq, steal;
    ss >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;

    long long idleTime = idle + iowait;
    long long totalTime = user + nice + system + idle + iowait + irq + softirq + steal;

    float usage = 0.0f;
    if (totalTime > prevTotal) 
    {
        usage = (float)(1.0 - (double)(idleTime - prevIdle) / (totalTime - prevTotal)) * 100.0f;
    }
    prevIdle = idleTime;
    prevTotal = totalTime;
    return usage;
#endif
}

float SystemMonitor::getRamUsage()
{
#ifdef Q_OS_WIN
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    if (GlobalMemoryStatusEx(&memInfo)) return (float)memInfo.dwMemoryLoad;
    return 0.0f;
#else
    // Linux implementation
    std::ifstream file("/proc/meminfo");
    std::string line;
    long long memTotal = 0, memAvailable = 0;
    while (std::getline(file, line)) {
        if (line.substr(0, 8) == "MemTotal") sscanf(line.c_str(), "MemTotal: %lld kB", &memTotal);
        if (line.substr(0, 12) == "MemAvailable") sscanf(line.c_str(), "MemAvailable: %lld kB", &memAvailable);
    }
    if (memTotal == 0) return 0.0f;
    return (float)((memTotal - memAvailable) * 100.0f / memTotal);
#endif
}