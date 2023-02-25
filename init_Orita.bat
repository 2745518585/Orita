rmdir /s /Q "%appdata%\Orita" > nul 2>&1
mkdir "%appdata%\Orita" > nul 2>&1
mkdir "%appdata%\Orita\name" > nul 2>&1
echo {} > "%appdata%\Orita\name\name.json"
mkdir "%appdata%\Orita\data" > nul 2>&1
echo {"time":1000} > "%appdata%\Orita\data\data.json"
echo. > "%appdata%\Orita\data\data.in"
echo. > "%appdata%\Orita\data\data.out"
mkdir "%appdata%\Orita\source" > nul 2>&1
mkdir "%appdata%\Orita\random" > nul 2>&1
mkdir "%appdata%\Orita\temp" > nul 2>&1
g++ %~dp0compile.cpp -o %~dp0compile.exe -std=c++14 -O2 -Wl,--stack=2147483647 -I %~dp0include
start /b /D %~dp0 /WAIT compile.exe