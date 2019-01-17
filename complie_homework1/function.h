#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED

extern int getsym();
extern void program();
extern void condef(int tempkind);
extern void constate();
extern void vardef();
extern void varstate();
extern void parametertable();
extern void valueofpara(char* names);
extern void complexsentence();
extern void sentencelist();
extern void sentence();
extern void scanfsentence();
extern void printfsentence();
extern void returnsentence();
extern void ifsentence();
extern void condition();
extern void loopsentence();
extern void switchsentence();
extern void expression();
extern void term();
extern void factor();
extern void error(int n);
extern void insertproc(int paranum);
extern void pushtable(char* name, int kind, float value, int paranum, int ischar, int isVec);
extern int searchst(char* name, int flag, int needret);
extern void gen(char* x, int y, float z);
extern void pushnumtable(int address, int kind, int paranum);
extern int searchnum(int address);
extern int searchfunction(char* names);
extern void interpret();

#endif // FUNCTION_H_INCLUDED
