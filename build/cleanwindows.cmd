@echo off
setlocal EnableExtensions

set "ROOT=%~dp0.."
for %%I in ("%ROOT%") do set "ROOT=%%~fI"

if exist "%ROOT%\out" rmdir /S /Q "%ROOT%\out"
if exist "%ROOT%\build\loaderpkg" rmdir /S /Q "%ROOT%\build\loaderpkg"
exit /b 0