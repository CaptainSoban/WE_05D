#ifndef Warp_Object
#define Warp_Object
#include "DataDefinition.h"
//------------------------------
//正方体的八个点在空间中的坐标
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

//十二个三角形的法向量
extern _3DData PlanNorVect[12];

void LoadObject();
//------------------------------
#endif