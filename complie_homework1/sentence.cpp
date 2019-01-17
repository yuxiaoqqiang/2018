#include "data.h"
#include "function.h"
#include "global.h"

//��������䣾   ::=  �ۣ�����˵�����ݣۣ�����˵�����ݣ�����У�
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
        int templnum2;//�ָ��ֳ���
        strcpy(tempbackupline1, backupline);
        templnum1 = lnum;
        getsym();
        if(symid != IDEN){
            error(1);
            cout << "var id wrong" << endl;
            continue;
        }
        strcpy(name, id.c_str());//��������
        getsym();
        if(symid == COMMA || symid == LBRACK){//�����','����'[',���Ƕ������������������鶨��
            symid = tempid;
            cnum = tempcnum;
            ch = tempch;
            varstate();
            continue;
        }
        else if(symid == SEMICN){//�����';',��Ϊһ����������
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

//������У�   ::= ������䣾��
void sentencelist(){
    if(symid == IFTK || symid == WHILETK || symid == SWITCHTK || symid == LBRACE
        || symid == IDEN || symid == RETURNTK || symid == SCANFTK || symid == PRINTFTK || symid == SEMICN){
        sentence();
    }
    /*
    ���һ��������������õĵ���Ϊif,while..�ȱ�����,˵���ǻ������δ����
    ��������sentence()���д���
    */
    while(symid == IFTK || symid == WHILETK || symid == SWITCHTK || symid == LBRACE
        || symid == IDEN || symid == RETURNTK || symid == SCANFTK || symid == PRINTFTK || symid == SEMICN){
        sentence();
    }
}

/*
����䣾    ::= ��������䣾����ѭ����䣾| ��{��������У���}�������з���ֵ����������䣾;
                             |���޷���ֵ����������䣾;������ֵ��䣾;��������䣾;����д��䣾;�����գ�; |�������䣾����������䣾;
*/
void sentence(){
    char names[30];
    if(symid == IFTK){//�������
        ifsentence();
        return;
    }

    else if(symid == WHILETK){//ѭ�����
        loopsentence();
        return;
    }

    else if(symid == SWITCHTK){//������
        switchsentence();
        return;
    }

    else if(symid == LBRACE){//{������С�}
        getsym();
        sentencelist();
        if(symid != RBRACE){
            error(0);
            return;
        }
        getsym();
        return;
    }
    else if(symid == IDEN){//����������������ֵ��䣾;
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
        if(symid == LBRACK){//����
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
        if(symid == ASSIGN){//��ֵ���
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
        else if(symid == LPARENT){//�����������
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

    else if(symid == SCANFTK){//�����
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

    else if(symid == PRINTFTK){//д���
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

    else if(symid == RETURNTK){//�������
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

    else if(symid == SEMICN){//�����
        getsym();
        return;
    }

    else{//�Ƿ��ľ���
        error(1);
        cout << "illegal sentence" << endl;
        return;
    }
}

//������䣾    ::=  scanf ��(������ʶ����{,����ʶ����}��)��
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
        if(maintable.element[searchst(names, 0, 0)].kind == CONST){//����������
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
��д��䣾    ::=   printf ��(�����ַ�����,�����ʽ����)��|
                     printf ��(�����ַ�������)��| printf ��(�������ʽ����)��
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

//��������䣾   ::=  return[��(�������ʽ����)��]
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

//��������䣾  ::=  if ��(������������)������䣾��else����䣾��
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

//��������    ::=  �����ʽ������ϵ������������ʽ���������ʽ�� //���ʽΪ0����Ϊ�٣�����Ϊ��
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

//��ѭ����䣾   ::=   while '('��������')'����䣾
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
�������䣾  ::=  switch ��(�������ʽ����)�� ��{��������� ��}��
�������   ::=  ���������䣾{���������䣾}
���������䣾  ::=  case����ö�ٳ�����������䣾
����ö�ٳ�����   ::=  ��������| ���ַ���
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
