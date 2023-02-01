#ifndef _FILE_INIT
#define _FILE_INIT _FILE_INIT
#include<bits/stdc++.h>
#include<windows.h>
#include<direct.h>
#include "configor/json.hpp"
using namespace std;
using namespace configor;
string system_to_nul=" > nul 2>&1";
int system(string x) {return system(x.c_str());}
#endif