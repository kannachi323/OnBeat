@echo off

:: Remove the previous build directory
rmdir /s /q build

:: Create a new build directory
mkdir build

:: Run CMake to generate build files
cmake -B build -G "MinGW Makefiles"

:: Build the project
cmake --build build

:: Check if the build was successful
if exist build\OnBeat.exe (
    echo Build succeeded, starting the program...
    cd build
    start OnBeat.exe
) else (
    echo Build failed. OnBeat.exe not found.
)

pause
