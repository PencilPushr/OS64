@echo off
setlocal EnableExtensions

set "ROOT=%~dp0.."
for %%I in ("%ROOT%") do set "ROOT=%%~fI"

set "EDK2=%ROOT%\external\edk2"
set "VENV=%ROOT%\.venv-edk2"

if not exist "%EDK2%\edksetup.bat" (
  git -C "%ROOT%" submodule update --init --recursive
  if errorlevel 1 exit /b 1
)

if not exist "%VENV%\Scripts\python.exe" (
  py -3.13 -m venv "%VENV%"
  if errorlevel 1 exit /b 1
)

"%VENV%\Scripts\python.exe" -m pip install --upgrade pip
if errorlevel 1 exit /b 1

"%VENV%\Scripts\python.exe" -m pip install -r "%EDK2%\pip-requirements.txt"
if errorlevel 1 exit /b 1

exit /b 0