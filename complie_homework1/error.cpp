#include "global.h"
#include "function.h"
#include "data.h"
void error(int n){
    errornum++;
    cout << lnum << endl;
    cout << backupline << endl;
    if(n == 0){//忽略缺失符号
        return;
    }
    else if(n == 1){//跳到下一个;
        while(symid != SEMICN){
            getsym();
        }
        getsym();
        return;
    }
    else if(n == 2){//跳到下一个)
        while(symid != RPARENT){
            getsym();
        }
        return;
    }
    else if(n == 4){//跳到下一个类型符号
        while(symid != INTTK && symid != CHARTK && symid != FLOATTK && symid != VOIDTK){
            getsym();
        }
        return;
    }
    else if(n == 5){//跳到下一个; , [
        while(symid != SEMICN && symid != COMMA && symid != LBRACK){
            getsym();
        }
        getsym();
        return;
    }
    else if(n == 6){
        while(symid != SEMICN){
            getsym();
        }
        return;
    }
}
