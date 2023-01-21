#ifndef INIT
#define INIT INIT
#include<bits/stdc++.h>
#include<windows.h>
#include<direct.h>
#include"nlohmann/json.hpp"
using namespace std;
using json=nlohmann::json;
string system_to_rubbish=" > \"%appdata%\\Orita\\rubbish\\rubbish.txt\" 2>&1";
int system(string x) {return system(x.c_str());}
#endif