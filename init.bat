mkdir %APPDATA%\Orita
echo %~dp0build > %APPDATA%\Orita\path.txt 
mkdir bin
g++ orita.cpp -o bin\orita.exe -std=c++20 -O2 -w