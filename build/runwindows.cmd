@echo off
setlocal EnableExtensions

set "ROOT=%~dp0.."
for %%I in ("%ROOT%") do set "ROOT=%%~fI"

set "QEMU_DIR=%ROOT%\debugger\windows"
set "QEMU=%QEMU_DIR%\qemu.exe"
set "OVMF=%QEMU_DIR%\OVMF.fd"
set "ESP=%ROOT%\out\x64\debug\esp"

if not exist "%ESP%\efi\boot\bootx64.efi" (
  call "%ROOT%\build\buildwindows.cmd"
  if errorlevel 1 exit /b 1
)

if not exist "%QEMU%" (
  echo [run] ERROR: QEMU not found at %QEMU%
  exit /b 1
)

if not exist "%OVMF%" (
  echo [run] ERROR: OVMF not found at %OVMF%
  exit /b 1
)

rem If your ROM files are actually in debugger\windows\pc-bios, change QEMU_ROM_DIR to that.
set "QEMU_ROM_DIR=%QEMU_DIR%"

pushd "%QEMU_DIR%" || exit /b 1

"%QEMU%" ^
  -L "%QEMU_ROM_DIR%" ^
  -name OS64 ^
  -bios "%OVMF%" ^
  -drive format=raw,file=fat:rw:"%ESP%" ^
  -m 2048M ^
  -machine q35,smm=off ^
  -nodefaults ^
  -vga std

set "RC=%ERRORLEVEL%"
popd
exit /b %RC%