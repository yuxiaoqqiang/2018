#include "global.h"
#include "function.h"
#include "data.h"
//定义全局变量

char ch = ' ';
int symid;
int num;
float fnum;
string id = "";
string sym = "";

int line[500];
char backupline[500];
int lnum = 0, cnum = 0, llen = 0;
FILE* src = NULL;
ofstream foutput;
int havefloat = 0;

char name[MAX];
int kind;
float value;
int ischar;
int paranum;
int errornum = 0;
int cx = 0;
char result[200];

int factornum = 0;
int onlychar = 0;
int tempfactornum = 0;
int ifreturn = 0;
int returnnum = 0;

symtable maintable;
numsymtable numtable;
Code code[cxmax];
Str str;
temp_table table;
