@echo off
setlocal
rem Alternativa con CMake; ejecutar desde una terminal de desarrollo de Visual Studio.
pushd "%~dp0"
if errorlevel 1 exit /b 1

cmake -S . -B build/windows -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Release
if errorlevel 1 goto :error
cmake --build build/windows
if errorlevel 1 goto :error

echo.
echo Compilacion completada: "%CD%\build\windows\bin\tp_integrador.exe"
popd
exit /b 0

:error
set "compile_exit_code=%errorlevel%"
echo Error: no se pudo completar la compilacion. 1>&2
popd
exit /b %compile_exit_code%
