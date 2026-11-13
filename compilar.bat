@echo off
title SITRAC - Compilacion y ejecucion
where g++ >nul 2>nul
if errorlevel 1 (
  echo No se encontro g++.
  echo Instala MinGW-w64 o MSYS2 y agrega la carpeta bin al PATH.
  pause
  exit /b 1
)
g++ -std=c++14 -Wall -Wextra -pedantic src\main.cpp -o sitrac.exe
if errorlevel 1 (
  echo Hubo errores de compilacion. Revisa los mensajes anteriores.
  pause
  exit /b 1
)
echo Compilacion correcta. Iniciando SITRAC...
sitrac.exe
pause
