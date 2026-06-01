@echo off

rd build /s /q

cmake -B build -G Ninja ^
  -DCMAKE_C_COMPILER=clang ^
  -DCMAKE_CXX_COMPILER=clang++

if errorlevel 1 exit /b %errorlevel%

cmake --build build

pause