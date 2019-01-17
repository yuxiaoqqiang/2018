#include "data.h"
#include "function.h"
#include "global.h"

void gen(char* x, int y, float z){
    if(cx > cxmax){
        cout << "too long" << endl;
        exit(0);
    }
    else{
        strcpy(code[cx].f, x);
        code[cx].l = y;
        code[cx].a = z;
    }
    cx++;
    return;
}

int searchfunction(char* names){
    int j = 0;
    while(j < cx){
        if(strcmp(code[j].f, names) == 0)
            break;
        j++;
    }
    j++;
    return j;
}

void interpret(){
    table.index = 0;
    const int stacksize = 5000;
    int p, t;
    int index = 0;
    float s[stacksize];
    int op[MAX];
    Code i;
    t = 0;
    p = 0;
    while(1){
        i.a = code[p].a;
        strcpy(i.f, code[p].f);
        i.l = code[p].l;
        p++;
        if(strcmp(i.f, "lit") == 0){
            t++;
            s[t] = i.a;
        }
        else if(strcmp(i.f, "lod") == 0){
            t++;
            if(i.l == 0){
                s[t] = maintable.element[(int)i.a].value;
            }
            else{//array
                t--;
                sprintf(result, "%f", s[t]);
                int tempnum = 0;
                while(result[tempnum] != '\0'){
                    if(isdigit(result[tempnum]))
                        tempnum++;
                    else if(result[tempnum] == '.'){
                        tempnum++;
                        while(result[tempnum] != '\0'){
                            if(result[tempnum] == '0')
                                tempnum++;
                            else{
                                cout << "array wrong" << endl;
                                return;
                            }
                        }
                    }
                    else{
                        cout << "array wrong" << endl;
                        return;
                    }
                }
                if((int)s[t] >= numtable.num[searchnum((int)i.a)].paranum){
                    cout << "too long array" << endl;
                    exit(0);
                }
                s[t] = numtable.num[searchnum((int)i.a)].f[(int)s[t]];
            }
        }
        else if(strcmp(i.f, "sto") == 0){
            if(i.l == 0){
                maintable.element[(int)i.a].value = s[t];
            }
            else{//array
                sprintf(result, "%f", s[t-1]);
                int tempnum = 0;
                while(result[tempnum] != '\0'){
                    if(isdigit(result[tempnum]))
                        tempnum++;
                    else if(result[tempnum] == '.'){
                        tempnum++;
                        while(result[tempnum] != '\0'){
                            if(result[tempnum] == '0')
                                tempnum++;
                            else{
                                cout << "array wrong" << endl;
                                return;
                            }
                        }
                    }
                    else{
                        cout << "array wrong" << endl;
                        return;
                    }
                }
                if((int)s[t-1] >= numtable.num[searchnum((int)i.a)].paranum){
                    cout << "too long array" << endl;
                    exit(0);
                }
                numtable.num[searchnum((int)i.a)].f[(int)s[t-1]] = s[t];
                t--;
            }
            t--;
        }
        else if(strcmp(i.f, "jmp") == 0){
           p = (int)i.a;
        }
        else if(strcmp(i.f, "jpc") == 0){
            if(i.l == 0){//if,while
                if(s[t] == 0){
                    p = (int)i.a;
                    t--;
                }
                else
                    t--;
            }
            else if(i.l == 1){//case
                 if(s[t+1] == 0){
                    p = (int)i.a;
                }
            }
        }
        else if(strcmp(i.f, "opr") == 0){
            int m = 0;
            switch((int)i.a){
            case 0://return
                p = op[--index];
                table.index--;
                if(index == -1)
                    return;
                if(maintable.element[searchst(code[table.num[table.index].address - 1].f, 1, 0)].value == 1){
                    if(maintable.element[searchst(code[table.num[table.index].address - 1].f, 1, 0)].datakind != FLOAT)
                        s[t] = (int)s[t];
                }
                if(table.num[table.index].para == 0)
                    break;
                else{
                    while(maintable.element[searchst(code[table.num[table.index].address - 1].f, 1, 0) + m + 1].kind != FUNCTION){
                        maintable.element[searchst(code[table.num[table.index].address - 1].f, 1, 0) + m + 1].value = table.num[table.index].tempnum[m];
                        m++;
                    }
                }
                break;
            case 1:
                s[t] = -s[t];
                break;
            case 2:
                t = t-1;
                if(i.l == 1)
                    s[t] = s[t] + s[t+1];
                else
                    s[t] = (int)(s[t] + s[t+1]);
                break;
            case 3:
                t = t-1;
                if(i.l == 1)
                    s[t] = s[t] - s[t+1];
                else
                    s[t] = (int)(s[t] - s[t+1]);
                break;
            case 4:
                t = t-1;
                if(i.l == 1)
                    s[t] = s[t] * s[t+1];
                else
                    s[t] = (int)(s[t] * s[t+1]);
                break;
            case 5:
                t = t-1;
                if(i.l == 1)
                    s[t] = s[t] / s[t+1];
                else
                    s[t] = (int)(s[t] / s[t+1]);
                break;
            case 8:
                t = t-1;
                s[t] = s[t] == s[t+1];
                break;
            case 9:
                t = t-1;
                s[t] = s[t] != s[t+1];
                break;
            case 10:
                t = t-1;
                s[t] = s[t] < s[t+1];
                break;
            case 11:
                t = t-1;
                s[t] = s[t] >= s[t+1];
                break;
            case 12:
                t = t-1;
                s[t] = s[t] > s[t+1];
                break;
            case 13:
                t = t-1;
                s[t] = s[t] <= s[t+1];
                break;
            case 14:
                t = t-1;
                s[t+1] = s[t] == s[t+1];
                break;
            }
        }
        else if(strcmp(i.f, "red") == 0){
           float tempf;
           int tempi;
           char tempc;
           if(i.l == INT){
               cin >> tempi;
               maintable.element[(int)i.a].value = tempi;
           }
           else if(i.l == CHAR){
               cin >> tempc;
               maintable.element[(int)i.a].value = tempc;
           }
           else if(i.l == FLOAT){
               cin >> tempf;
               maintable.element[(int)i.a].value = tempf;
           }
        }
        else if(strcmp(i.f, "wrt") == 0){
           if(i.l == 0){//string
                cout << str.s[(int)i.a].str;
           }
           else{//expression
                if(i.a == 0){
                    cout << s[t];
                }
                else{
                    cout << (char)s[t];
                }
                t--;
           }
        }
        else if(strcmp(i.f, "cal") == 0){
            op[index++] = p;
            p = (int)i.a;
            int m = 0;
            if(i.l > 0){
                table.num[table.index].address = (int)i.a;
                table.num[table.index].para = i.l;
                while(maintable.element[searchst(code[(int)i.a - 1].f, 1, 0) + m + 1].kind != FUNCTION){
                    table.num[table.index].tempnum[m] = maintable.element[searchst(code[(int)i.a - 1].f, 1, 0) + m + 1].value;
                    m++;
                }
            }
            else{
                table.num[table.index].address = (int)i.a;
                table.num[table.index].para = i.l;
            }
            table.index++;
            m = 0;
            int n = i.l-1;
            while(m < i.l){
                if(maintable.element[searchst(code[(int)i.a - 1].f, 1, 0) + m + 1].datakind == FLOAT)
                    maintable.element[searchst(code[(int)i.a - 1].f, 1, 0) + m + 1].value = s[t-n];
                else if(maintable.element[searchst(code[(int)i.a - 1].f, 1, 0) + m + 1].datakind == INT)
                    maintable.element[searchst(code[(int)i.a - 1].f, 1, 0) + m + 1].value = (int)s[t-n];
                else
                    maintable.element[searchst(code[(int)i.a - 1].f, 1, 0) + m + 1].value = (char)s[t-n];
                m++;
                n--;
            }
            t -= i.l;
        }
        else if(strcmp(i.f, "END") == 0){
            return;
        }
    }
}
