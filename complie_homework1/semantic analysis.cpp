#include "data.h"
#include "function.h"
#include "global.h"

void pushnumtable(int address, int kind, int paranum){
    if(numtable.index >= MAXSYM){
        error(0);
        cout << "too long table" << endl;
        return;
    }
    numtable.num[numtable.index].address = address;
    numtable.num[numtable.index].kind = kind;
    numtable.num[numtable.index].paranum =  paranum;
    numtable.index++;
}

int searchnum(int address){
    int n = 0;
    while(n < numtable.index){
        if(numtable.num[n].address == address)
            break;
        n++;
    }
    if(n == numtable.index){
        error(0);
        cout << "not found" << endl;
        return -1;
    }
    return n;
}

void pushtable(char* name, int kind, float value, int paranum, int ischar, int isVec){
    int iter;
    if(maintable.index >= MAXSYM){//符号表是否已满
        error(0);
        cout << "too long table" << endl;
        return;
    }
    if(kind == FUNCTION){//函数
        for(iter = 1; iter <= maintable.total; iter++){
            if (!strcmp(maintable.element[maintable.indextable[iter]].name, name)){//函数名重复
                error(0);
                cout << "same function name" << endl;
                return;
            }
        }
        maintable.indextable[++maintable.total] = maintable.index;
    }
    else{//常量，变量，参数
        iter = maintable.indextable[maintable.total] + 1;
        for(;iter < maintable.index; iter++){//本函数块内不要重复
            if(!strcmp(maintable.element[iter].name, name)){
                error(0);
                cout << "same name" << endl;
                return;
            }
        }
    }
    strcpy(maintable.element[maintable.index].name, name);
    maintable.element[maintable.index].kind = kind;
    maintable.element[maintable.index].value = value;
    maintable.element[maintable.index].datakind = ischar;
    maintable.element[maintable.index].address = maintable.index;
    maintable.element[maintable.index].paranum = isVec ? isVec : paranum;
    maintable.index++;
}

int searchst(char* name, int flag, int needret){
    int n;
    int m = maintable.indextable[1] == 0 ? maintable.index : maintable.indextable[1];
    if(flag == 1){//函数
        n = 1;
        while(n <= maintable.total){
            if(strcmp(maintable.element[maintable.indextable[n]].name, name) == 0)
                break;
            n++;
        }
        if(n > maintable.total){//函数未定义
            return -1;
        }
        if(maintable.element[maintable.indextable[n]].value == 0 && needret == 1)//函数无返回值
            return -2;
        return maintable.element[maintable.indextable[n]].address;
    }
    else{//常量，变量，参数
        n = maintable.indextable[maintable.total] + 1;//查找分程序符号表中是否定义
        while(n < maintable.index){
            if(strcmp(maintable.element[n].name, name) == 0)
                break;
            n++;
        }
        if(n == maintable.index){//如果分程序符号表中无定义，查找最外层符号表
            n = 0;
            while(n < m){
                if(strcmp(maintable.element[n].name, name) == 0)
                    break;
                n++;
            }
            if(n == m){//符号表中没有定义
                return -1;
            }
        }
        return maintable.element[n].address;
    }
}
