g++ %~dp0..\orita.cpp -o %~dp0..\orita.exe -std=c++14 -O2 -Wl,--stack=2147483647 -I %~dp0..\include
g++ %~dp0..\orita\orita.cpp -o %~dp0..\orita\orita.exe -std=c++14 -O2 -Wl,--stack=2147483647 -I %~dp0..\include
g++ %~dp0..\run.cpp -o %~dp0..\run.exe -std=c++14 -O2 -Wl,--stack=2147483647 -I %~dp0..\include
g++ %~dp0..\check.cpp -o %~dp0..\check.exe -std=c++14 -O2 -Wl,--stack=2147483647 -I %~dp0..\include
g++ %~dp0..\judge.cpp -o %~dp0..\judge.exe -std=c++14 -O2 -Wl,--stack=2147483647 -I %~dp0..\include
g++ %~dp0..\chdata.cpp -o %~dp0..\chdata.exe -std=c++14 -O2 -Wl,--stack=2147483647 -I %~dp0..\include
g++ %~dp0..\compile.cpp -o %~dp0..\compile.exe -std=c++14 -O2 -Wl,--stack=2147483647 -I %~dp0..\include
g++ %~dp0..\changna.cpp -o %~dp0..\changna.exe -std=c++14 -O2 -Wl,--stack=2147483647 -I %~dp0..\include
g++ %~dp0..\cmp.cpp -o %~dp0..\cmp.exe -std=c++14 -O2 -Wl,--stack=2147483647 -I %~dp0..\include
g++ %~dp0..\setfile.cpp -o %~dp0..\setfile.exe -std=c++14 -O2 -Wl,--stack=2147483647 -I %~dp0..\include
g++ %~dp0..\reset_Orita.cpp -o %~dp0..\reset_Orita.exe -std=c++14 -O2 -Wl,--stack=2147483647
orita reset_Orita
exit