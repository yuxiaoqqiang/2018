#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include<stdio.h>
#include <string.h>
#include <ctype.h>
#include <string>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include <stdlib.h>
#include <math.h>
#include <typeinfo>
#include <sstream>
using namespace std;

extern char ch;
extern int symid;
extern int num;
extern string id;
extern int over;
extern string sym;
extern int lnum;
extern int cnum;
extern int llen;
extern int line[500];
extern char backupline[500];
extern int errornum;
extern int run[100];

extern int ifdefine;
extern int ifok;

extern int idnum;
extern int funnum;
extern int calnum;

extern int snum;

extern int f0num;
extern int f1num;
extern int f2num;
extern int f3num;

extern string ids[10];
extern string funs[10];
extern string f0[3];
extern string f1[3];
extern string f2[3];
extern string f3[3];

extern string com[1000];
extern int truenum[1024];
extern int idv[1025][11];

extern string cal[100];

extern int f01;
extern int f02;
extern int f03;

extern int f11[2];
extern int f12[2];
extern int f13[2];

extern int f21[2][2];
extern int f22[2][2];
extern int f23[2][2];

extern int f31[2][2][2];
extern int f32[2][2][2];
extern int f33[2][2][2];

#endif // DATA_H_INCLUDED
