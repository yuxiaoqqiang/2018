#include "data.h"
#include "function.h"
#include "global.h"
//�����ʽ��    ::= �ۣ������ݣ��{���ӷ�����������}
void expression(){
    havefloat = 0;
    factornum = 0;
    onlychar = 0;
    if(symid == PLUS || symid == MINU){//��+/-�����,��Ҫ�ٶ�һ������
        if(symid == PLUS){
            getsym();
            term();
        }
        else{
            getsym();
            term();
            gen(opr, 0, 1);
        }
    }
    else{
        term();
    }
    while(symid == PLUS || symid == MINU){
        if(symid == PLUS){
            getsym();
            term();
            gen(opr, havefloat, 2);
        }
        else{
            getsym();
            term();
            gen(opr, havefloat, 3);
        }
    }
    return;
}

//���     ::= �����ӣ�{���˷�������������ӣ�}
void term(){
    factor();
    while(symid == MULT || symid == DIV){
            if(symid == MULT){
                getsym();
                factor();
                gen(opr, havefloat, 4);//�˷�
                continue;
            }
            if(symid == DIV){
                getsym();
                factor();
                gen(opr, havefloat, 5);//����
                continue;
            }
    }
    return;
}


//�����ӣ�    ::= ����ʶ����������ʶ������[�������ʽ����]������������|��ʵ����|���ַ��������з���ֵ����������䣾|��(�������ʽ����)��
void factor(){
    char names[30];
    int t;
    if(symid == IDEN){//����ʶ����������ʶ������[�������ʽ����]�������з���ֵ����������䣾
        strcpy(names, id.c_str());
        getsym();
        if(symid == LPARENT){ //�����'('�����ǣ��з���ֵ����������䣾
            getsym();
            tempfactornum = factornum;
            valueofpara(names);
            factornum = tempfactornum;
            if(symid != RPARENT){
                error(0);
                cout << "lost (" << endl;
            }
            else{
                getsym();
            }
            t = searchst(names, 1, 1);
            if(t == -1){
                error(6);
                cout << "undefined function" << endl;
                return;
            }
            else if(t == -2){
                error(6);
                cout << "no return function" << endl;
                return;
            }
            if(maintable.element[t].datakind == FLOAT && maintable.element[t].value == 1){
                havefloat = 1;
            }
            if(maintable.element[t].datakind == CHAR && maintable.element[t].value == 1){
                onlychar = factornum == 0 ? 1 : 0;
            }
            gen(cal, maintable.element[t].paranum, searchfunction(names));
        }
        else if(symid == LBRACK){//�����'[',��������
            int temphavefloat = 0;
            t = searchst(names, 0, 0);
            if(t == -1){
                error(6);
                cout << "undefined id" << endl;
                return;
            }
            if(maintable.element[t].kind == CONST){
                error(6);
                cout << "array can not be a con" << endl;
                return;
            }
            getsym();
            tempfactornum = factornum;
            temphavefloat = havefloat;
            expression();
            if(havefloat == 1){
                error(0);
                cout << "inside array can't be a float" << endl;
            }
            havefloat = temphavefloat;
            factornum = tempfactornum;
            if(symid != RBRACK){
                error(0);
                cout << "lost ]" << endl;
            }
            else{
                switch(maintable.element[t].kind){
                case VARIABLE:
                    gen(lod, 1, maintable.element[t].address);
                    break;
                case PARA:
                    gen(lod, 1, maintable.element[t].address);
                    break;
                }
                getsym();
            }
            if(maintable.element[t].datakind == CHAR){
                onlychar = factornum == 0 ? 1 : 0;
            }
            if(maintable.element[t].datakind == FLOAT){
                havefloat = 1;
            }
        }
        else if(symid != LBRACK){
            t = searchst(names, 0, 0);
            if(t == -1){
                error(6);
                cout << "undefined id" << endl;
                return;
            }
            switch(maintable.element[t].kind){
            case CONST:
                gen(lit, 0, maintable.element[t].value);
                break;
            case VARIABLE:
                gen(lod, 0, maintable.element[t].address);
                break;
            case PARA:
                gen(lod, 0, maintable.element[t].address);
                break;
            }
            if(maintable.element[t].datakind == CHAR){
                onlychar = factornum == 0 ? 1 : 0;
            }
            if(maintable.element[t].datakind == FLOAT){
                havefloat = 1;
            }
        }
    }
    else if(symid == LPARENT){//��(�������ʽ����)��
        getsym();
        expression();
        if(symid != RPARENT){
            error(0);
            cout << "lost )" << endl;
        }
        else{
            getsym();
        }
    }
    else if(symid == PLUS || symid == MINU || symid == INTCON || symid == CHARCON || symid == FLOATCON){// ��������|��ʵ����|���ַ���
        int temp = 1;
        while(symid == PLUS || symid == MINU){
            if(symid == PLUS){
                temp *= 1;
                getsym();
            }
            else if(symid == MINU){
                temp *= -1;
                getsym();
            }
        }
        if(symid == INTCON){
            gen(lit, 0, temp * num);
        }
        else if(symid == CHARCON){
            gen(lit, 0, id.c_str()[0]);
            onlychar = factornum == 0 ? 1 : 0;
        }
        else{
            havefloat = 1;
            gen(lit, 0, temp * fnum);
        }
        getsym();
    }
    else{
        error(0);//���Ӵ���
        cout << "fact wrong" << endl;
        return;
    }
    factornum++;
}
