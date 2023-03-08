rmdir /s /Q "%appdata%\Orita" > nul 2>&1
mkdir "%appdata%\Orita" > nul 2>&1
echo {} > "%appdata%\Orita\name.json"
echo {"time":1000,"compile_parameter":"-std=c++14 -O2 -Wl,--stack=2147483647"} > "%appdata%\Orita\data.json"
echo {^
    "colors":{^
        "white":[255,255,255],^
        "red":[240,0,0],^
        "orange":[240,160,0],^
        "yellow":[240,240,0],^
        "green":[32,224,112],^
        "blue":[0,176,255],^
        "purple":[160,0,240]^
    }^
} > "%appdata%\Orita\settings.json"
mkdir "%appdata%\Orita\data" > nul 2>&1
echo. > "%appdata%\Orita\data\data.in"
echo. > "%appdata%\Orita\data\data.out"
mkdir "%appdata%\Orita\source" > nul 2>&1
mkdir "%appdata%\Orita\random" > nul 2>&1
mkdir "%appdata%\Orita\temp" > nul 2>&1
exit