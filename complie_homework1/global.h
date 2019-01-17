#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include "function.h"
#include "data.h"

extern char ch;
extern int symid;
extern int num;
extern float fnum;
extern string id;
extern string sym;
extern int lnum;
extern int cnum;
extern int llen;
extern int line[500];
extern char backupline[500];
extern int errornum;


extern ofstream foutput;
extern FILE* src;
extern int havefloat;

extern char name[MAX];
extern int kind;
extern float value;
extern int ischar;
extern int paranum;

extern int cx;
extern char result[200];
//符号表
typedef struct{
char name[MAX]; //符号名称
int kind; //类型(常量,变量,函数,参数)
/*
0 - CONST//常量
1 - VARIABLE//变量
2 - FUNCTION//函数
3 - PARA//参数
*/
float value; //常量的值
int datakind;  //0->int, 1->char, 2- > float
int address; //存储这个变量在符号表里的地址
int paranum; //参数的个数或数组的长度(只有一维数组)
}basic_symtable;

typedef struct{
//char name[MAX];
int kind;//类型(int, char, float)
/*
0 - INT //int
1 - CHAR //char
2 - FLOAT //float
*/
int address;
float f[MAX];
int paranum;
}basic_numsymtable;

typedef struct{
basic_numsymtable num[MAXSYM];
int index;
}numsymtable;//数组表

typedef struct{
basic_symtable element[MAXSYM];
int index; //符号表栈顶指针
int total; //分程序总数
int indextable[MAXSYM]; //分程序索引数组
}symtable;

typedef struct{
char f[MAX];//操作名
int l;//标记数
float a;//操作数
}Code;

typedef struct{
char str[200];
}basic_Str;

typedef struct{
basic_Str s[MAX];//字符串内容
int index;//字符串个数
}Str;

typedef struct{
int value;
}basic_case;

typedef struct{
basic_case c[MAX];
int index;
int kind;
}Case;//防止case重复

extern symtable maintable;
extern numsymtable numtable;
extern Str str;
extern Code code[cxmax];

typedef struct{
float tempnum[MAX];
int address;
int para;
}basic_temp_table;

typedef struct{
basic_temp_table num[MAX];
int index;
}temp_table;

extern temp_table table;
//判断是否单个字符
extern int factornum;
extern int onlychar;
extern int tempfactornum;
extern int ifreturn;
extern int returnnum;
#endif // GLOBAL_H_INCLUDED
