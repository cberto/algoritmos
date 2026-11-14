@echo off
setlocal
cd /d "%~dp0"
if errorlevel 1 goto :error
if not exist work mkdir work
if errorlevel 1 goto :error
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" >nul
if errorlevel 1 goto :error
cl /nologo /std:c++17 /EHsc /W4 /WX /MDd /D_DEBUG /utf-8 /Iinclude src\main.cpp src\Sistema.cpp /Fe:bicis.exe /Fo:work\
if errorlevel 1 goto :error
echo.
echo Compilacion exitosa: bicis.exe
pause
exit /b 0

:error
echo.
echo ERROR: la compilacion no se pudo completar. Revisa los mensajes anteriores.
pause
exit /b 1
