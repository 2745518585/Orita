g++ %~dp0source\orita.cpp -o %~dp0build\orita.exe -std=c++14 -O2 -Wl,--stack=2147483647 -I %~dp0include
g++ %~dp0source\run.cpp -o %~dp0build\run.exe -std=c++14 -O2 -Wl,--stack=2147483647 -I %~dp0include
g++ %~dp0source\check.cpp -o %~dp0build\check.exe -std=c++14 -O2 -Wl,--stack=2147483647 -I %~dp0include
g++ %~dp0source\judge.cpp -o %~dp0build\judge.exe -std=c++14 -O2 -Wl,--stack=2147483647 -I %~dp0include
g++ %~dp0source\chdata.cpp -o %~dp0build\chdata.exe -std=c++14 -O2 -Wl,--stack=2147483647 -I %~dp0include
g++ %~dp0source\compile.cpp -o %~dp0build\compile.exe -std=c++14 -O2 -Wl,--stack=2147483647 -I %~dp0include
g++ %~dp0source\changna.cpp -o %~dp0build\changna.exe -std=c++14 -O2 -Wl,--stack=2147483647 -I %~dp0include
g++ %~dp0source\cmp.cpp -o %~dp0build\cmp.exe -std=c++14 -O2 -Wl,--stack=2147483647 -I %~dp0include
g++ %~dp0source\setfile.cpp -o %~dp0build\setfile.exe -std=c++14 -O2 -Wl,--stack=2147483647 -I %~dp0include
g++ %~dp0source\reset_Orita.cpp -o %~dp0build\reset_Orita.exe -std=c++14 -O2 -Wl,--stack=2147483647 -I %~dp0include
orita reset_Orita
exit