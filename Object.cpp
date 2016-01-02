#include "DataDefinition.h"

//正方体的八个点在空间中的坐标

//十二个三角形的法向量
_3DData PlanNorVect[12];

void GenA();
void GenB();
int num[4]={0,8,14,48};
unsigned short int IndexOfObj[6]={0,1,1,2,2,2};
unsigned short int IndexOfLv[3]={0,2,3};
unsigned short int VertexInLv[7]={3,3,4,8,8,8,8};
unsigned short int NumOfLv[3]={2,1,4};
float vertex[48][3]={
					32.0f,32.0f,0.5f,
					32.0f,-32.0f,0.5f,
					-32.0f,32.0f,0.5f,
					32.0f,32.0f,-0.5f,
					-32.0f,-32.0f,0.5f,
					-32.0f,32.0f,-0.5f,
					32.0f,-32.0f,-0.5f,
					-32.0f,-32.0f,-0.5f,
						
					0.0f,0.0f,5.0f,
					5.0f,5.0f,0.0f,
					-5.0f,5.0f,0.0f,
					-5.0f,-5.0f,0.0f,
					5.0f,-5.0f,0.0f,
					0.0f,0.0f,0.0f,

					0.0f,0.0f,10.0f,
					//
					8.0f,0.0f,6.0f,
					5.656f,5.656f,6.0f,
					0.0f,8.0f,6.0f,
					-5.656f,5.656f,6.0f,
					-8.0f,0.0f,6.0f,
					-5.656f,-5.656f,6.0f,
					0.0f,-8.0f,6.0f,
					5.656f,-5.656f,6.0f,
					//
					9.797f,0.0f,2.0f,
					6.928f,6.928f,2.0f,
					0.0f,9.797f,2.0f,
					-6.928f,6.928f,2.0f,
					-9.797f,0.0f,2.0f,
					-6.928f,-6.928f,2.0f,
					0.0f,-9.797f,2.0f,
					6.928f,-6.928f,2.0f,
					//
					9.797f,0.0f,-2.0f,
					6.928f,6.928f,-2.0f,
					0.0f,9.797f,-2.0f,
					-6.928f,6.928f,-2.0f,
					-9.797f,0.0f,-2.0f,
					-6.928f,-6.928f,-2.0f,
					0.0f,-9.797f,-2.0f,
					6.928f,-6.928f,-2.0f,
					//
					8.0f,0.0f,-6.0f,
					5.656f,5.656f,-6.0f,
					0.0f,8.0f,-6.0f,
					-5.656f,5.656f,-6.0f,
					-8.0f,0.0f,-6.0f,
					-5.656f,-5.656f,-6.0f,
					0.0f,-8.0f,-6.0f,
					5.656f,-5.656f,-6.0f,
					//
					0.0f,0.0f,-10.0f,
					};

float NorVect[84][3]={
	0,0,1,
	0,1,0,
	1,0,0,
	0,0,1,
	0,1,0,
	1,0,0,
	-1,0,0,
	0,0,-1,
	0,-1,0,
	-1,0,0,
	0,0,-1,
	0,-1,0,

	0,1,1,
	-1,0,1,
	0,-1,1,
	1,0,1,
	0,0,-1,
	0,0,-1,
	0,0,-1,
	0,0,-1,

	22.6240005, 9.37600708, 45.2480011,
	9.37599945, 22.6239929, 45.2479858,
	-9.37599945, 22.6239929, 45.2479858,
	-22.6240005, 9.37600708, 45.2480011,
	-22.6240005, -9.37600708, 45.2480011,
	-9.37599945, -22.6239929, 45.2479858,
	9.37599945, -22.6239929, 45.2479858,
	22.6240005, -9.37600708, 45.2480011,
	22.6240005, 9.37600708, 10.1638374,
	9.37599945, 22.6239929, 10.1760044,
	-9.37599945, 22.6239929, 10.1638288,
	-22.6240005, 9.37600708, 10.1760197,
	-22.6240005, -9.37600708, 10.1638374,
	-9.37599945, -22.6239929, 10.1760044,
	9.37599945, -22.6239929, 10.1638288,
	22.6240005, -9.37600708, 10.1760197,
	27.7119999, 11.4759979, 12.4618034,
	11.4759998, 27.7120056, 12.4496183,
	-11.4759998, 27.7120056, 12.4617939,
	-27.7119999, 11.4759979, 12.4496222,
	-27.7119999, -11.4759979, 12.4618034,
	-11.4759998, -27.7120056, 12.4496183,
	11.4759998, -27.7120056, 12.4617939,
	27.7119999, -11.4759979, 12.4496222,
	27.7119999, 11.4759979, 0.000000000,
	11.4759998, 27.7120056, 0.000000000,
	-11.4759998, 27.7120056, 0.000000000,
	-27.7119999, 11.4759979, 0.000000000,
	-27.7119999, -11.4759979, -0.000000000,
	-11.4759998, -27.7120056, -0.000000000,
	11.4759998, -27.7120056, 0.000000000,
	27.7119999, -11.4759979, 0.000000000,
	27.7119999, 11.4759979, 0.000000000,
	11.4759998, 27.7120056, 0.000000000,
	-11.4759998, 27.7120056, 0.000000000,
	-27.7119999, 11.4759979, 0.000000000,
	-27.7119999, -11.4759979, 0.000000000,
	-11.4759998, -27.7120056, 0.000000000,
	11.4759998, -27.7120056, 0.000000000,
	27.7119999, -11.4759979, 0.000000000,
	27.7119999, 11.4759979, -12.4496222,
	11.4759998, 27.7120056, -12.4617939,
	-11.4759998, 27.7120056, -12.4496183,
	-27.7119999, 11.4759979, -12.4618053,
	-27.7119999, -11.4759979, -12.4496222,
	-11.4759998, -27.7120056, -12.4617939,
	11.4759998, -27.7120056, -12.4496183,
	27.7119999, -11.4759979, -12.4618053,
	22.6240005, 9.37600708, -10.1760197,
	9.37599945, 22.6239929, -10.1638288,
	-9.37599945, 22.6239929, -10.1760044,
	-22.6240005, 9.37600708, -10.1638365,
	-22.6240005, -9.37600708, -10.1760197,
	-9.37599945, -22.6239929, -10.1638288,
	9.37599945, -22.6239929, -10.1760044,
	22.6240005, -9.37600708, -10.1638365,
	-22.6240005, -9.37600708, 45.2480011,
	-9.37599945, -22.6239929, 45.2479858,
	9.37599945, -22.6239929, 45.2479858,
	22.6240005, -9.37600708, 45.2480011,
	22.6240005, 9.37600708, 45.2480011,
	9.37599945, 22.6239929, 45.2479858,
	-9.37599945, 22.6239929, 45.2479858,
	-22.6240005, 9.37600708, 45.2480011
};

float AllVert[122][3];
unsigned int AllVertIndex[7]={0,8,14,20,54,88,122};
unsigned short NorVectIdx[3]={0,12,20};
float trans[6][3]={
				0.0f,0.0f,-0.5f,
				-32.0f,-32.0f,0.0f,
				-16.0f,16.0f,32.0f,
				40.0f,0.0f,0.0f,
				40.0f,-25.0f,0.0f,
				40.0f,-50.0f,0.0f,
				};
unsigned int DeltaIndex[220][4];

void LoadObject()
{
	unsigned short int SortOfObj=3;
	unsigned short int NumberOfObj=6;
	
	
	
	
	unsigned short int LinkInvertex[33]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

	GenA();
	GenB();
}

void GenA()
{
	int j=0;
	for(int k=0;k<=5;k++)
	{
		for(int n=num[IndexOfObj[k]];n<num[IndexOfObj[k]+1];n++)
		{
			AllVert[j][0]=vertex[n][0]+trans[k][0];
			AllVert[j][1]=vertex[n][1]+trans[k][1];
			AllVert[j][2]=vertex[n][2]+trans[k][2];
			j++;
		}
	}
}

void GenB()
{
	unsigned int NumberOfDeltaInObj[3]={12,8,8+16+16+16+8};
	unsigned int NumberOfDelta=12+8*2+NumberOfDeltaInObj[2]*3;
	
	unsigned int j=0;
	for(int k=0;k<6;k++)//Which object
	{
		unsigned int d=0;
		for(int i=1;i<=NumOfLv[IndexOfObj[k]];i++)//Which level
		{
			unsigned int PassLvVertexCur=0;
			unsigned int PassLvVertexPre=0;
			unsigned int PassLvVertexPst=0;
			for(int d=0;d<i-1;d++)
			{
				PassLvVertexPre=PassLvVertexCur;//count how many vertexs operated before the level before this level
				PassLvVertexCur=PassLvVertexCur+VertexInLv[IndexOfLv[IndexOfObj[k]]+d];//count how many vertexs operated before this level
				PassLvVertexPst=PassLvVertexCur+VertexInLv[IndexOfLv[IndexOfObj[k]]+d+1];//count how many vertexs oprated including current level
			}
			//pere construction
			if(i==1)//if it is the beginning of a object
			{
				PassLvVertexPst=VertexInLv[IndexOfLv[IndexOfObj[k]]];
				for(int m=1;m<=VertexInLv[i+IndexOfLv[IndexOfObj[k]]-1];m++)//Which vertex in level
				{
					DeltaIndex[j][0]=AllVertIndex[k];
					DeltaIndex[j][1]=AllVertIndex[k]+m;
					if(m==VertexInLv[i+IndexOfLv[IndexOfObj[k]]-1])//if the circuit closed
					{
						DeltaIndex[j][2]=AllVertIndex[k]+1;
					}
					else
					{
						DeltaIndex[j][2]=AllVertIndex[k]+m+1;
					}
					DeltaIndex[j][3]=d+NorVectIdx[IndexOfObj[k]];
					d++;
					j++;
				}
			}
			else
			{
				for(int m=1;m<=VertexInLv[i+IndexOfLv[IndexOfObj[k]]-1];m++)//Which vertex in level
				{
					DeltaIndex[j][0]=AllVertIndex[k]+PassLvVertexCur+m;
					if(m==VertexInLv[i+IndexOfLv[IndexOfObj[k]]-1])//if the circuit closed
					{
						DeltaIndex[j][1]=AllVertIndex[k]+PassLvVertexCur+1;
						DeltaIndex[j][2]=AllVertIndex[k]+PassLvVertexPre+1;
					}
					else
					{
						DeltaIndex[j][1]=AllVertIndex[k]+PassLvVertexCur+m+1;
						DeltaIndex[j][2]=AllVertIndex[k]+PassLvVertexPre+m+1;
					}
					DeltaIndex[j][3]=d+NorVectIdx[IndexOfObj[k]];
					d++;
					j++;
				}
			}
			//post construction
			if(i==NumOfLv[IndexOfObj[k]])//if it is the ending of a object
			{
				for(int m=1;m<=VertexInLv[i+IndexOfLv[IndexOfObj[k]]-1];m++)//Which vertex in level
				{
					DeltaIndex[j][0]=AllVertIndex[k+1]-1;
					DeltaIndex[j][1]=AllVertIndex[k]+PassLvVertexCur+m;
					if(m==VertexInLv[i+IndexOfLv[IndexOfObj[k]]-1])
					{
						DeltaIndex[j][2]=AllVertIndex[k]+PassLvVertexCur+1;
					}
					else
					{
						DeltaIndex[j][2]=AllVertIndex[k]+PassLvVertexCur+m+1;
					}
					DeltaIndex[j][3]=d+NorVectIdx[IndexOfObj[k]];
					d++;
					j++;
				}
			}
			else
			{
				for(int m=1;m<=VertexInLv[i+IndexOfLv[IndexOfObj[k]]-1];m++)//Which vertex in level
				{
					DeltaIndex[j][0]=AllVertIndex[k]+PassLvVertexCur+m;
					DeltaIndex[j][1]=AllVertIndex[k]+PassLvVertexPst+m;
					if(m==VertexInLv[i+IndexOfLv[IndexOfObj[k]]-1])
					{
						DeltaIndex[j][2]=AllVertIndex[k]+PassLvVertexCur+1;
					}
					else
					{
						DeltaIndex[j][2]=AllVertIndex[k]+PassLvVertexCur+m+1;
					}
					DeltaIndex[j][3]=d+NorVectIdx[IndexOfObj[k]];
					d++;
					j++;
				}
			}
		}
	}
}