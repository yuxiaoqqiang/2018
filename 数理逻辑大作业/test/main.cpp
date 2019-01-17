#include <iostream>
#include "data.h"

void getch(){//backupline是用来保存现场的，目的是为了出错时方便处理
    int i = 0;
    if(ifok == 0){
        if(cnum == llen && ~line[llen]){//判断是否是一行的开头或结尾，或是输入结束。
            if(cnum == 0){
                cin.get(ch);

                while(ch == ' ' || ch == '\n' || ch == '\t'){
                    if(ch == '\n') {
                        lnum++;
                    }
                    if(ch != '\n')
                        backupline[i++] = ch;//原样保存一整行输入
                    //ch = fgetc(src);
                    cin.get(ch);
                }
                for(llen = 0; ch != '\n' && ch != EOF; llen++){
                    line[llen] = ch;//保留一个单词
                    backupline[i++] = ch;
                    //ch = fgetc(src);
                    cin.get(ch);
                    //cout << ch;
                }
                if(ch == EOF)
                    line[llen] = EOF;
                else
                    line[llen] = '\n';
                backupline[i] = '\0';
                cnum = 0;
                ch = '\n';
                lnum++;//行数+1
            }
            else{
                over = 1;
            }
        }
        else{
            ch = line[cnum++];//从line中取回字符
        }
    }
    else{
        ch = backupline[calnum++];
        if(calnum == cnum+1){
            over = 0;
        }
    }
}

int getsym(){
    id = "";
    while(isspace(ch) && ch != EOF){//去除空格，tab,回车,换行符
        getch();
    }
    if(ch == '\n'){
        symid = -1;
        return -1;
    }
    if(isalpha(ch)){//字母或_
        while(isalpha(ch) || isdigit(ch)){
            id += ch;
            getch();
        }
        if(ifdefine == 1){
            sym = "FUNC";
        }
        else{
            if(ch == '('){
                sym = "FUNC";
            }
            else{
                sym = "ID";
            }
        }
    }
    else if(isdigit(ch)){//0~9
        sym = "NUM";
        //symid = INTCON;
        id += ch;
        getch();
    }
    else if(ch == '\241'){
        id += ch;
        getch();
        id += ch;
        if(ch == '\304'){
            sym = "AND";
        }
        else if(ch == '\305'){
            sym = "OR";
        }
        else  if(ch == '\372'){
            sym = "PU";
        }
        else{
            return 0;
        }
        //symid = AND;
        getch();
    }
    else if(ch == '\250'){
        id += ch;
        getch();
        id += ch;
        sym = "XOR";
        getch();
    }
    else if(ch == '?'){
        id += ch;
        sym = "DPU";
        //symid = DPU;
        getch();
    }
    else if(ch == '~'){
        id += ch;
        sym = "NOT";
        //symid = NOT;
        getch();
    }
    else if(ch == ','){
        id += ch;
        sym = "DOU";
        getch();
    }
    else{
        if(ch == '('){
            sym = "LPARENT";
            //symid = LPARENT;
        }
        else if(ch == ')'){
            sym = "RPARENT";
            //symid = RPARENT;
        }
        else if(ch == '#'){
            ifdefine = 1;
            sym = "FNUM";
        }
        id += ch;
        getch();
    }
    return 0;
}

int andb(int i, int j){
    if(i == 1 && j == 1)
        return 1;
    else
        return 0;
}

int orb(int i, int j){
    if(i == 1 || j == 1)
        return 1;
    else
        return 0;
}

int xorb(int i, int j){
    if((i == 1 && j == 0) || (i == 0 && j == 1))
        return 1;
    else
        return 0;
}

int pu(int i, int j){
    if(i == 1 && j == 0)
        return 0;
    else
        return 1;
}

int dpu(int i, int j){
    if(i == j)
        return 1;
    else
        return 0;
}

void change(int k, int variable){
    int i,j;
    int index;
    for (index = 0; index< idnum; index++){
        i=variable%2;  //取2的余数
        j=variable/2;  //取被2整除的数
        variable=j;  //将得到的商赋给变量variable,用来下次求%，获得下一个数
        idv[k][index] = i; //将余数存放在数组中
    }

}

void program(){
    int tempi;
    while(over == 0){
        getsym();
        if(sym.compare("ID") == 0){
            if(idnum == 0){
                ids[idnum] = id;
                idv[0][idnum] = idnum;
                idnum++;
                //cout << ids[idnum - 1] << endl;
            }
            else{
                //cout << id << endl;
                for(tempi = 0; tempi < idnum; tempi++){
                    if(ids[tempi].compare(id) != 0){
                        ;
                    }
                    else{
                        break;
                    }
                }
                if(tempi == idnum){
                    ids[idnum] = id;
                    idv[0][idnum] = idnum;
                    idnum++;
                    if(idnum == 10){
                        cout << "Over 10 !!" << endl;
                    }
                }
            }
        }
        else if(sym.compare("FUNC") == 0){
            if(ifdefine == 1){
                string tmp;
                int i, j;
                tmp = id;
                getsym();
                if(sym.compare("NUM") == 0){
                    i = atoi(id.c_str());
                    if (i == 0){
                        for(j = 0; j< f0num; j++){
                            if(f0[f0num].compare(tmp) != 0){
                                ;
                            }
                            else{
                                break;
                            }
                        }
                        if(j == f0num){
                            f0[f0num] = tmp;
                            if(f0num == 0){
                                getsym();
                                if(sym.compare("NUM") == 0){
                                    f01 = atoi(id.c_str());
                                }
                            }
                            else if(f0num == 1){
                                getsym();
                                if(sym.compare("NUM") == 0){
                                    f02 = atoi(id.c_str());
                                }
                            }
                            else if(f0num == 2){
                                getsym();
                                if(sym.compare("NUM") == 0){
                                    f03 = atoi(id.c_str());
                                }
                            }
                            f0num++;
                        }
                        else{
                            cout << "repeat define" << endl;
                        }
                    }
                    else if(i == 1){
                        for(j = 0; j< f1num; j++){
                            if(f1[f1num].compare(tmp) != 0){
                                ;
                            }
                            else{
                                break;
                            }
                        }
                        if(j == f1num){
                            f1[f1num] = tmp;
                            if(f1num == 0){
                                for(int m = 0; m < 2; m++){
                                    getsym();
                                    if(sym.compare("NUM") == 0){
                                        f11[m] = atoi(id.c_str());
                                    }
                                }
                            }
                            else if(f1num == 1){
                                for(int m = 0; m < 2; m++){
                                    getsym();
                                    if(sym.compare("NUM") == 0){
                                        f12[m] = atoi(id.c_str());
                                    }
                                }
                            }
                            else if(f1num == 2){
                                for(int m = 0; m < 2; m++){
                                    getsym();
                                    if(sym.compare("NUM") == 0){
                                        f13[m] = atoi(id.c_str());
                                    }
                                }
                            }
                            f1num++;
                        }
                        else{
                            cout << "repeat define" << endl;
                        }
                    }
                    else if(i == 2){
                        for(j = 0; j < f2num; j++){
                            if(f2[f2num].compare(tmp) != 0){
                                ;
                            }
                            else{
                                break;
                            }
                        }
                        if(j == f2num){
                            f2[f2num] = tmp;
                            if(f2num == 0){
                                for(int m = 0; m < 2; m++){
                                    for(int n = 0; n < 2; n++){
                                        getsym();
                                        if(sym.compare("NUM") == 0){
                                            f21[m][n] = atoi(id.c_str());
                                        }
                                    }
                                }
                            }
                            else if(f2num == 1){
                                for(int m = 0; m < 2; m++){
                                    for(int n = 0; n < 2; n++){
                                        getsym();
                                        if(sym.compare("NUM") == 0){
                                            f22[m][n] = atoi(id.c_str());
                                        }
                                    }
                                }
                            }
                            else if(f2num == 2){
                                for(int m = 0; m < 2; m++){
                                    for(int n = 0; n < 2; n++){
                                        getsym();
                                        if(sym.compare("NUM") == 0){
                                            f23[m][n] = atoi(id.c_str());
                                        }
                                    }
                                }
                            }
                            f2num++;
                        }
                        else{
                            cout << "repeat define" << endl;
                        }
                    }
                    else if(i == 3){
                        for(j = 0; j< f3num; j++){
                            if(f3[f3num].compare(tmp) != 0){
                                ;
                            }
                            else{
                                break;
                            }
                        }
                        if(j == f3num){
                            f3[f3num] = tmp;
                            if(f3num == 0){
                                for(int m = 0; m < 2; m++){
                                    for(int n = 0; n < 2; n++){
                                        for(int k = 0; k < 2; k++){
                                            getsym();
                                            if(sym.compare("NUM") == 0){
                                                f31[m][n][k] = atoi(id.c_str());
                                            }
                                        }
                                    }
                                }
                            }
                            if(f3num == 1){
                                for(int m = 0; m < 2; m++){
                                    for(int n = 0; n < 2; n++){
                                        for(int k = 0; k < 2; k++){
                                            getsym();
                                            if(sym.compare("NUM") == 0){
                                                f32[m][n][k] = atoi(id.c_str());
                                            }
                                        }
                                    }
                                }
                            }
                            else if(f3num == 2){
                                for(int m = 0; m < 2; m++){
                                    for(int n = 0; n < 2; n++){
                                        for(int k = 0; k < 2; k++){
                                            getsym();
                                            if(sym.compare("NUM") == 0){
                                                f33[m][n][k] = atoi(id.c_str());
                                            }
                                        }
                                    }
                                }
                            }
                            f3num++;
                        }
                        else{
                            cout << "repeat define" << endl;
                        }
                    }
                }
            }
            else{

            }
        }
    }
    for(int i = 0; i < pow(2, idnum); i++){
        change(i+1, i);
    }
//    for(int i = 0; i <= pow(2, idnum); i++){
//        for(int j = 0; j < idnum; j++){
//            cout << idv[i][j] << " ";
//        }
//        cout << endl;
//    }
        /*else if(strcmp(sym, "FUNC") == 0){
            getsym();
        }*/
        //cout << sym <<endl;

}

string getstring (int n){

std::stringstream newstr;
newstr<<n;
return newstr.str();

}

int profunc(int i){
    int ln = 0;
    int n = 0;
    int m[3];
    int k = 0;
    int j = 0;
    for(j = 0; j < 3; j++){
        if(f0[j].compare(id) == 0){
            n = 0;
            break;
        }
        else if(f1[j].compare(id) == 0){
            n = 1;
            break;
        }
        else if(f2[j].compare(id) == 0){
            n = 2;
            break;
        }
        else if(f3[j].compare(id) == 0){
            n = 3;
            break;
        }
    }
    while(true){
        getsym();
        if(sym.compare("LPARENT") == 0){
            ln++;
        }
        else if(sym.compare("RPARENT") == 0){
            ln--;
        }
        else if(sym.compare("ID") == 0){
            for(int j = 0; j < idnum; j++){
                if(ids[j].compare(id) == 0){
                    m[k++] = idv[i+1][j];
                }
            }
        }
        else if(sym.compare("NUM") == 0){
            m[k++] = atoi(id.c_str());
        }
        else if(sym.compare("FUNC") == 0){
            m[k++] = profunc(i);
        }
        else if(sym.compare("DOU") == 0){
            ;
        }
        if(ln == 0 && k == n){
            int res = 0;
            if(j == 0){
                if(n == 0){
                    res = f01;
                }
                else if(n == 1){
                    res = f11[m[0]];
                }
                else if(n == 2){
                    res = f21[m[0]][m[1]];
                }
                else if(n == 3){
                    res = f31[m[0]][m[1]][m[2]];
                }
            }
            else if(j == 1){
                if(n == 0){
                    res = f02;
                }
                else if(n == 1){
                    res = f12[m[0]];
                }
                else if(n == 2){
                    res = f22[m[0]][m[1]];
                }
                else if(n == 3){
                    res = f32[m[0]][m[1]][m[2]];
                }
            }
            else if(j == 2){
                if(n == 0){
                    res = f03;
                }
                else if(n == 1){
                    res = f13[m[0]];
                }
                else if(n == 2){
                    res = f23[m[0]][m[1]];
                }
                else if(n == 3){
                    res = f33[m[0]][m[1]][m[2]];
                }
            }
            return res;
        }
    }
}

void calculate(){
    int tmp = 0;
    int tmpresult = 0;
    int result = 0;
    int ifnot = 0;
    ch = ' ';
    for(int i = 0, snum = 0; i < pow(2, idnum); i++, snum = 0){
        ifdefine = 0;
        tmpresult = 0;
        while(over == 1){
            getsym();
            if(sym.compare("ID") == 0){
                for(int j = 0; j < idnum; j++){
                    if(ids[j].compare(id) == 0){
                        if(snum > 0){
                            if(cal[snum-1].compare("~") == 0){
                                if(idv[i+1][j] == 1){
                                    run[tmpresult++] = 0;
                                }
                                else{
                                    run[tmpresult++] = 1;
                                }
                                snum--;
                            }
                            else{
                               run[tmpresult++] = idv[i+1][j];
                            }
                        }
                        else{
                           run[tmpresult++] = idv[i+1][j];
                        }
                    }
                }
            }
            else if(sym.compare("AND") == 0){
                cal[snum++] = "&";
            }
            else if(sym.compare("OR") == 0){
                cal[snum++] = "|";
            }
            else if(sym.compare("PU") == 0){
                cal[snum++] = ">";
            }
            else if(sym.compare("XOR") == 0){
                cal[snum++] = "^";
            }
            else if(sym.compare("DPU") == 0){
                cal[snum++] = "<";
            }
            else if(sym.compare("FUNC") == 0){
                tmp = profunc(i);
                if(snum > 0){
                    if(cal[snum-1].compare("~") == 0){
                        if(tmp == 1){
                            run[tmpresult++] = 0;
                        }
                        else{
                            run[tmpresult++] = 1;
                        }
                        snum--;
                    }
                    else{
                       run[tmpresult++] = tmp;
                    }
                }
                else{
                   run[tmpresult++] = tmp;
                }
            }
            else if(sym.compare("NUM") == 0){
                run[tmpresult++] = atoi(id.c_str());
            }
            else if(sym.compare("NOT") == 0){
                cal[snum++] = id;
                ifnot = 1;
            }
            else if(sym.compare("FNUM") == 0){
                break;
            }
            else if(sym.compare("LPARENT") == 0){
                cal[snum++] = id;
            }
            else if(sym.compare("RPARENT") == 0){
                if(ifnot == 1){
                    int checknot = snum - 1;
                    while(cal[checknot].compare("(") != 0){
                        checknot--;
                    }
                    if(cal[--checknot].compare("~") == 0){
                        for(int now = checknot; now < snum -1; now++){
                            cal[now] = cal[now+1];
                        }
                        snum--;
                    }
                }
                int tt = snum;
//                for (int tm = 0; tm < snum; tm++)
//                    cout << cal[tm] << " ";
                while(cal[--tt].compare("(") != 0){
                    if(cal[tt].compare("&") == 0){
                        run[tt-1] = andb(run[tt-1], run[tt]);
                        result = tt -1;
                        for(int k = tt; k < tmpresult-1; k++){
                            run[k] = run[k + 1];
                        }
                        tmpresult--;
                        for(int k = tt; k < snum-1; k++){
                            cal[k] = cal[k+1];
                        }
                        snum--;
                    }
                    else if(cal[tt].compare("|") == 0){
                        run[tt-1] = orb(run[tt-1], run[tt]);
                        result = tt -1;
                        for(int k = tt; k < tmpresult-1; k++){
                            run[k] = run[k + 1];
                        }
                        tmpresult--;
                        for(int k = tt; k < snum-1; k++){
                            cal[k] = cal[k+1];
                        }
                        snum--;
                    }
                    else if(cal[tt].compare("^") == 0){
                        run[tt-1] = xorb(run[tt-1], run[tt]);
                        result = tt -1;
                        for(int k = tt; k < tmpresult-1; k++){
                            run[k] = run[k + 1];
                        }
                        tmpresult--;
                        for(int k = tt; k < snum-1; k++){
                            cal[k] = cal[k+1];
                        }
                        snum--;
                    }
                }
                //cout << "snum : " << snum << endl;
                int pp = snum;
                while(cal[--pp].compare("(") != 0){
                    if(cal[pp].compare(">") == 0){
                        run[pp-1] = pu(run[pp-1], run[pp]);
                        result = pp -1;
                        for(int k = pp; k < tmpresult-1; k++){
                            run[k] = run[k + 1];
                        }
                        tmpresult--;
                        for(int k = pp; k < snum-1; k++){
                            cal[k] = cal[k+1];
                        }
                        snum--;
                    }
                }
                int qq = snum;
                while(cal[--qq].compare("(") != 0){
                    if(cal[qq].compare("<") == 0){
                        run[qq-1] = dpu(run[qq-1], run[qq]);
                        result = qq -1;
                        for(int k = qq; k < tmpresult-1; k++){
                            run[k] = run[k + 1];
                        }
                        tmpresult--;
                        for(int k = qq; k < snum-1; k++){
                            cal[k] = cal[k+1];
                        }
                        snum--;
                    }
                }
                snum--;
                if(ifnot == 1){
                    if(run[result] == 1)
                        run[result] = 0;
                    else
                        run[result] = 1;
                    ifnot = 0;
                }
                //cout << snum << endl;
//                if(snum != 0){
//                    if()
//                }
                /*while(cal[--snum].compare("(") != 0){
                    if(cal[snum].compare("&") == 0){
                        run[tmpresult-2] = andb(run[tmpresult-1], run[tmpresult-2]);
                    }
                    else if(cal[snum].compare("|") == 0){
                        run[tmpresult-2] = orb(run[tmpresult-1], run[tmpresult-2]);
                    }
                    else if(cal[snum].compare("^") == 0){
                        run[tmpresult-2] = xorb(run[tmpresult-1], run[tmpresult-2]);
                    }
                    else if(cal[snum].compare(">") == 0){
                        run[tmpresult-2] = pu(run[tmpresult-2], run[tmpresult-1]);
                    }
                    else if(cal[snum].compare("<") == 0){
                        run[tmpresult-2] = dpu(run[tmpresult-1], run[tmpresult-2]);
                    }
                    tmpresult--;
                }
                */
                //cal[snum] = "";
            }
        }
        if(snum != 0){
            int tt = snum;
            while(tt-- != 0){
                if(cal[tt].compare("&") == 0){
                    run[tt] = andb(run[tt+1], run[tt]);
                    for(int k = tt + 1 ; k < tmpresult-1; k++){
                        run[k] = run[k+1];
                    }
                    tmpresult--;
                    for(int k = tt+1; k < snum-1; k++){
                        cal[k] = cal[k+1];
                    }
                    snum--;
                }
                else if(cal[tt].compare("|") == 0){
                    run[tt] = orb(run[tt+1], run[tt]);
                    for(int k = tt+1; k < tmpresult-1; k++){
                        run[k] = run[k + 1];
                    }
                    tmpresult--;
                    for(int k = tt+1; k < snum-1; k++){
                        cal[k] = cal[k+1];
                    }
                    snum--;
                }
                else if(cal[tt].compare("^") == 0){
                    run[tt] = xorb(run[tt+1], run[tt]);
                    for(int k = tt; k < tmpresult-1; k++){
                        run[k] = run[k + 1];
                    }
                    tmpresult--;
                    for(int k = tt+1; k < snum-1; k++){
                        cal[k] = cal[k+1];
                    }
                    snum--;
                }
            }
            int pp = snum;
            while(pp-- != 0){
                if(cal[pp].compare(">") == 0){
                    run[pp] = pu(run[pp], run[pp+1]);
                    for(int k = pp+1; k < tmpresult-1; k++){
                        run[k] = run[k + 1];
                    }
                    tmpresult--;
                    for(int k = pp; k < snum-1; k++){
                        cal[k] = cal[k+1];
                    }
                    snum--;
                }
            }
            int qq = snum;
            while(qq-- != 0){
                if(cal[qq].compare("<") == 0){
                    run[qq] = dpu(run[qq+1], run[qq]);
                    for(int k = qq+1; k < tmpresult-1; k++){
                        run[k] = run[k + 1];
                    }
                    tmpresult--;
                    for(int k = qq; k < snum-1; k++){
                        cal[k] = cal[k+1];
                    }
                    snum--;
                }
            }
//                if(cal[snum].compare("&") == 0){
//                    run[tmpresult-2] = andb(run[tmpresult-1], run[tmpresult-2]);
//                }
//                else if(cal[snum].compare("|") == 0){
//                    run[tmpresult-2] = orb(run[tmpresult-1], run[tmpresult-2]);
//                }
//                else if(cal[snum].compare("^") == 0){
//                    run[tmpresult-2] = xorb(run[tmpresult-1], run[tmpresult-2]);
//                }
//                else if(cal[snum].compare(">") == 0){
//                    run[tmpresult-2] = pu(run[tmpresult-2], run[tmpresult-1]);
//                }
//                else if(cal[snum].compare("<") == 0){
//                    run[tmpresult-2] = dpu(run[tmpresult-1], run[tmpresult-2]);
//                }
//                tmpresult--;
        }
        idv[i+1][idnum] = run[0];
        calnum = 0;
        over = 1;
        ch = ' ';
        for(int cou = 0; cou <= idnum; cou++){
            cout << idv[i+1][cou] << " ";
        }
        cout << endl;
    }
    cout << "---------------------------------------------" << endl;
    int ifalways = 0;
    int total = 0;
    for(int i = 0; i < pow(2, idnum); i++){
        if(idv[i+1][idnum] == 1){
            truenum[total++] = i + 1;
        }
        else{
            ifalways = 1;
        }
    }
    if(ifalways == 0){
        cout << "always true" << endl;
    }
    if(total == 0){
        cout << "always false" << endl;
    }
    else{
        cout << "when value = 1" << endl;
        for(int i = 0; i < total; i++){
            for(int cou = 0; cou <= idnum; cou++){
                cout << idv[truenum[i]][cou] << " ";
            }
            cout << endl;
        }
        cout << "not always true" << endl;
    }
}
void ifcom(){
    int havenot = 0;
    if(ifdefine == 0){
        return;
    }
    else{
        if(f1num != 0){
            if(f1num == 1){
                if(f11[0] == 1 && f11[1] == 0){
                    havenot = 1;
                }
            }
            else if(f1num == 2){
                if((f11[0] == 1 && f11[1] == 0) || (f12[0] == 1 && f12[1] == 0)){
                    havenot = 1;
                }
            }
            else if(f1num == 3){
                if((f11[0] == 1 && f11[1] == 0) || (f12[0] == 1 && f12[1] == 0) || (f13[0] == 1 && f13[1] == 0)){
                    havenot = 1;
                }
            }
        }
        if(f2num != 0){
            if(f2num == 1){
                if(havenot == 0){
                    cout << "not complete" << endl;
                    return;
                }
                else{
                    if((f21[0][0] == 0 && f21[0][1] == 0 && f21[1][0] == 0 && f21[1][1] == 0) ||
                       (f21[0][0] == 1 && f21[0][1] == 1 && f21[1][0] == 1 && f21[1][1] == 1)){
                        cout << "not complete" << endl;
                       }
                    else{
                        cout << "complete" << endl;
                    }
                    return;
                }
            }
            else if(f2num == 2){
                if((f21[0][0] == f22[0][0] && f21[0][1] == f22[0][1] && f21[1][0] == f22[1][0] && f21[1][1] == f22[1][1]) ||
                   (f21[0][0] == 1 && f21[0][1] == 1 && f21[1][0] == 1 && f21[1][1] == 1) ||
                   (f21[0][0] == 0 && f21[0][1] == 0 && f21[1][0] == 0 && f21[1][1] == 0) ||
                   (f22[0][0] == 1 && f22[0][1] == 1 && f22[1][0] == 1 && f22[1][1] == 1) ||
                   (f22[0][0] == 0 && f22[0][1] == 0 && f22[1][0] == 0 && f22[1][1] == 0)){
                    cout << "not complete" << endl;
                   }
                else{
                    cout << "complete" << endl;
                }
                return;
            }
            else if(f2num == 3){
                cout << "complete" << endl;
                return;
            }
        }
        if(f3num != 0){
            cout << "not complete" << endl;
            return;
        }
        if(havenot == 0){
            cout << "not complete" << endl;
        }
        else{
            cout << "complete" << endl;
        }
    }
}
int main()
{
    string input;
    cout << "Please input:" << endl;
    //cin >> input;
    program();
    ifok = 1;
    cout << "value table" << endl;
    calculate();

    ifcom();
    //cout << backupline << endl;
    //change(1024);

    //src = fopen(input.c_str(),"r");
    //getch();
    return 0;
}
