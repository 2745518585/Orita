rmdir /s /Q "%appdata%\Orita" > nul 2>&1
mkdir "%appdata%\Orita" > nul 2>&1
echo {} > "%appdata%\Orita\name.json"
mkdir "%appdata%\Orita\data" > nul 2>&1
echo {"time":1000,"compile_parameter":"-std=c++14 -O2 -Wl,--stack=2147483647"} > "%appdata%\Orita\data.json"
echo. > "%appdata%\Orita\data\data.in"
echo. > "%appdata%\Orita\data\data.out"
mkdir "%appdata%\Orita\source" > nul 2>&1
mkdir "%appdata%\Orita\random" > nul 2>&1
mkdir "%appdata%\Orita\temp" > nul 2>&1
exit