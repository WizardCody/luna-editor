:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::: Program: Luna Helper
::::::::: Version: 1.1.0
::::::::: Company: MLPOnline Team
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

@ECHO OFF

:START
CLS

VER | FIND "Version 6." > nul
IF %ERRORLEVEL% == 0 (
   REM Newer than Vista
   OPENFILES > nul
   IF ERRORLEVEL 1 (
      COLOR CF
      ECHO.Right click on this bat file and select 'Run as administrator'.
	  PAUSE
      EXIT /B 1
      )
   )

VER | FIND "Version 5.2." > nul
IF %ERRORLEVEL% == 0 (
   REM Newer than 2003 Server
   OPENFILES > nul
   IF ERRORLEVEL 1 (
      COLOR CF
      ECHO.You must be logged on as Administrator to run this program'.
	  PAUSE
      EXIT /B 1
      )
   )
   
@ECHO =============================================================================
@ECHO                Welcome in Luna Helper installer (Windows OS)
@ECHO.
@ECHO What's Luna Helper?
@ECHO    Luna Helper is a useful shortcut which allows you to access a single or 
@ECHO    multiple scripts a lot faster. Easily by right clicking on file(s) and 
@ECHO    choosing "Edit with Luna Editor".
@ECHO.
@ECHO Now... what do you want to do?
@ECHO    (1) Install
@ECHO    (2) Uninstall
@ECHO =============================================================================

CHOICE /C 12 /N /M "I choose:"
@ECHO.

IF ERRORLEVEL 2 GOTO UNINSTALL
IF ERRORLEVEL 1 GOTO INSTALL

:INSTALL
@ECHO INSTALLING...
@ECHO.

REG ADD "HKEY_CLASSES_ROOT\*\shell\Edit with Luna Editor" /f
REG ADD "HKEY_CLASSES_ROOT\*\shell\Edit with Luna Editor" /v Icon /t REG_SZ /d "\"%~dp0LunaEditor.exe\"" /f
REG ADD "HKEY_CLASSES_ROOT\*\shell\Edit with Luna Editor\command" /d "\"%~dp0LunaEditor.exe\" \"%%1\"" /f

GOTO END

:UNINSTALL
@ECHO UNINSTALLING...
@ECHO.

REG DELETE "HKEY_CLASSES_ROOT\*\shell\Edit with Luna Editor" /F

GOTO END

:END
@ECHO =============================================================================
PAUSE
EXIT /B 0