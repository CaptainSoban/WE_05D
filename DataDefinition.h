#ifndef _1174_DataDefinition
#define _1174_DataDefinition
//------------------------------
//用于二维数据的管理和传递
//For managing and delivering two-dimensional datum
typedef struct _2DData_
{
public:
	float x,y;
}_2DData;

//用于三维数据的管理和传递
//For managing and delivering three-dimensional datum
typedef struct _3DData_
{
public:
	float x,y,z;
}_3DData;

//用于三行三列矩阵的管理和传递
//For managing and delivering 3*3 matrix
typedef struct matrix33_
{
public:
	float line1[3],line2[3],line3[3];
}matrix33;
//------------------------------
#endif