#ifndef Warp_Object
#define Warp_Object
#include "DataDefinition.h"
//------------------------------
//������İ˸����ڿռ��е�����
extern float AllVert[120][3];
extern float NorVect[84][3];
extern unsigned int DeltaIndex[220][4];

extern unsigned short int SortOfObj;
extern unsigned short int NumberOfObj;
extern float trans[6][3];
extern unsigned short int IndexOfObj[6];
extern unsigned short int NumOfLv[3];
extern unsigned short int VertexInLv[8];
extern unsigned short int LinkInvertex[33];

//ʮ���������εķ�����
extern _3DData PlanNorVect[12];

void LoadObject();
//------------------------------
#endif