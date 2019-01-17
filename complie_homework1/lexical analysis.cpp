#include "global.h"
#include "function.h"
#include "data.h"

const int kwdnum = 14;//�����ָ�����1
char *word[] = {//������
    "case", "char", "const",//0~2
    "else", "float",  //3~4
    "if", "int", "main",//5~7
    "printf", "return",  //8~9
    "scanf", "switch",//10~11
    "void", "while"//12~13
};

char *wsym[] = {//�����
    "CASETK", "CHARTK", "CONSTTK",
    "ELSETK", "FLOATTK",
    "IFTK", "INTTK", "MAINTK",
    "PRINTFTK", "RETURNTK",
    "SCANFTK", "SWITCHTK",
    "VOIDTK", "WHILETK"
};

void getch(){//backupline�����������ֳ��ģ�Ŀ����Ϊ�˳���ʱ���㴦��
    int i = 0;
    if(cnum == llen && ~line[llen]){//�ж��Ƿ���һ�еĿ�ͷ���β���������������
        ch = fgetc(src);
        while(ch == ' ' || ch == '\n' || ch == '\t'){
            if(ch == '\n') {
                lnum++;
            }
            if(ch != '\n')
                backupline[i++] = ch;//ԭ������һ��������
            ch = fgetc(src);
        }
        for(llen = 0; ch != '\n' && ch != EOF; llen++){
            line[llen] = ch;//����һ������
            backupline[i++] = ch;
            ch = fgetc(src);
        }
        if(ch == EOF)
            line[llen] = EOF;
        else
            line[llen] = '\n';
        backupline[i] = '\0';
        cnum = 0;
        ch = '\n';
        lnum++;//����+1
    }
    else{
        ch = line[cnum++];//��line��ȡ���ַ�
    }
}

int getsym(){
    id = "";
    while(isspace(ch) && ch != EOF){//ȥ���ո�tab,�س�,���з�
        getch();
    }
    if(ch == EOF){
        symid = -1;
        return OVER;
    }
    if(isalpha(ch) || ch == '_'){//��ĸ��_
        while(isalpha(ch) || isdigit(ch) || ch == '_'){
            ch = tolower(ch);//��Ϊ��ʶ�������ִ�Сд������ȫ��ת��ΪСд���б���
            id += ch;
            getch();
        }
        int iter;
        for(iter = 0; iter < kwdnum; iter++){
            if (strcmp(word[iter], id.c_str()) == 0){
                sym = wsym[iter];
                symid = iter + 1;
                break;
            }
        }
        if(iter == kwdnum){
            sym = "IDEN";
            symid = IDEN;
        }
    }
    else if(isdigit(ch)){//0~9
        sym = "INTCON";
        symid = INTCON;
        num = 0;
        while(isdigit(ch)){
            id += ch;
            num = num * 10 + (int)(ch - '0');
            getch();
        }
        if(ch == '.'){
            id += ch;
            sym = "FLOATCON";
            symid = FLOATCON;
            float t = 0.1;
            fnum = num * 1.0;
            getch();
            while(isdigit(ch)){
                id += ch;
                fnum = fnum + (int)(ch - '0') * t;
                t /= 10;
                getch();
            }
        }
    }
    else if(ch == '='){
        id += ch;
        sym = "ASSIGN";
        symid = ASSIGN;
        getch();
        if(ch == '='){
            id += ch;
            sym = "EQL";
            symid = EQL;
            getch();
        }
    }
    else if(ch == '<'){
        id += ch;
        getch();
        if(ch == '='){
            id += ch;
            sym = "LEQ";
            symid = LEQ;
            getch();
        }
        else{
            sym = "LSS";
            symid = LSS;
        }
    }
    else if(ch == '>'){
        id += ch;
        getch();
        if(ch == '=' ){
            id += ch;
            sym = "GEQ";
            symid = GEQ;
            getch();
        }
        else{
            sym = "GRE";
            symid = GRE;
        }
    }
    else if(ch == '!'){
        id += ch;
        getch();
        if(ch == '='){
            id += ch;
            sym = "NEQ";
            symid = NEQ;
            getch();
        }
    }
    else if(ch == '\"'){
        getch();
        while (ch == 32 || ch == 33 || (ch <= 126 && ch >= 35)){//�ַ���
            id += ch;
            getch();
        }
        if(ch == '\"'){
            getch();
            sym = "STRCON";
            symid = STRCON;
        }
        else{
            return WRONG;
        }
    }
    else if(ch == '\''){
        getch();
        if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '_' || isalnum(ch)){//�ַ�
            id += ch;
            getch();
        }
        else{
            return WRONG;
        }
        if (ch == '\''){
            sym = "CHARCON";
            symid = CHARCON;
            getch();
        }
        else{
            return WRONG;
        }
    }
    else{
        if(ch == '+'){
            sym = "PLUS";
            symid = PLUS;
        }
        else if(ch == '-'){
            sym = "MINU";
            symid = MINU;
        }
        else if(ch == '*'){
            sym = "MULT";
            symid = MULT;

        }
        else if(ch == '/'){
            sym = "DIV";
            symid = DIV;
        }
        else if(ch == ','){
            sym = "COMMA";
            symid = COMMA;
        }
        else if(ch == ':'){
            sym = "COLON";
            symid = COLON;
        }
        else if(ch == ';'){
            sym = "SEMICN";
            symid = SEMICN;
        }
        else if(ch == '{'){
            sym = "LBRACE";
            symid = LBRACE;
        }
        else if(ch == '}'){
            sym = "RBRACE";
            symid = RBRACE;
        }
        else if(ch == '['){
            sym = "LBRACK";
            symid = LBRACK;
        }
        else if(ch == ']'){
            sym = "RBRACK";
            symid = RBRACK;
        }
        else if(ch == '('){
            sym = "LPARENT";
            symid = LPARENT;
        }
        else if(ch == ')'){
            sym = "RPARENT";
            symid = RPARENT;
        }
        id += ch;
        getch();
    }
    return 0;
}
