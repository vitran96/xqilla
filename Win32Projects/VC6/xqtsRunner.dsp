# Microsoft Developer Studio Project File - Name="xqtsRunner" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=xqtsRunner - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "xqtsRunner.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "xqtsRunner.mak" CFG="xqtsRunner - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "xqtsRunner - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "xqtsRunner - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "xqtsRunner - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "../../build/win32/VC6/release"
# PROP BASE Intermediate_Dir "Release\xqtsRunner"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../build/win32/VC6/release"
# PROP Intermediate_Dir "Release\xqtsRunner"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "." /I "../../include" /I "../../../xerces-c-src/include" /I "../../../xerces-c-src/src"/I "../../include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32  /libpath:../../build/win32/VC6 xerces-c_2.lib xqilla10.lib /libpath:Release /libpath:../../../xerces-c-src/Build/Win32/VC6/Release /nologo /out:../../build/win32/VC6/release/xqtsRunner.exe /subsystem:console /machine:I386 /nodefaultlib:"libcmt"

!ELSEIF  "$(CFG)" == "xqtsRunner - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "../../build/win32/VC6/debug"
# PROP BASE Intermediate_Dir "Debug\xqtsRunner"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../build/win32/VC6/debug"
# PROP Intermediate_Dir "Debug\xqtsRunner"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Zi /Od /I "." /I "../../include" /I "../../../xerces-c-src/include" /I "../../../xerces-c-src/src" /I "../../include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32  /libpath:../../build/win32/VC6 xerces-c_2d.lib xqilla10d.lib /libpath:Debug /libpath:../../../xerces-c-src/Build/Win32/VC6/Debug /nologo /out:../../build/win32/VC6/debug/xqtsRunner.exe /pdb:"../../build/win32/VC6/debug/xqilla10.pdb" /subsystem:console /machine:I386 /nodefaultlib:"libcmt"

!ENDIF 

# Begin Target

# Name "xqtsRunner - Win32 Release"
# Name "xqtsRunner - Win32 Debug"
# Begin Source File

SOURCE=..\..\tests\xqts\runner.cpp
# End Source File
# End Target
# End Project