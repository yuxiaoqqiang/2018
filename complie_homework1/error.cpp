#include "global.h"
#include "function.h"
#include "data.h"
void error(int n){
    errornum++;
    cout << lnum << endl;
    cout << backupline << endl;
    if(n == 0){//����ȱʧ����
        return;
    }
    else if(n == 1){//������һ��;
        while(symid != SEMICN){
            getsym();
        }
        getsym();
        return;
    }
    else if(n == 2){//������һ��)
        while(symid != RPARENT){
            getsym();
        }
        return;
    }
    else if(n == 4){//������һ�����ͷ���
        while(symid != INTTK && symid != CHARTK && symid != FLOATTK && symid != VOIDTK){
            getsym();
        }
        return;
    }
    else if(n == 5){//������һ��; , [
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
