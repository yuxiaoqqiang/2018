#include "data.h"
#include "function.h"
#include "global.h"
/*
＜常量定义＞   ::=   int＜标识符＞＝＜整数＞{,＜标识符＞＝＜整数＞}
                                    | float＜标识符＞＝＜实数＞{,＜标识符＞＝＜实数＞}
                                    | char＜标识符＞＝＜字符＞{,＜标识符＞＝＜字符＞}
*/
void condef(int tempkind){
    int tempc;
    if(symid == IDEN){
        strcpy(name, id.c_str());
        getsym();
        if(symid == ASSIGN){
            getsym();
        }
        else{
            error(0);
            cout << "lost =" << endl;
        }
        if(symid == PLUS || symid == MINU){
            int tempsym;
            tempsym = symid;
            getsym();
            if(tempkind == FLOATTK && (symid == PLUS || symid == MINU)){
                if(symid == PLUS)
                    ;
                else
                    tempsym == tempsym == PLUS ? MINU : PLUS;
                getsym();
            }
            if(tempkind == INTTK && symid == INTCON){
                if(tempsym == PLUS)
                    value = num;
                else{
                    value = -num;
                }
                pushtable(name, kind, value, paranum, ischar, 0);
            }
            else if(tempkind == FLOATTK){
                if(symid == FLOATCON){
                    if(tempsym == PLUS)
                        value = fnum;
                    else{
                        value = -fnum;
                    }
                }
                else if(symid == INTCON){
                    if(tempsym == PLUS)
                        value = num;
                    else{
                        value = -num;
                    }
                }
                else{
                    error(6);
                    cout << "con data type wrong" << endl;
                    return;
                }
                pushtable(name, kind, value, paranum, ischar, 0);
            }
            else{
                error(6);
                cout << "con data type wrong" << endl;
                return;
            }
        }
        else if(tempkind == CHARTK && symid == CHARCON){
            value = id.c_str()[0];
            pushtable(name, kind, value, paranum, ischar, 0);
        }
        else if(tempkind == INTTK && symid == INTCON){
            value = num;
            pushtable(name, kind, value, paranum, ischar, 0);
        }
        else if(tempkind == FLOATTK){
            if(symid == FLOATCON){
                value = fnum;
            }
            else if(symid == INTCON){
                value = num;
            }
            else{
                error(6);
                cout << "con data type wrong" << endl;
                return;
            }
            pushtable(name, kind, value, paranum, ischar, 0);
        }
        else{
            error(6);
            cout << "con define wrong" << endl;
            return;
        }
    }
    else{
        error(6);
        cout << "con id wrong" << endl;
        return;
    }
    getsym();
}

//＜常量说明＞ ::=  const＜常量定义＞;{ const＜常量定义＞;}
void constate(){
    while(symid == CONSTTK){
        getsym();
        int tempkind;
        if(symid == INTTK || symid == CHARTK || symid == FLOATTK){
            tempkind = symid;
            kind = CONST;
            ischar = tempkind == INTTK ? INT : tempkind == CHARTK ? CHAR : FLOAT;
            paranum = 0;
            getsym();
            condef(tempkind);
            while(symid == COMMA){
                getsym();
                condef(tempkind);//同一类型标识符后必须跟着相同类型的数据
            }
            if(symid != SEMICN){
                error(0);
                cout << "lost ;" << endl;
                continue;
            }
            else{
                getsym();
            }
        }
        else{
            error(1);
            cout << "lost type" << endl;
            continue;
        }
    }
    return;
}

//＜变量定义＞  ::= ＜类型标识符＞(＜标识符＞|＜标识符＞‘[’＜无符号整数＞‘]’){,(＜标识符＞|＜标识符＞‘[’＜无符号整数＞‘]’ )}
void vardef(){
    int tpkind;
    if(symid == INTTK || symid == CHARTK || symid == FLOATTK){
        tpkind = (symid == INTTK) ? INT : (symid == CHARTK) ? CHAR : FLOAT;
        kind = VARIABLE;
        getsym();
        if(symid != IDEN){
            error(1);
            cout << "var id wrong" << endl;
            return;
        }
        else{
            strcpy(name, id.c_str());
        }
    }
    else{
        error(1);
        cout << "var type wrong" << endl;
        return;
    }
    getsym();
    value = 0;
    ischar = tpkind;
    paranum = 0;
    if(symid == LBRACK){//如果是数组
        int tempnum;
        getsym();
        if(symid != INTCON){
            error(1);
            cout << "array data wrong" << endl;
            return;
        }
        tempnum = num;
        getsym();
        if(symid != RBRACK){
            error(0);
            cout << "lost ]";
        }
        else{
            getsym();
        }
        pushtable(name, kind, value, paranum, ischar, tempnum);
        pushnumtable(searchst(name, 0, 0), tpkind, tempnum);
    }
    else{
        pushtable(name, kind, value, paranum, ischar, 0);
    }
    while(symid == COMMA){//如果后面是逗号，那么变量定义未结束
        getsym();
        if(symid != IDEN){
            error(1);
            cout << "var type wrong" << endl;
            return;
        }
        strcpy(name, id.c_str());
        getsym();
        if(symid == LBRACK){//如果是数组
            int tempnum;
            getsym();
            if(symid != INTCON){
                error(1);
                cout << "array data wrong" << endl;
                return;
            }
            tempnum = num;
            getsym();
            if(symid != RBRACK){
                error(0);
                cout << "lost ]" << endl;
            }
            else{
                getsym();
            }
            pushtable(name, kind, value, paranum, ischar, tempnum);
            pushnumtable(searchst(name, 0, 0), tpkind, tempnum);
        }
        else{
            pushtable(name, kind, value, paranum, ischar, 0);
        }
    }
}

//＜变量说明＞  ::= ＜变量定义＞;{＜变量定义＞;}
void varstate(){
    vardef();
    if(symid != SEMICN){
        error(0);
        cout << "lost ;" << endl;
    }
    else{
        getsym();
    }
    return;
}
