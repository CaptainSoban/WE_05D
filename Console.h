#ifndef _1174_Console
#define _1174_Console
#include<Windows.h>
//------------------------------
void ConWrite(char *InputText);
void ConWrite(unsigned int *InputNum);
void ConRead(char *OutputText,unsigned short Num);
extern HANDLE ConsoleHandle;
//------------------------------
#endif