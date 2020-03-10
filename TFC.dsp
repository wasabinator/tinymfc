# Microsoft Developer Studio Project File - Name="TFC" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=TFC - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TFC.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TFC.mak" CFG="TFC - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TFC - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "TFC - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TFC - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0xc09 /d "NDEBUG"
# ADD RSC /l 0xc09 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "TFC - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "UNICODE" /D "_UNICODE" /YX /FD /GZ /c
# ADD BASE RSC /l 0xc09 /d "_DEBUG"
# ADD RSC /l 0xc09 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "TFC - Win32 Release"
# Name "TFC - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\button.cpp
# End Source File
# Begin Source File

SOURCE=.\dc.cpp
# End Source File
# Begin Source File

SOURCE=.\dialog.cpp
# End Source File
# Begin Source File

SOURCE=.\dockview.cpp
# End Source File
# Begin Source File

SOURCE=.\globals.cpp
# End Source File
# Begin Source File

SOURCE=.\listview.cpp
# End Source File
# Begin Source File

SOURCE=.\mainwnd.cpp
# End Source File
# Begin Source File

SOURCE=.\rect.cpp
# End Source File
# Begin Source File

SOURCE=.\splitter.cpp
# End Source File
# Begin Source File

SOURCE=.\statbar.cpp
# End Source File
# Begin Source File

SOURCE=.\tabctl.cpp
# End Source File
# Begin Source File

SOURCE=.\Toolbar.cpp
# End Source File
# Begin Source File

SOURCE=.\treeview.cpp
# End Source File
# Begin Source File

SOURCE=.\view.cpp
# End Source File
# Begin Source File

SOURCE=.\window.cpp
# End Source File
# Begin Source File

SOURCE=.\wndclass.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\button.h
# End Source File
# Begin Source File

SOURCE=.\dc.h
# End Source File
# Begin Source File

SOURCE=.\dialog.h
# End Source File
# Begin Source File

SOURCE=.\dockview.h
# End Source File
# Begin Source File

SOURCE=.\globals.h
# End Source File
# Begin Source File

SOURCE=.\listview.h
# End Source File
# Begin Source File

SOURCE=.\mainwnd.h
# End Source File
# Begin Source File

SOURCE=.\rect.h
# End Source File
# Begin Source File

SOURCE=.\splitter.h
# End Source File
# Begin Source File

SOURCE=.\statbar.h
# End Source File
# Begin Source File

SOURCE=.\tabctl.h
# End Source File
# Begin Source File

SOURCE=.\toolbar.h
# End Source File
# Begin Source File

SOURCE=.\treeview.h
# End Source File
# Begin Source File

SOURCE=.\view.h
# End Source File
# Begin Source File

SOURCE=.\window.h
# End Source File
# Begin Source File

SOURCE=.\wndclass.h
# End Source File
# End Group
# End Target
# End Project
