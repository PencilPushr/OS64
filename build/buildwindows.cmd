@echo off
setlocal EnableExtensions

set "ROOT=%~dp0.."
for %%I in ("%ROOT%") do set "ROOT=%%~fI"

set "VENV=%ROOT%\.venv-edk2\Scripts\python.exe"

set "KERNEL_OUT=%ROOT%\out\x64\debug\kernel"
set "ESP_BOOT=%ROOT%\out\x64\debug\esp\efi\boot"
set "ESP_KERNEL=%ROOT%\out\x64\debug\esp\kernel"

set "KERNEL_OBJ=%KERNEL_OUT%\kmain.o"
set "KERNEL_ELF=%KERNEL_OUT%\kernel.elf"
set "LOADER_EFI_SRC=%ROOT%\build\loaderpkg\DEBUG_CLANGPDB\X64\loader.efi"
set "LOADER_EFI_DST=%ESP_BOOT%\bootx64.efi"

if not exist "%VENV%" (
  call "%ROOT%\build\bootstrapwindows.cmd"
  if errorlevel 1 exit /b 1
)

rem Resolve clang from PATH first
for %%I in (clang.exe) do set "CLANG=%%~$PATH:I"
for %%I in (ld.lld.exe) do set "LD_LLD=%%~$PATH:I"

if not defined CLANG (
  if exist "C:\Program Files\LLVM\bin\clang.exe" set "CLANG=C:\Program Files\LLVM\bin\clang.exe"
)

if not defined LD_LLD (
  if exist "C:\Program Files\LLVM\bin\ld.lld.exe" set "LD_LLD=C:\Program Files\LLVM\bin\ld.lld.exe"
)

if not defined CLANG (
  echo [build] ERROR: clang.exe not found on PATH or in C:\Program Files\LLVM\bin
  exit /b 1
)

if not defined LD_LLD (
  echo [build] ERROR: ld.lld.exe not found on PATH or in C:\Program Files\LLVM\bin
  exit /b 1
)

for %%I in ("%CLANG%") do set "LLVM_BIN_WIN=%%~dpI"

echo [build] Using clang:   %CLANG%
echo [build] Using ld.lld:  %LD_LLD%
echo [build] Using LLVM dir:%LLVM_BIN_WIN%

mkdir "%KERNEL_OUT%" 2>nul
mkdir "%ESP_BOOT%" 2>nul
mkdir "%ESP_KERNEL%" 2>nul

echo [build] Building kernel object...
"%CLANG%" --target=x86_64-unknown-elf ^
  -ffreestanding -fno-stack-protector -fno-pic -mno-red-zone -Wall -Wextra ^
  -c "%ROOT%\kernel\kmain.c" -o "%KERNEL_OBJ%"
if errorlevel 1 exit /b 1

echo [build] Linking kernel ELF...
"%LD_LLD%" -m elf_x86_64 ^
  -T "%ROOT%\kernel\linker.ld" ^
  -o "%KERNEL_ELF%" "%KERNEL_OBJ%"
if errorlevel 1 exit /b 1

echo [build] Building UEFI loader...
set "ROOT_DIR_WIN=%ROOT%"
set "EDK2_DIR_WIN=%ROOT%\external\edk2"
set "PYTHON_COMMAND_WIN=%ROOT%\.venv-edk2\Scripts\python.exe"
set "LLVM_BIN_WIN=C:\Program Files\LLVM\bin\"
call "%ROOT%\build\edk2buildwindows.cmd"
if errorlevel 1 exit /b 1

copy /Y "%LOADER_EFI_SRC%" "%LOADER_EFI_DST%" >nul
if errorlevel 1 exit /b 1

copy /Y "%KERNEL_ELF%" "%ESP_KERNEL%\kernel.elf" >nul
if errorlevel 1 exit /b 1

echo [build] Done.
exit /b 0