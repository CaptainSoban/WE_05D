#ifndef _1174_DataDefinition
#define _1174_DataDefinition
//------------------------------
//���ڶ�ά���ݵĹ���ʹ���
//For managing and delivering two-dimensional datum
typedef struct _2DData_
{
public:
	float x,y;
}_2DData;

//������ά���ݵĹ���ʹ���
//For managing and delivering three-dimensional datum
typedef struct _3DData_
{
public:
	float x,y,z;
}_3DData;

//�����������о���Ĺ���ʹ���
//For managing and delivering 3*3 matrix
typedef struct matrix33_
{
public:
	float line1[3],line2[3],line3[3];
}matrix33;
//------------------------------
#endif