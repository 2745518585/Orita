#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
int main(int argc,char **argv)
{
    system("rmdir /s /Q %appdata%\\Orita > nul 2>&1");
    system("mkdir %appdata%\\Orita > nul 2>&1");
    system("mkdir %appdata%\\Orita\\name > nul 2>&1");
    system("echo {} > %appdata%\\Orita\\name\\name.json");
    system("mkdir %appdata%\\Orita\\data > nul 2>&1");
    system("echo {\"time\":1000} > %appdata%\\Orita\\data\\data.json");
    system("echo. > %appdata%\\Orita\\data\\data.in");
    system("echo. > %appdata%\\Orita\\data\\data.out");
    system("mkdir %appdata%\\Orita\\source > nul 2>&1");
    system("mkdir %appdata%\\Orita\\random > nul 2>&1");
    return 0;
}