@echo off
setlocal EnableExtensions

if "%~1"=="" (
  cmd.exe /C build\buildwindows.cmd
  exit /b %ERRORLEVEL%
)

if /I "%~1"=="bootstrap" (
  cmd.exe /C build\bootstrapwindows.cmd
  exit /b %ERRORLEVEL%
)

if /I "%~1"=="build" (
  cmd.exe /C build\buildwindows.cmd
  exit /b %ERRORLEVEL%
)

if /I "%~1"=="run" (
  shift
  cmd.exe /C build\runwindows.cmd %*
  exit /b %ERRORLEVEL%
)

if /I "%~1"=="clean" (
  cmd.exe /C build\cleanwindows.cmd
  exit /b %ERRORLEVEL%
)

if /I "%~1"=="info" (
  echo OS64 Windows wrapper
  echo Targets: bootstrap, build, run, clean
  exit /b 0
)

echo Unknown target: %~1
exit /b 1