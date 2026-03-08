@echo off
setlocal EnableExtensions

if not defined ROOT_DIR_WIN (
  set "ROOT_DIR_WIN=%~dp0.."
  for %%I in ("%ROOT_DIR_WIN%") do set "ROOT_DIR_WIN=%%~fI"
)

if not defined EDK2_DIR_WIN (
  set "EDK2_DIR_WIN=%ROOT_DIR_WIN%\external\edk2"
)

if not defined PYTHON_COMMAND_WIN (
  set "PYTHON_COMMAND_WIN=%ROOT_DIR_WIN%\.venv-edk2\Scripts\python.exe"
)

if not defined EDK2_ARCH (
  set "EDK2_ARCH=X64"
)

if not defined EDK2_TARGET (
  set "EDK2_TARGET=DEBUG"
)

rem Force official Windows LLVM for edk2 CLANGPDB.
if not defined LLVM_BIN_WIN (
  set "LLVM_BIN_WIN=C:\Program Files\LLVM\bin\"
)

echo [edk2] ROOT_DIR_WIN=%ROOT_DIR_WIN%
echo [edk2] EDK2_DIR_WIN=%EDK2_DIR_WIN%
echo [edk2] PYTHON_COMMAND_WIN=%PYTHON_COMMAND_WIN%
echo [edk2] LLVM_BIN_WIN=%LLVM_BIN_WIN%

if not exist "%PYTHON_COMMAND_WIN%" (
  echo [edk2] ERROR: Python venv missing. Run make bootstrap first.
  exit /b 1
)

if not exist "%LLVM_BIN_WIN%llvm-lib.exe" (
  echo [edk2] ERROR: Official Windows LLVM not found.
  echo [edk2] Expected:
  echo [edk2]   %LLVM_BIN_WIN%llvm-lib.exe
  exit /b 1
)

if not exist "%LLVM_BIN_WIN%clang-cl.exe" (
  echo [edk2] WARNING: clang-cl.exe not found in %LLVM_BIN_WIN%
)

set "MAKEFLAGS="
set "MFLAGS="
set "WORKSPACE=%ROOT_DIR_WIN%"
set "PACKAGES_PATH=%EDK2_DIR_WIN%"
set "PYTHON_COMMAND=%PYTHON_COMMAND_WIN%"
set "CLANG_HOST_BIN=n"
set "CLANG_BIN=%LLVM_BIN_WIN%"

if exist "C:\Program Files\NASM\nasm.exe" (
  set "NASM_PREFIX=C:\Program Files\NASM\"
)

cd /d "%ROOT_DIR_WIN%" || exit /b 1

if exist "%EDK2_DIR_WIN%\BaseTools\Bin\Win32\build.exe" (
  call "%EDK2_DIR_WIN%\edksetup.bat" VS2022 || exit /b 1
) else (
  call "%EDK2_DIR_WIN%\edksetup.bat" Rebuild VS2022 || exit /b 1
)

build -p bootloader\uefi\loaderpkg\loaderpkg.dsc -a %EDK2_ARCH% -b %EDK2_TARGET% -t CLANGPDB || exit /b 1
exit /b 0