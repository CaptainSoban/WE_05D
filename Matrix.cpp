//3��3����ά����
//3*3 3D Matrix
#include <math.h>
#include "DataDefinition.h"
//1��3�о�����3��3�о������
//1*3 matrix multiple 3*3 matrix
_3DData Mat13MultMat33(_3DData mat1,matrix33 mat2)
{
	_3DData result;
	result.x=mat1.x*mat2.line1[0]+mat1.y*mat2.line2[0]+mat1.z*mat2.line3[0];
	result.y=mat1.x*mat2.line1[1]+mat1.y*mat2.line2[1]+mat1.z*mat2.line3[1];
	result.z=mat1.x*mat2.line1[2]+mat1.y*mat2.line2[2]+mat1.z*mat2.line3[2];
	return result;
}

//��X������Ϊ�����ת����ʱ��Ϊ������
//Rotate around X-axis. Clockwise is positive direction.
_3DData RotArouX(_3DData InpCord,float RotAng)
{
	matrix33 ForRot;
	ForRot.line1[0]=1;
	ForRot.line1[1]=0;
	ForRot.line1[2]=0;
	ForRot.line2[0]=0;
	ForRot.line2[1]=cos(RotAng);
	ForRot.line2[2]=-sin(RotAng);
	ForRot.line3[0]=0;
	ForRot.line3[1]=sin(RotAng);
	ForRot.line3[2]=cos(RotAng);
	return Mat13MultMat33(InpCord,ForRot);
}

//��Y������Ϊ�����ת����ʱ��Ϊ������
//Rotate around Y-axis. Clockwise is positive direction.
_3DData RotArouY(_3DData InpCord,float RotAng)
{
	matrix33 ForRot;
	ForRot.line1[0]=cos(RotAng);
	ForRot.line1[1]=0;
	ForRot.line1[2]=sin(RotAng);
	ForRot.line2[0]=0;
	ForRot.line2[1]=1;
	ForRot.line2[2]=0;
	ForRot.line3[0]=-sin(RotAng);
	ForRot.line3[1]=0;
	ForRot.line3[2]=cos(RotAng);
	return Mat13MultMat33(InpCord,ForRot);
}

//��Z������Ϊ�����ת����ʱ��Ϊ������
//Rotate around Z-axis. Clockwise is positive direction.
_3DData RotArouZ(_3DData InpCord,float RotAng)
{
	matrix33 ForRot;
	ForRot.line1[0]=cos(RotAng);
	ForRot.line1[1]=-sin(RotAng);
	ForRot.line1[2]=0;
	ForRot.line2[0]=sin(RotAng);
	ForRot.line2[1]=cos(RotAng);
	ForRot.line2[2]=0;
	ForRot.line3[0]=0;
	ForRot.line3[1]=0;
	ForRot.line3[2]=1;
	return Mat13MultMat33(InpCord,ForRot);
}