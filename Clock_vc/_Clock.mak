# Microsoft Developer Studio Generated NMAKE File, Based on _Clock.dsp
!IF "$(CFG)" == ""
CFG=_Clock - Win32 Debug
!MESSAGE No configuration specified. Defaulting to _Clock - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "_Clock - Win32 Release" && "$(CFG)" != "_Clock - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "_Clock.mak" CFG="_Clock - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "_Clock - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "_Clock - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "_Clock - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\_Clock.exe"


CLEAN :
	-@erase "$(INTDIR)\_CalendarDlg.obj"
	-@erase "$(INTDIR)\_Clock.obj"
	-@erase "$(INTDIR)\_Clock.pch"
	-@erase "$(INTDIR)\_Clock.res"
	-@erase "$(INTDIR)\_ClockDlg.obj"
	-@erase "$(INTDIR)\_Exit_Dlg.obj"
	-@erase "$(INTDIR)\calendar.obj"
	-@erase "$(INTDIR)\font.obj"
	-@erase "$(INTDIR)\msmask.obj"
	-@erase "$(INTDIR)\picture.obj"
	-@erase "$(INTDIR)\staticcolor.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\_Clock.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Fp"$(INTDIR)\_Clock.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC=rc.exe
RSC_PROJ=/l 0x419 /fo"$(INTDIR)\_Clock.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\_Clock.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\_Clock.pdb" /machine:I386 /out:"$(OUTDIR)\_Clock.exe" 
LINK32_OBJS= \
	"$(INTDIR)\_CalendarDlg.obj" \
	"$(INTDIR)\_Clock.obj" \
	"$(INTDIR)\_ClockDlg.obj" \
	"$(INTDIR)\_Exit_Dlg.obj" \
	"$(INTDIR)\calendar.obj" \
	"$(INTDIR)\font.obj" \
	"$(INTDIR)\msmask.obj" \
	"$(INTDIR)\picture.obj" \
	"$(INTDIR)\staticcolor.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\_Clock.res"

"$(OUTDIR)\_Clock.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "_Clock - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\_Clock.exe" "$(OUTDIR)\_Clock.bsc"


CLEAN :
	-@erase "$(INTDIR)\_CalendarDlg.obj"
	-@erase "$(INTDIR)\_CalendarDlg.sbr"
	-@erase "$(INTDIR)\_Clock.obj"
	-@erase "$(INTDIR)\_Clock.pch"
	-@erase "$(INTDIR)\_Clock.res"
	-@erase "$(INTDIR)\_Clock.sbr"
	-@erase "$(INTDIR)\_ClockDlg.obj"
	-@erase "$(INTDIR)\_ClockDlg.sbr"
	-@erase "$(INTDIR)\_Exit_Dlg.obj"
	-@erase "$(INTDIR)\_Exit_Dlg.sbr"
	-@erase "$(INTDIR)\calendar.obj"
	-@erase "$(INTDIR)\calendar.sbr"
	-@erase "$(INTDIR)\font.obj"
	-@erase "$(INTDIR)\font.sbr"
	-@erase "$(INTDIR)\msmask.obj"
	-@erase "$(INTDIR)\msmask.sbr"
	-@erase "$(INTDIR)\picture.obj"
	-@erase "$(INTDIR)\picture.sbr"
	-@erase "$(INTDIR)\staticcolor.obj"
	-@erase "$(INTDIR)\staticcolor.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\_Clock.bsc"
	-@erase "$(OUTDIR)\_Clock.exe"
	-@erase "$(OUTDIR)\_Clock.ilk"
	-@erase "$(OUTDIR)\_Clock.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\_Clock.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
RSC=rc.exe
RSC_PROJ=/l 0x419 /fo"$(INTDIR)\_Clock.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\_Clock.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\_CalendarDlg.sbr" \
	"$(INTDIR)\_Clock.sbr" \
	"$(INTDIR)\_ClockDlg.sbr" \
	"$(INTDIR)\_Exit_Dlg.sbr" \
	"$(INTDIR)\calendar.sbr" \
	"$(INTDIR)\font.sbr" \
	"$(INTDIR)\msmask.sbr" \
	"$(INTDIR)\picture.sbr" \
	"$(INTDIR)\staticcolor.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\_Clock.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\_Clock.pdb" /debug /machine:I386 /out:"$(OUTDIR)\_Clock.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\_CalendarDlg.obj" \
	"$(INTDIR)\_Clock.obj" \
	"$(INTDIR)\_ClockDlg.obj" \
	"$(INTDIR)\_Exit_Dlg.obj" \
	"$(INTDIR)\calendar.obj" \
	"$(INTDIR)\font.obj" \
	"$(INTDIR)\msmask.obj" \
	"$(INTDIR)\picture.obj" \
	"$(INTDIR)\staticcolor.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\_Clock.res"

"$(OUTDIR)\_Clock.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("_Clock.dep")
!INCLUDE "_Clock.dep"
!ELSE 
!MESSAGE Warning: cannot find "_Clock.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "_Clock - Win32 Release" || "$(CFG)" == "_Clock - Win32 Debug"
SOURCE=.\_CalendarDlg.cpp

!IF  "$(CFG)" == "_Clock - Win32 Release"


"$(INTDIR)\_CalendarDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\_Clock.pch"


!ELSEIF  "$(CFG)" == "_Clock - Win32 Debug"


"$(INTDIR)\_CalendarDlg.obj"	"$(INTDIR)\_CalendarDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\_Clock.pch"


!ENDIF 

SOURCE=.\_Clock.cpp

!IF  "$(CFG)" == "_Clock - Win32 Release"


"$(INTDIR)\_Clock.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\_Clock.pch"


!ELSEIF  "$(CFG)" == "_Clock - Win32 Debug"


"$(INTDIR)\_Clock.obj"	"$(INTDIR)\_Clock.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\_Clock.pch"


!ENDIF 

SOURCE=.\_Clock.rc

"$(INTDIR)\_Clock.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\_ClockDlg.cpp

!IF  "$(CFG)" == "_Clock - Win32 Release"


"$(INTDIR)\_ClockDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\_Clock.pch"


!ELSEIF  "$(CFG)" == "_Clock - Win32 Debug"


"$(INTDIR)\_ClockDlg.obj"	"$(INTDIR)\_ClockDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\_Clock.pch"


!ENDIF 

SOURCE=.\_Exit_Dlg.cpp

!IF  "$(CFG)" == "_Clock - Win32 Release"


"$(INTDIR)\_Exit_Dlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\_Clock.pch"


!ELSEIF  "$(CFG)" == "_Clock - Win32 Debug"


"$(INTDIR)\_Exit_Dlg.obj"	"$(INTDIR)\_Exit_Dlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\_Clock.pch"


!ENDIF 

SOURCE=.\calendar.cpp

!IF  "$(CFG)" == "_Clock - Win32 Release"


"$(INTDIR)\calendar.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\_Clock.pch"


!ELSEIF  "$(CFG)" == "_Clock - Win32 Debug"


"$(INTDIR)\calendar.obj"	"$(INTDIR)\calendar.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\_Clock.pch"


!ENDIF 

SOURCE=.\font.cpp

!IF  "$(CFG)" == "_Clock - Win32 Release"


"$(INTDIR)\font.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\_Clock.pch"


!ELSEIF  "$(CFG)" == "_Clock - Win32 Debug"


"$(INTDIR)\font.obj"	"$(INTDIR)\font.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\_Clock.pch"


!ENDIF 

SOURCE=.\msmask.cpp

!IF  "$(CFG)" == "_Clock - Win32 Release"


"$(INTDIR)\msmask.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\_Clock.pch"


!ELSEIF  "$(CFG)" == "_Clock - Win32 Debug"


"$(INTDIR)\msmask.obj"	"$(INTDIR)\msmask.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\_Clock.pch"


!ENDIF 

SOURCE=.\picture.cpp

!IF  "$(CFG)" == "_Clock - Win32 Release"


"$(INTDIR)\picture.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\_Clock.pch"


!ELSEIF  "$(CFG)" == "_Clock - Win32 Debug"


"$(INTDIR)\picture.obj"	"$(INTDIR)\picture.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\_Clock.pch"


!ENDIF 

SOURCE=.\staticcolor.cpp

!IF  "$(CFG)" == "_Clock - Win32 Release"


"$(INTDIR)\staticcolor.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\_Clock.pch"


!ELSEIF  "$(CFG)" == "_Clock - Win32 Debug"


"$(INTDIR)\staticcolor.obj"	"$(INTDIR)\staticcolor.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\_Clock.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "_Clock - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Fp"$(INTDIR)\_Clock.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\_Clock.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "_Clock - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\_Clock.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\_Clock.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

