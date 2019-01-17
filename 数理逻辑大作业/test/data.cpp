#include "data.h"

char ch = ' ';
int symid;
int num;
float fnum;
string id = "";
string sym = "";
int over = 0;

int line[500];
char backupline[500];
int lnum = 0, cnum = 0, llen = 0;
int idnum = 0;
int funnum = 0;
int calnum = 0;
int snum = 0;
int run[100];

int ifdefine = 0;
int ifok = 0;

int f0num = 0;
int f1num = 0;
int f2num = 0;
int f3num = 0;

int truenum[1024];
string com[1000];

string ids[10];
string funs[10];
string f0[3];
string f1[3];
string f2[3];
string f3[3];

int idv[1025][11];

string cal[100];

int f01 = 0;
int f02 = 0;
int f03 = 0;

int f11[2];
int f12[2];
int f13[2];

int f21[2][2];
int f22[2][2];
int f23[2][2];

int f31[2][2][2];
int f32[2][2][2];
int f33[2][2][2];
