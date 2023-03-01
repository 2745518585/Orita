start /b /WAIT clear_Orita.bat
g++ %~dp0compile.cpp -o %~dp0compile.exe -std=c++14 -O2 -Wl,--stack=2147483647 -I %~dp0include
start /b /D %~dp0 /WAIT compile.exe
exit