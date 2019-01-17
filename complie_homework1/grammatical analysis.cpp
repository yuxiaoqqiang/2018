#include "data.h"
#include "function.h"
#include "global.h"
//＜程序＞    ::= ［＜常量说明＞］［＜变量说明＞］{＜有返回值函数定义＞|＜无返回值函数定义＞}＜主函数＞
void program(){
    int temperror = 0;
    gen(jmp, 0, 0);
    temperror = getsym();
    if(temperror == -1){
        cout << "null file" << endl;
        exit(0);
    }
    if(symid == CONSTTK){//常量说明
        constate();
    }
    while(symid == INTTK || symid == CHARTK || symid == FLOATTK){//变量说明
        int tempid = symid;
        char tempch = ch;
        int tempcnum = cnum;
        char tempbackupline1[500];
        char tempbackupline2[500];
        int templnum1;
        int templnum2;//恢复现场用
        strcpy(tempbackupline1, backupline);
        templnum1 = lnum;
        getsym();
        if(symid != IDEN){
            error(1);
            cout << "var id wrong" << endl;
            continue;
        }
        strcpy(name, id.c_str());
        getsym();
        if(symid == COMMA || symid == LBRACK){//如果是','或者'[',则是多个变量定义或者是数组定义
            symid = tempid;
            cnum = tempcnum;
            ch = tempch;
            varstate();//变量说明子程序
            continue;
        }
        else if(symid == SEMICN){//如果是';',则为一个变量定义
            strcpy(tempbackupline2, backupline);
            strcpy(backupline, tempbackupline1);
            templnum2 = lnum;
            lnum = templnum1;
            value = 0;
            ischar = tempid == INTTK ? INT : tempid == CHARTK ? CHAR : FLOAT;
            paranum = 0;
            pushtable(name, VARIABLE, value, paranum, ischar, 0);
            lnum = templnum2;
            strcpy(backupline, tempbackupline2);
            getsym();
            continue;
        }
        else if(symid == LPARENT){//如果是'(',则为函数定义
            symid = tempid;
            cnum = tempcnum;
            ch = tempch;
            break;
        }
        else{
            error(1);
            cout << "var define wrong" << endl;
            continue;
        }
    }
    if(symid == INTTK || symid == CHARTK || symid == FLOATTK || symid == VOIDTK)
        ;
    else{
        error(4);
        cout << "function define wrong" << endl;
    }
    while(symid == INTTK || symid == CHARTK || symid == FLOATTK || symid == VOIDTK){//函数部分
        returnnum = 0;
        if(symid == INTTK || symid == CHARTK || symid == FLOATTK){//＜有返回值函数定义＞  ::=  ＜声明头部＞‘(’＜参数＞‘)’ ‘{’＜复合语句＞‘}’
            int tepid = symid;
            int templnum = lnum;
            ifreturn = 1;
            getsym();
            if(symid != IDEN){//函数名
                error(0);
                itoa(errornum, name, 10);
                cout << "function id wrong" << endl;
            }
            else{
                strcpy(name,id.c_str());
                getsym();
            }
            gen(name, 0, 0);
            kind = FUNCTION;
            ischar = (tepid == INTTK) ? INT : (tepid == CHARTK) ? CHAR : FLOAT;
            value = 1;
            paranum = 0;
            pushtable(name, kind, value, paranum, ischar, 0);
            if(symid != LPARENT){//'('
                error(0);
                cout << "lost (" << endl;
            }
            else{
                getsym();
            }
            parametertable();//处理参数
            if(symid != RPARENT){//')'
                error(0);
                cout << "lost )" << endl;
            }
            else{
                getsym();
            }
            if(symid != LBRACE){//'{'
                error(0);
                cout << "lost {" << endl;
            }
            else{
                getsym();
            }
            complexsentence();//处理复合语句
            if(symid != RBRACE){//'}'
                error(0);
                cout << "lost }" << endl;
            }
            else{
                getsym();
            }
            if(returnnum == 0){
                errornum++;
                cout << templnum << endl;
                cout << name << endl;
                cout << "no return value" << endl;
            }
            else{
                gen(opr, 0, 0);
            }
        }

        if(symid == VOIDTK){//无返回值函数或者主函数
            ifreturn = 0;
            getsym();
            if(symid == MAINTK){//＜主函数＞    ::= void main‘(’‘)’ ‘{’＜复合语句＞‘}’
                strcpy(name, "main");
                gen(name, 0, 0);
                code[0].a = cx;
                kind = FUNCTION;
                value = 0;
                ischar = 0;
                paranum = 0;
                pushtable(name, kind, value, paranum, ischar, 0);
                getsym();
                if(symid != LPARENT){
                    error(0);
                    cout << "lost (" << endl;
                }
                else{
                    getsym();
                }
                if(symid != RPARENT){
                    error(0);
                    cout << "lost )" << endl;
                }
                else{
                    getsym();
                }
                if(symid != LBRACE){
                    error(0);
                    cout << "lost {" << endl;
                }
                else{
                    getsym();
                }
                complexsentence();
                if(symid != RBRACE){
                    error(0);
                    cout << "lost }" << endl;
                }
                gen("END", 0, 0);
                return;//源程序结束，跳出
            }
            else{//＜无返回值函数定义＞  ::= void＜标识符＞‘(’＜参数＞‘)’‘{’＜复合语句＞‘}’
                if(symid != IDEN){//函数名
                    error(0);
                    itoa(errornum, name, 10);
                    cout << "function id wrong" << endl;
                }
                else{
                    strcpy(name, id.c_str());
                    getsym();
                }
                gen(name, 0, 0);
                kind = FUNCTION;
                value = 0;
                ischar = 0;
                paranum = 0;
                pushtable(name, kind, value, paranum, ischar, 0);
                if(symid != LPARENT){
                    error(0);
                    cout << "lost (" << endl;
                }
                else{
                   getsym();
                }
                parametertable();
                if(symid != RPARENT){
                    error(0);
                    cout << "lost )" << endl;
                }
                else{
                    getsym();
                }
                if(symid != LBRACE){
                    error(0);
                    cout << "lost {" << endl;
                }
                else{
                    getsym();
                }
                complexsentence();
                if(symid != RBRACE){
                    error(0);
                    cout << "lost }" << endl;
                }
                else{
                    getsym();
                }
                gen(opr, 0, 0);
            }
        }
    }
}
