#include "Matrix.h"
#include "Camera.h"
#include <math.h>

//Camera Position
_3DData CamPos;

//Horizontal Angle, Vertical Angle and Inclined Angle.
float HorAng,VerAng,IncAng;

float Sight,WidthPix,HeightPix;

//Camera Normal Vector, Camera Inclined Vector and Camera Aide Vector.
_3DData CamNorVect;
_3DData CamIncVect;
_3DData CamAidVect;
_3DData PixVect[1024][768];

void PixVectIni();

bool CamInitial()
{
	CamPos.x=64;
	CamPos.y=64;
	CamPos.z=64;

	//Horizontal Angle, Vertical Angle and Inclined Angle.
	HorAng=2.3561944901f;		//3*Pi/4
	VerAng=5.6677055995f;		//2*pi-atan(sqrt(2)/2)
	IncAng=0.0f;				//0

	Sight=0.7853981634f;		//Pi/4，镜头对角线视角的一半
	WidthPix=1024;
	HeightPix=768;
	
	ReCam();
	PixVectIni();
	return false;
}

void ReCam()
{
	CamNorVect.x=1;
	CamNorVect.y=0;
	CamNorVect.z=0;

	CamIncVect.x=0;
	CamIncVect.y=0;
	CamIncVect.z=1;

	CamAidVect.x=0;
	CamAidVect.y=1;
	CamAidVect.z=0;

	//镜头的法向量
	CamNorVect=RotArouY(CamNorVect,VerAng);
	CamNorVect=RotArouZ(CamNorVect,HorAng);

	//镜头的次向量（垂直向量）
	CamIncVect=RotArouX(CamIncVect,IncAng);
	CamIncVect=RotArouY(CamIncVect,VerAng);
	CamIncVect=RotArouZ(CamIncVect,HorAng);

	//
	CamAidVect=RotArouX(CamAidVect,IncAng);
	CamAidVect=RotArouY(CamAidVect,VerAng);
	CamAidVect=RotArouZ(CamAidVect,HorAng);


	for(unsigned int a=0;a<1024;a++){
		for(unsigned int b=0;b<768;b++){
			PixVect[a][b].x=CamNorVect.x;
			PixVect[a][b].y=CamNorVect.y;
			PixVect[a][b].z=CamNorVect.z;
			PixVect[a][b]=RotArouX(PixVect[a][b],IncAng);
			PixVect[a][b]=RotArouY(PixVect[a][b],VerAng);
			PixVect[a][b]=RotArouZ(PixVect[a][b],HorAng);
		}
	}
}

void MoveCam(int wParam)
{
	switch(wParam)
	{
	case 0:
		CamPos.x=CamPos.x+CamNorVect.x;
		CamPos.y=CamPos.y+CamNorVect.y;
		CamPos.z=CamPos.z+CamNorVect.z;
		break;
	case 1:
		CamPos.x=CamPos.x-CamNorVect.x;
		CamPos.y=CamPos.y-CamNorVect.y;
		CamPos.z=CamPos.z-CamNorVect.z;
		break;
	case 2:
		CamPos.x=CamPos.x+CamIncVect.x;
		CamPos.y=CamPos.y+CamIncVect.y;
		CamPos.z=CamPos.z+CamIncVect.z;
		break;
	case 3:
		CamPos.x=CamPos.x-CamIncVect.x;
		CamPos.y=CamPos.y-CamIncVect.y;
		CamPos.z=CamPos.z-CamIncVect.z;
		break;
	case 4:
		CamPos.x=CamPos.x-CamAidVect.x;
		CamPos.y=CamPos.y-CamAidVect.y;
		CamPos.z=CamPos.z-CamAidVect.z;
		break;
	case 5:
		CamPos.x=CamPos.x+CamAidVect.x;
		CamPos.y=CamPos.y+CamAidVect.y;
		CamPos.z=CamPos.z+CamAidVect.z;
		break;
	case 6:
		VerAng=VerAng+0.02f*cos(IncAng);
		HorAng=HorAng-0.02f*sin(IncAng);
		ReCam();
		break;
	case 7:
		VerAng=VerAng-0.02f*cos(IncAng);
		HorAng=HorAng+0.02f*sin(IncAng);
		ReCam();
		break;
	case 8:
		VerAng=VerAng-0.02f*sin(IncAng);
		HorAng=HorAng+0.02f*cos(IncAng);
		ReCam();
		break;
	case 9:
		VerAng=VerAng+0.02f*sin(IncAng);
		HorAng=HorAng-0.02f*cos(IncAng);
		ReCam();
		break;
	case 10:
		IncAng=IncAng-0.02f;
		ReCam();
		break;
	case 11:
		IncAng=IncAng+0.02f;
		ReCam();
		break;
	case 12:
		Sight=Sight-0.01f;
		break;
	case 13:
		Sight=Sight+0.01f;
		break;
	}
}

void PixVectIni(){
	float ang1,ang2,ta,tb;
	_3DData base;
	base.x=1;
	base.y=0;
	base.z=0;
	for(unsigned int a=0;a<800;a++){
		for(unsigned int b=0;b<600;b++){
			ta=a;
			tb=b;
			ta=ta-400;
			tb=300-tb;
			ang1=Sight*sqrt(ta*ta+tb*tb)/500;	//500=sqrt(800^2+600^2)/2
			ang2=atan(tb/ta);
			if(ta<0){
				ang2=ang2+3.1415926f;
			}
			base=RotArouY(base,ang1);
			base=RotArouX(base,ang2-3.1415926f/2);
			PixVect[a][b]=base;
			base.x=1;
			base.y=0;
			base.z=0;
		}
	}
}