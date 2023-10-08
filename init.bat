mkdir %APPDATA%\Orita
echo %~dp0 > %APPDATA%\Orita\path.txt 
mkdir bin
g++ orita.cpp -o bin\orita.exe -std=c++20 -O2 -w