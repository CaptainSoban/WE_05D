#ifndef _1174_Camera
#define _1174_Camera
#include "DataDefinition.h"
//------------------------------
//Camera Position
extern _3DData CamPos;

//Horizontal Angle, Vertical Angle and Inclined Angle.
extern float HorAng,VerAng,IncAng;

extern float Sight,WidthPix,HeightPix;

//Camera Normal Vector and Camera Inclined Vector.
extern _3DData CamNorVect;
extern _3DData CamIncVect;
extern _3DData CamAidVect;
extern _3DData PixVect[1024][768];
bool CamInitial();
void ReCam();
void MoveCam(int wParam);
//------------------------------
#endif