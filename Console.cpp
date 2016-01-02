#include"Console.h"
#include<stdio.h>
#pragma warning(disable:4996)
HANDLE ConsoleHandle;
void ConWrite(char *InputText)
{
	int i=0;
	char *End="\0";
	while(InputText[i]!=*End)
	{
		i++;
	}
	WriteConsole(ConsoleHandle,InputText,i,NULL,NULL);
}
void ConWrite(unsigned int *InputNum)
{
	freopen("conout$","w",stdout);
	printf("%d",*InputNum);
}
void ConRead(char *OutputText,unsigned short Num)
{
	LPDWORD i=(LPDWORD)malloc(8);
	ReadConsole(GetStdHandle(STD_INPUT_HANDLE),OutputText,Num,i,NULL);
}