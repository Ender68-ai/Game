@echo off
setlocal EnableExtensions

rem Clean previous build + CMake cache
if exist build rd /s /q build
if exist release rd /s /q release
if exist release.zip del /q release.zip

rem =========================
rem MAXIMUM RUNTIME FLAGS (Clang)
rem =========================
set "CFLAGS=-O3 -ffast-math -DNDEBUG -march=native -mtune=native -flto -fno-math-errno -fno-trapping-math -ffp-contract=fast -fstrict-aliasing"
set "CXXFLAGS=-O3 -ffast-math -DNDEBUG -march=native -mtune=native -flto -fno-math-errno -fno-trapping-math -ffp-contract=fast -fstrict-aliasing"

echo Configuring...

cmake -S . -B build -G Ninja ^
  -DCMAKE_BUILD_TYPE=Release ^
  -DCMAKE_C_COMPILER=clang ^
  -DCMAKE_CXX_COMPILER=clang++ ^
  -DCMAKE_C_FLAGS_RELEASE="%CFLAGS%" ^
  -DCMAKE_CXX_FLAGS_RELEASE="%CXXFLAGS%" ^
  -DCMAKE_INTERPROCEDURAL_OPTIMIZATION=ON ^
  -DCMAKE_EXE_LINKER_FLAGS_RELEASE="-fuse-ld=lld -flto" ^
  -DCMAKE_SHARED_LINKER_FLAGS_RELEASE="-fuse-ld=lld -flto"

if %ERRORLEVEL% NEQ 0 (
    echo Configuration failed! Exiting...
    pause
    exit /b %ERRORLEVEL%
)

echo Building...

cmake --build build --parallel %NUMBER_OF_PROCESSORS%

if %ERRORLEVEL% NEQ 0 (
    echo Build failed! Exiting...
    pause
    exit /b %ERRORLEVEL%
)

echo Packaging Release...

rem 1. Create the target structure: release/game/
mkdir release\game

rem 2. Copy the binary into release/game/
if exist build\game.exe (
    copy build\game.exe release\game\ >nul
) else (
    echo Error: build/game.exe not found! Check your CMake target name.
    pause
    exit /b 1
)

rem 3. Copy the assets folder into the root of the game installation directory (release/game/assets/)
if exist assets (
    xcopy /E /I /Y assets release\game\assets >nul
) else (
    echo Warning: Local assets folder not found to copy!
)

echo Zipping Release Folder...

rem 4. Compress the entire release/game structure into a portable release.zip archive
powershell -Command "Compress-Archive -Path 'release\game' -DestinationPath 'release.zip' -Force"

if %ERRORLEVEL% NEQ 0 (
    echo Packaging failed! Exiting...
    pause
    exit /b %ERRORLEVEL%
)

echo Built and packaged successfully as release.zip!
echo Waiting 60 seconds before closing this window...
timeout /t 60 /nobreak >nul
exit /b 0