//
// Передача переменной типа CString
//
#if _MSC_VER > 1000
#pragma once
#endif


#ifndef _TRNTIME_H
#define _TRNTIME_H

CString _myTimeExit;

void setTimeExit(CString myString);
CString getTimeExit();

#endif // end header file
