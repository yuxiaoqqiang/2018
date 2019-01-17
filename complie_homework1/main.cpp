#include "data.h"
#include "function.h"
#include "global.h"
int main(){
    string input, output;
    cout << "Please input input_file address:";
    cin >> input;
//    cout << "Please input output_file address:";
//    cin >> output;
    foutput.open("d:\\2.txt");
    src = fopen(input.c_str(),"r");
    program();
    if(errornum != 0){
        cout << "OVER" << endl;
        return 0;
    }
    int i = 0;
    while(i < cx){
        foutput << i << ' ' << code[i].f << ' ' << code[i].l << ' ' << code[i].a << endl;
        i++;
    }
    foutput.close();
    fclose(src);
    interpret();
    cout << "END" << endl;
    return 0;
}
