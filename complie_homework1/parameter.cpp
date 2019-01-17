#include "data.h"
#include "function.h"
#include "global.h"
/*
＜参数＞    ::= ＜参数表＞
＜参数表＞    ::=  ＜类型标识符＞＜标识符＞{,＜类型标识符＞＜标识符＞}| ＜空＞
*/
void parametertable(){
    int i = 0;
    int tempid;
    while(symid == INTTK || symid == CHARTK || symid == FLOATTK){
        tempid = symid;
        getsym();
        if(symid != IDEN){
            error(0);
            itoa(errornum, name, 10);
            cout << "para id wrong" << endl;
        }
        else{
            strcpy(name, id.c_str());
            getsym();
        }
        kind = PARA;
        value = 0;
        ischar = tempid == INTTK ? INT : tempid == CHARTK ? CHAR : FLOAT;
        paranum = 0;
        pushtable(name, kind, value, paranum, ischar, 0);
        i++;
        if(symid == COMMA){
            getsym();
            continue;
        }
    }
    paranum = i;
    insertproc(paranum);
    return;
}

void insertproc(int paranum){
    maintable.element[maintable.indextable[maintable.total]].paranum = paranum;//插入函数参数个数信息
    return;
}
/*
＜值参数表＞   ::=   ＜表达式＞{,＜表达式＞}｜＜空＞
*/
void valueofpara(char* names){
    int j = 0;
    do{
        if(symid == COMMA){
            getsym();
        }
        if(symid == PLUS || symid == MINU || symid == IDEN || symid == LPARENT || symid == CHARCON || symid == INTCON || symid == FLOATCON){
            expression();
            j++;
        }
        if(symid != COMMA && symid != RPARENT){
            error(2);
            cout << "lost ,| )" << endl;
            return;
        }
    }while(symid == COMMA);//如果是逗号，则还有其他的参数
    paranum = j;
    if(maintable.element[searchst(names, 1, 0)].paranum != paranum){
        error(0);
        cout << "para number wrong" << endl;
    }
    return;
}
