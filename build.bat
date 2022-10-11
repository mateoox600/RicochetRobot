@echo off
cd build
call cmake --build .
call ricochet-robot.exe
cd ..