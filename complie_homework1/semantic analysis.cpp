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
    if(maintable.index >= MAXSYM){//���ű��Ƿ�����
        error(0);
        cout << "too long table" << endl;
        return;
    }
    if(kind == FUNCTION){//����
        for(iter = 1; iter <= maintable.total; iter++){
            if (!strcmp(maintable.element[maintable.indextable[iter]].name, name)){//�������ظ�
                error(0);
                cout << "same function name" << endl;
                return;
            }
        }
        maintable.indextable[++maintable.total] = maintable.index;
    }
    else{//����������������
        iter = maintable.indextable[maintable.total] + 1;
        for(;iter < maintable.index; iter++){//���������ڲ�Ҫ�ظ�
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
    if(flag == 1){//����
        n = 1;
        while(n <= maintable.total){
            if(strcmp(maintable.element[maintable.indextable[n]].name, name) == 0)
                break;
            n++;
        }
        if(n > maintable.total){//����δ����
            return -1;
        }
        if(maintable.element[maintable.indextable[n]].value == 0 && needret == 1)//�����޷���ֵ
            return -2;
        return maintable.element[maintable.indextable[n]].address;
    }
    else{//����������������
        n = maintable.indextable[maintable.total] + 1;//���ҷֳ�����ű����Ƿ���
        while(n < maintable.index){
            if(strcmp(maintable.element[n].name, name) == 0)
                break;
            n++;
        }
        if(n == maintable.index){//����ֳ�����ű����޶��壬�����������ű�
            n = 0;
            while(n < m){
                if(strcmp(maintable.element[n].name, name) == 0)
                    break;
                n++;
            }
            if(n == m){//���ű���û�ж���
                return -1;
            }
        }
        return maintable.element[n].address;
    }
}
