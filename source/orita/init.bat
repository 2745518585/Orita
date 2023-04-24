mkdir %~dp0..\..\build > nul 2>&1
mkdir %~dp0..\..\build\build_orita > nul 2>&1
g++ %~dp0orita.cpp -o %~dp0..\..\build\build_orita\orita.exe -std=c++14 -O2 -w
exit