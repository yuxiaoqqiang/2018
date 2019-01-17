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
//���ű�
typedef struct{
char name[MAX]; //��������
int kind; //����(����,����,����,����)
/*
0 - CONST//����
1 - VARIABLE//����
2 - FUNCTION//����
3 - PARA//����
*/
float value; //������ֵ
int datakind;  //0->int, 1->char, 2- > float
int address; //�洢��������ڷ��ű���ĵ�ַ
int paranum; //�����ĸ���������ĳ���(ֻ��һά����)
}basic_symtable;

typedef struct{
//char name[MAX];
int kind;//����(int, char, float)
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
}numsymtable;//�����

typedef struct{
basic_symtable element[MAXSYM];
int index; //���ű�ջ��ָ��
int total; //�ֳ�������
int indextable[MAXSYM]; //�ֳ�����������
}symtable;

typedef struct{
char f[MAX];//������
int l;//�����
float a;//������
}Code;

typedef struct{
char str[200];
}basic_Str;

typedef struct{
basic_Str s[MAX];//�ַ�������
int index;//�ַ�������
}Str;

typedef struct{
int value;
}basic_case;

typedef struct{
basic_case c[MAX];
int index;
int kind;
}Case;//��ֹcase�ظ�

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
//�ж��Ƿ񵥸��ַ�
extern int factornum;
extern int onlychar;
extern int tempfactornum;
extern int ifreturn;
extern int returnnum;
#endif // GLOBAL_H_INCLUDED
