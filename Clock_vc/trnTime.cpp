// Передача переменной типа CString

#include "trntime.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef _DEBUG
void setTimeExit(CString myString)
{	
	_myTimeExit = myString; 
}
CString getTimeExit()
{                	
	return _myTimeExit;     
}
#endif