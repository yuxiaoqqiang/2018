#include "data.h"
#include "function.h"
#include "global.h"

//＜复合语句＞   ::=  ［＜常量说明＞］［＜变量说明＞］＜语句列＞
void complexsentence(){
    if(symid == CONSTTK){
        constate();
    }
    while(symid == INTTK || symid == CHARTK || symid == FLOATTK) {
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
        strcpy(name, id.c_str());//拷贝名字
        getsym();
        if(symid == COMMA || symid == LBRACK){//如果是','或者'[',则是多个变量定义或者是数组定义
            symid = tempid;
            cnum = tempcnum;
            ch = tempch;
            varstate();
            continue;
        }
        else if(symid == SEMICN){//如果是';',则为一个变量定义
            strcpy(tempbackupline2, backupline);
            strcpy(backupline, tempbackupline1);
            templnum2 = lnum;
            lnum = templnum1;
            value = 0;
            paranum = 0;
            ischar = tempid == INTTK ? INT : tempid == CHARTK ? CHAR : FLOAT;
            pushtable(name, VARIABLE, value, paranum, ischar, 0);
            lnum = templnum2;
            strcpy(backupline, tempbackupline2);
            getsym();
            continue;
        }
        else{
            error(5);
            cout << "lost ; | , | [" << endl;
            continue;
        }
    }
    sentencelist();
    return;
}

//＜语句列＞   ::= ｛＜语句＞｝
void sentencelist(){
    if(symid == IFTK || symid == WHILETK || symid == SWITCHTK || symid == LBRACE
        || symid == IDEN || symid == RETURNTK || symid == SCANFTK || symid == PRINTFTK || symid == SEMICN){
        sentence();
    }
    /*
    如果一条语句结束后所获得的单词为if,while..等保留字,说明是还有语句未处理，
    继续调用sentence()进行处理
    */
    while(symid == IFTK || symid == WHILETK || symid == SWITCHTK || symid == LBRACE
        || symid == IDEN || symid == RETURNTK || symid == SCANFTK || symid == PRINTFTK || symid == SEMICN){
        sentence();
    }
}

/*
＜语句＞    ::= ＜条件语句＞｜＜循环语句＞| ‘{’＜语句列＞‘}’｜＜有返回值函数调用语句＞;
                             |＜无返回值函数调用语句＞;｜＜赋值语句＞;｜＜读语句＞;｜＜写语句＞;｜＜空＞; |＜情况语句＞｜＜返回语句＞;
*/
void sentence(){
    char names[30];
    if(symid == IFTK){//条件语句
        ifsentence();
        return;
    }

    else if(symid == WHILETK){//循环语句
        loopsentence();
        return;
    }

    else if(symid == SWITCHTK){//情况语句
        switchsentence();
        return;
    }

    else if(symid == LBRACE){//{‘语句列’}
        getsym();
        sentencelist();
        if(symid != RBRACE){
            error(0);
            return;
        }
        getsym();
        return;
    }
    else if(symid == IDEN){//函数调用语句｜＜赋值语句＞;
        int mark = 0;
        strcpy(names, id.c_str());
        if(strcmp(names, "for") == 0){
            error(0);
            cout << "for is not legal" << endl;
            int i = 0;
            while(symid != LBRACE){
                getsym();
            }
            i++;
            while(1){
                getsym();
                if(symid == RBRACE)
                    i--;
                else if(symid == LBRACE)
                    i++;
                if(i == 0)
                    break;
            }
            getsym();
            return;
        }
        getsym();
        if(symid == LBRACK){//数组
            if(searchst(names, 0, 0) == -1){
                error(1);
                cout << "id not define" << endl;
                return;
            }
            if(maintable.element[searchst(names, 0, 0)].paranum == 0){
                error(1);
                cout << "type not array" << endl;
                return;
            }
            mark = 1;
            getsym();
            expression();
            if(havefloat == 1){
                error(1);
                cout << "inside array can't be a float" << endl;
                return;
            }
            if(symid != RBRACK){
                error(0);
                cout << "lost ]" << endl;
            }
            else{
                getsym();
            }
        }
        if(symid == ASSIGN){//赋值语句
            if(searchst(names, 0, 0) == -1){
                error(1);
                cout << "id not define" << endl;
                return;
            }
            if(maintable.element[searchst(names,0,0)].kind == CONST){
            error(1);
            cout << "con can't be assigned" << endl;
            return;
            }
            getsym();
            expression();
            if(symid != SEMICN){
                error(0);
                cout << "lost ;" << endl;
            }
            else{
               getsym();
            }
            gen(sto, mark, maintable.element[searchst(names, 0, 0)].address);
            return;
        }
        else if(symid == LPARENT){//函数调用语句
            getsym();
            valueofpara(names);
            if(symid != RPARENT){
                error(0);
                cout << "lost (" << endl;
            }
            else{
                getsym();
            }
            if(symid != SEMICN){
                error(0);
                cout << "lost ;" << endl;
            }
            else{
                getsym();
            }
            if(searchst(names, 1, 0) == -1){
                error(1);
                cout << "function not exist" << endl;
                return;
            }
            gen(cal, maintable.element[searchst(names, 1, 0)].paranum, searchfunction(names));
            return;
        }
        else{
            error(1);
            cout << "assign or call sentence wrong" << endl;
            return;
        }
    }

    else if(symid == SCANFTK){//读语句
        scanfsentence();
        if(symid != SEMICN){
            error(0);
            cout << "lost ;" << endl;
        }
        else{
            getsym();
        }
        return;
    }

    else if(symid == PRINTFTK){//写语句
        printfsentence();
        if(symid != SEMICN){
            error(0);
            cout << "lost ;" << endl;
        }
        else{
            getsym();
        }
        return;
    }

    else if(symid == RETURNTK){//返回语句
        returnsentence();
        if(symid != SEMICN){
            error(0);
            cout << "lost ;" << endl;
        }
        else{
            getsym();
        }
        return;
    }

    else if(symid == SEMICN){//空语句
        getsym();
        return;
    }

    else{//非法的句子
        error(1);
        cout << "illegal sentence" << endl;
        return;
    }
}

//＜读语句＞    ::=  scanf ‘(’＜标识符＞{,＜标识符＞}‘)’
void scanfsentence(){
    int mark = 0;
    char names[30];
    getsym();
    if(symid != LPARENT){
        error(0);
        cout << "lost (" << endl;
        mark = 1;
    }
    do{
        if(mark == 0)
            getsym();
        if(symid != IDEN){
            error(6);
            cout << "illegal id" << endl;
            return;
        }
        strcpy(names, id.c_str());
        if(searchst(names, 0, 0) == -1){
            error(6);
            cout << "undefined id" << endl;
            return;
        }
        if(maintable.element[searchst(names, 0, 0)].kind == CONST){//常量，报错
            error(6);
            cout << "can not scan in a con" << endl;
            return;
        }
        if(maintable.element[searchst(names, 0, 0)].kind == FUNCTION){
            error(6);
            cout << "can not scan in a function" << endl;
            return;
        }
        gen(red, maintable.element[searchst(names, 0, 0)].datakind, maintable.element[searchst(names, 0, 0)].address);
        getsym();
    }while(symid == COMMA);
    if(symid != RPARENT){
        error(0);
        cout << "lost )" << endl;
    }
    else{
       getsym();
    }
    return;
}

/*
＜写语句＞    ::=   printf ‘(’＜字符串＞,＜表达式＞‘)’|
                     printf ‘(’＜字符串＞‘)’| printf ‘(’＜表达式＞‘)’
*/
void printfsentence(){
    char names[30];
    getsym();
    if(symid != LPARENT){
        error(0);
        cout << "lost (" << endl;
    }
    else{
        getsym();
    }
    if(symid == STRCON){
        strcpy(str.s[str.index++].str, id.c_str());
        getsym();
        if(symid == COMMA){
            getsym();
            expression();
            gen(wrt, 0, str.index - 1);
            gen(wrt, 1, onlychar);
        }
        else
            gen(wrt, 0, str.index - 1);
    }
    else{
        expression();
        gen(wrt, 1, onlychar);
    }
    if(symid != RPARENT) {
        error(0);
        cout << "lost )" << endl;
    }
    else{
        getsym();
    }
    return;
}

//＜返回语句＞   ::=  return[‘(’＜表达式＞‘)’]
void returnsentence(){
    getsym();
    if(symid == LPARENT){
        getsym();
        expression();
        if(symid != RPARENT){
            error(0);
            cout << "lost )" << endl;
        }
        else{
            if(ifreturn == 1)
                returnnum++;
            else{
                error(0);
                cout << "void can't have return value" << endl;
            }
            getsym();
        }
        gen(opr, 0, 0);
    }
    else if(symid == SEMICN){
        gen(opr, 0, 0);
    }
    else{
        error(6);
        cout << "return wrong, may be miss ( or ;" << endl;
    }
    return;
}

//＜条件语句＞  ::=  if ‘(’＜条件＞‘)’＜语句＞［else＜语句＞］
void ifsentence(){
    int cx1, cx2;
    getsym();
    if(symid != LPARENT){
        error(0);
        cout << "lost (" << endl;
    }
    else{
       getsym();
    }
    condition();
    if(symid != RPARENT){
        error(0);
        cout << "lost )" << endl;
    }
    else{
        getsym();
    }
    cx1 = cx;
    gen(jpc, 0, 0);
    sentence();
    if(symid == ELSETK){
        cx2 = cx;
        gen(jmp, 0, 0);
        code[cx1].a = cx;
        getsym();
        sentence();
        code[cx2].a = cx;
        return;
    }
    else{
        code[cx1].a = cx;
        return;
    }
}

//＜条件＞    ::=  ＜表达式＞＜关系运算符＞＜表达式＞｜＜表达式＞ //表达式为0条件为假，否则为真
void condition(){
    expression();
    if(symid == LSS || symid == LEQ || symid == GRE || symid == GEQ || symid == NEQ || symid == EQL){
        if(symid == LSS){
            getsym();
            expression();
            gen(opr, 0, 10);
        }
        else if(symid == LEQ){
            getsym();
            expression();
            gen(opr, 0, 13);
        }
        else if(symid == GRE){
            getsym();
            expression();
            gen(opr, 0, 12);
        }
        else if(symid == GEQ){
            getsym();
            expression();
            gen(opr, 0, 11);
        }
        else if(symid ==NEQ){
            getsym();
            expression();
            gen(opr, 0, 9);
        }
        else if(symid == EQL){
            getsym();
            expression();
            gen(opr, 0, 8);
        }
        return;
    }
    gen(lit, 0, 0);
    gen(opr, 0, 9);
    return;
}

//＜循环语句＞   ::=   while '('＜条件＞')'＜语句＞
void loopsentence(){
    int cx1, cx2;
    cx1 = cx;
    getsym();
    if(symid != LPARENT){
        error(0);
        cout << "lost (" << endl;
    }
    else{
        getsym();
    }
    condition();
    if(symid != RPARENT){
        error(0);
        cout << "lost )" << endl;
    }
    else{
        getsym();
    }
    cx2 = cx;
    gen(jpc, 0, 0);
    sentence();
    gen(jmp, 0, cx1);
    code[cx2].a = cx;
    return;
}
/*
＜情况语句＞  ::=  switch ‘(’＜表达式＞‘)’ ‘{’＜情况表＞ ‘}’
＜情况表＞   ::=  ＜情况子语句＞{＜情况子语句＞}
＜情况子语句＞  ::=  case＜可枚举常量＞：＜语句＞
＜可枚举常量＞   ::=  ＜整数＞| ＜字符＞
*/

void casesentence(Case ca){
    int cx1,cx2[MAX];
    int i = 0;
    int mark = 0;
    getsym();
    if(symid != INTCON && symid != CHARCON && symid != PLUS && symid != MINU){
        error(0);
        cout << "case wrong" << endl;
    }
    if(symid == PLUS){
        getsym();
        if(symid != INTCON){
            error(0);
            cout << "data type wrong" << endl;
            mark = 1;
        }
    }
    else if(symid == MINU){
        getsym();
        if(symid != INTCON){
            error(0);
            cout << "data type wrong" << endl;
            mark = 1;
        }
        num = -num;
    }
    ca.kind = symid == INTCON ? INT : CHAR;
    ca.c[ca.index++].value = ca.kind == INT ? num : int(id.c_str()[0]);
    gen(lit, 0, symid == INTCON ? num : int(id.c_str()[0]));
    if(mark == 1)
        mark = 0;
    else
        getsym();
    if(symid != COLON){
        error(0);
    }
    else{
       getsym();
    }
    gen(opr, 0, 14);
    cx1 = cx;
    gen(jpc, 1, 0);
    sentence();
    cx2[i++] = cx;
    gen(jmp, 0, 0);
    while(1){
        if(symid == CASETK){
            code[cx1].a = cx;
        }
        else{
            code[cx1].a = cx;
            while(i > 0){
                code[cx2[--i]].a = cx;
            }
            break;
        }
        while(symid == CASETK){
            getsym();
            if(symid != INTCON && symid != CHARCON && symid != PLUS && symid != MINU){
                error(0);
                cout << "case wrong" << endl;
            }
            if(symid == PLUS){
                getsym();
                if(symid != INTCON){
                    error(0);
                    cout << "case data type wrong" << endl;
                }
            }
            else if(symid == MINU){
                getsym();
                if(symid != INTCON){
                    error(0);
                    cout << "case data type wrong" << endl;
                }
                num = -num;
            }
//            if(symid == INTCON && ca.kind ==CHAR){
//                error(0);
//                cout << "switch different type data" << endl;
//            }
//            else if(symid == CHARCON && ca.kind == INT){
//                error(0);
//                cout << "switch different type data" << endl;
//            }
            int j;
            if(symid == INTCON){
                for(j = 0; j < ca.index; j++){
                    if(ca.c[j].value == num){
                        error(0);
                        cout << "case same data" << endl;
                    }
                }
            }
            else{
                for(j = 0; j < ca.index; j++){
                    if(ca.c[j].value == (int)id.c_str()[0]){
                        error(0);
                        cout << "case same data" << endl;
                    }
                }
            }
            ca.c[ca.index++].value = ca.kind == INT ? num : int(id.c_str()[0]);
            gen(lit, 0, symid == INTCON ? num : int(id.c_str()[0]));
            getsym();
            if(symid != COLON){
                error(0);
                cout << "lost :" << endl;
            }
            else{
               getsym();
            }
            gen(opr, 0, 14);
            cx1 = cx;
            gen(jpc, 1, 0);
            sentence();
            cx2[i++] = cx;
            gen(jmp, 0, 0);
            break;
        }
    }
    return;
}
void switchsentence(){
    Case ca;
    int i = 1;
    ca.index = 0;
    ca.kind = 0;
    getsym();
    if(symid != LPARENT){
        error(0);
        cout << "lost (" << endl;
    }
    else{
       getsym();
    }
    expression();
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
    if(symid != CASETK){
        error(0);
        cout << "case wrong" << endl;
        while(symid != CASETK){
            if(symid == LBRACE)
                i++;
            else if(symid == RBRACE)
                i--;
            if(i == 0)
                break;
            getsym();
        }
    }
    else{
        casesentence(ca);
    }
    if(symid != RBRACE){
        error(0);
        cout << "lost }" << endl;
    }
    else{
       getsym();
    }
    return;
}
