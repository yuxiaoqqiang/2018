#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

using namespace std;

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <typeinfo>

#define OVER       -1
#define WRONG      -2
#define MAX         1000
#define MAXSYM      10000
#define cxmax       10000

#define CASETK      1
#define CHARTK      2
#define CONSTTK     3
#define ELSETK      4
#define FLOATTK     5
#define IFTK        6
#define INTTK       7
#define MAINTK      8
#define PRINTFTK    9
#define RETURNTK    10
#define SCANFTK     11
#define SWITCHTK    12
#define VOIDTK      13
#define WHILETK     14
#define IDEN        15


#define INTCON      16  // int
#define CHARCON     17  // char
#define FLOATCON    18  // float
#define STRCON      19  // string
#define ASSIGN      20  // =
#define PLUS        21  // +
#define MINU        22  // -
#define MULT        23  // *
#define DIV         24  // /
#define COMMA       25  // ,
#define COLON       26  // :
#define SEMICN      27  // ;
#define LSS         28  // <
#define LEQ         29  // <=
#define GRE         30  // >
#define GEQ         31  // >=
#define NEQ         32  // !=
#define EQL         33  // ==
#define LPARENT     34  // (
#define RPARENT     35  // )
#define LBRACK      36  // [
#define RBRACK      37  // ]
#define LBRACE      38  // {
#define RBRACE      39  // }

#define CONST       0   //常量
#define VARIABLE    1   //变量
#define FUNCTION    2   //函数
#define PARA        3   //参数

#define INT         0   //int
#define CHAR        1   //char
#define FLOAT       2   //float

#define lit         "lit"
#define opr         "opr"
#define lod         "lod"
#define sto         "sto"
#define cal         "cal"
#define jmp         "jmp"
#define jpc         "jpc"
#define red         "red"
#define wrt         "wrt"
#define ret         "ret"

#endif // DATA_H_INCLUDED
