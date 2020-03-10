# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=GFX - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to GFX - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "GFX - Win32 Release" && "$(CFG)" != "GFX - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "GFX.mak" CFG="GFX - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GFX - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "GFX - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "GFX - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "GFX - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\GFX.exe"

CLEAN : 
	-@erase ".\Release\GFX.exe"
	-@erase ".\Release\Rect.obj"
	-@erase ".\Release\Window.obj"
	-@erase ".\Release\GFX.obj"
	-@erase ".\Release\Wndclass.obj"
	-@erase ".\Release\GFX.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/GFX.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0xc09 /d "NDEBUG"
# ADD RSC /l 0xc09 /d "NDEBUG"
RSC_PROJ=/l 0xc09 /fo"$(INTDIR)/GFX.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/GFX.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib ddraw.lib dxguid.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib ddraw.lib dxguid.lib\
 /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)/GFX.pdb"\
 /machine:I386 /def:".\GFX.def" /out:"$(OUTDIR)/GFX.exe" 
DEF_FILE= \
	".\GFX.def"
LINK32_OBJS= \
	".\Release\Rect.obj" \
	".\Release\Window.obj" \
	".\Release\GFX.obj" \
	".\Release\Wndclass.obj" \
	".\Release\GFX.res"

"$(OUTDIR)\GFX.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "GFX - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\GFX.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\GFX.exe"
	-@erase ".\Debug\GFX.obj"
	-@erase ".\Debug\Wndclass.obj"
	-@erase ".\Debug\Window.obj"
	-@erase ".\Debug\Rect.obj"
	-@erase ".\Debug\GFX.res"
	-@erase ".\Debug\GFX.ilk"
	-@erase ".\Debug\GFX.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/GFX.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0xc09 /d "_DEBUG"
# ADD RSC /l 0xc09 /d "_DEBUG"
RSC_PROJ=/l 0xc09 /fo"$(INTDIR)/GFX.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/GFX.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib ddraw.lib dxguid.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib ddraw.lib dxguid.lib\
 /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)/GFX.pdb" /debug\
 /machine:I386 /def:".\GFX.def" /out:"$(OUTDIR)/GFX.exe" 
DEF_FILE= \
	".\GFX.def"
LINK32_OBJS= \
	".\Debug\GFX.obj" \
	".\Debug\Wndclass.obj" \
	".\Debug\Window.obj" \
	".\Debug\Rect.obj" \
	".\Debug\GFX.res"

"$(OUTDIR)\GFX.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "GFX - Win32 Release"
# Name "GFX - Win32 Debug"

!IF  "$(CFG)" == "GFX - Win32 Release"

!ELSEIF  "$(CFG)" == "GFX - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\DirectDraw.h

!IF  "$(CFG)" == "GFX - Win32 Release"

!ELSEIF  "$(CFG)" == "GFX - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GFX.cpp
DEP_CPP_GFX_C=\
	".\Wndclass.h"\
	".\mainwnd.h"\
	".\GFX.h"\
	".\DirectDraw.h"\
	".\Window.h"\
	".\Rect.h"\
	{$(INCLUDE)}"\ddraw.h"\
	

"$(INTDIR)\GFX.obj" : $(SOURCE) $(DEP_CPP_GFX_C) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\GFX.def

!IF  "$(CFG)" == "GFX - Win32 Release"

!ELSEIF  "$(CFG)" == "GFX - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GFX.rc

"$(INTDIR)\GFX.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Rect.cpp
DEP_CPP_RECT_=\
	".\Rect.h"\
	

"$(INTDIR)\Rect.obj" : $(SOURCE) $(DEP_CPP_RECT_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Rect.h

!IF  "$(CFG)" == "GFX - Win32 Release"

!ELSEIF  "$(CFG)" == "GFX - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Window.cpp
DEP_CPP_WINDO=\
	".\Window.h"\
	".\Wndclass.h"\
	".\Rect.h"\
	

"$(INTDIR)\Window.obj" : $(SOURCE) $(DEP_CPP_WINDO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Window.h

!IF  "$(CFG)" == "GFX - Win32 Release"

!ELSEIF  "$(CFG)" == "GFX - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Wndclass.cpp
DEP_CPP_WNDCL=\
	".\Wndclass.h"\
	

"$(INTDIR)\Wndclass.obj" : $(SOURCE) $(DEP_CPP_WNDCL) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Wndclass.h

!IF  "$(CFG)" == "GFX - Win32 Release"

!ELSEIF  "$(CFG)" == "GFX - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
