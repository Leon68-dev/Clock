#ifndef PCH_H
#define PCH_H


#include "framework.h"
#include <powrprof.h>
#include <gdiplus.h>
#include <mmsystem.h>
#include <thread>
#include <vector>
#include <winsock2.h>
#include <iphlpapi.h>
#include <icmpapi.h>
#include <ws2tcpip.h>
#include <winhttp.h>

using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")
#pragma comment(lib, "PowrProf.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "winhttp.lib")

#endif