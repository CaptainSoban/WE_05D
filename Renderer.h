#ifndef _1174_Renderer
#define _1174_Renderer
//------------------------------
//texture-color, transparent, height, 
const char *Cartography[]=
{
	"__kernel void Planarization(\n",
	"const float4 CamPos,\n",					//X coordinate, Y coordinate, Z coordinate, SectorID
	"const float4 CamAng,\n",					//Horizontal Angle, Vertical Angle, Inclined Angle, Sight Angle
	"const float4 CamNorV1,\n",					//W represents horizontal resolution.
	"const float4 CamNorV2,\n",					//W represents vertical resolution.
	"const float4 CamNorV3,\n",					//W represents diagonal resolution.
	"__global const float4 *Vertex,\n",			//
	"__global ushort2 *ScrPos)\n",				//
	"{\n"
	"	float4 CpToV[VCOUNTER];\n",				//CpToV.w is useless.
	"	int GID=(int)get_global_id(0);\n",
	"	mem_fence(CLK_GLOBAL_MEM_FENCE);\n",

	"	CpToV[GID].xyz=Vertex[GID].xyz-CamPos.xyz;\n",
	"	float Distance[VCOUNTER];\n",
	"	mem_fence(CLK_GLOBAL_MEM_FENCE);\n",

	"	Distance[GID]=tan(acos((CamNorV1.x*CpToV[GID].x+CamNorV1.y*CpToV[GID].y+CamNorV1.z*CpToV[GID].z)*rsqrt(CamNorV1.x*CamNorV1.x+CamNorV1.y*CamNorV1.y+CamNorV1.z*CamNorV1.z)*rsqrt(CpToV[GID].x*CpToV[GID].x+CpToV[GID].y*CpToV[GID].y+CpToV[GID].z*CpToV[GID].z)))/tan(CamAng.w)*CamNorV3.w*0.5f;\n",
	"	float Scale[VCOUNTER];\n",
	"	mem_fence(CLK_GLOBAL_MEM_FENCE);\n",

	"	Scale[GID]=(CamNorV1.x*CpToV[GID].x+CamNorV1.y*CpToV[GID].y+CamNorV1.z*CpToV[GID].z)/(CamNorV1.x*CamNorV1.x+CamNorV1.y*CamNorV1.y+CamNorV1.z*CamNorV1.z);\n",
	"	float4 MapVect[VCOUNTER];\n",
	"	mem_fence(CLK_GLOBAL_MEM_FENCE);\n",

	"	"
	"	MapVect[GID].xyz=CpToV[GID].xyz-Scale[GID]*CamNorV1.xyz;\n",
	"	float Theta1[VCOUNTER];\n",
	"	float Theta2[VCOUNTER];\n",
	"	mem_fence(CLK_GLOBAL_MEM_FENCE);\n",

	"	Theta1[GID]=acos((CamNorV2.x*MapVect[GID].x+CamNorV2.y*MapVect[GID].y+CamNorV2.z*MapVect[GID].z)*rsqrt(CamNorV2.x*CamNorV2.x+CamNorV2.y*CamNorV2.y+CamNorV2.z*CamNorV2.z)*rsqrt(MapVect[GID].x*MapVect[GID].x+MapVect[GID].y*MapVect[GID].y+MapVect[GID].z*MapVect[GID].z));\n",
	"	Theta2[GID]=acos((CamNorV3.x*MapVect[GID].x+CamNorV3.y*MapVect[GID].y+CamNorV3.z*MapVect[GID].z)*rsqrt(CamNorV3.x*CamNorV3.x+CamNorV3.y*CamNorV3.y+CamNorV3.z*CamNorV3.z)*rsqrt(MapVect[GID].x*MapVect[GID].x+MapVect[GID].y*MapVect[GID].y+MapVect[GID].z*MapVect[GID].z));\n",
	"	float Theta[VCOUNTER];\n",
	"	const float Pi=(float)3.1415926f;\n",
	"	mem_fence(CLK_GLOBAL_MEM_FENCE);\n",

	"	(Theta1[GID]<=Pi/2)?(Theta[GID]=Theta2[GID]):(Theta[GID]=2*Pi-Theta2[GID]);\n",
	"	mem_fence(CLK_GLOBAL_MEM_FENCE);\n",

	"	ScrPos[GID].x=(ushort)(cos(Theta[GID])*Distance[GID]+CamNorV1.w*0.5f);\n",
	"	ScrPos[GID].y=(ushort)(sin(Theta[GID])*Distance[GID]+CamNorV2.w*0.5f);\n",
	"}\n",



	"__kernel void Polarization(\n",
	"const float4 CamPos,\n",
	"__global float4 *NmVect,\n",
	"__global float4 *Vertex,\n",
	"__global ushort4 *DltIdx,\n",		//W represents the index of planar vectors of primarch.
	"__global bool *Polar)\n"
	"{\n",
	"	int GID=(int)get_global_id(0);\n",
	"	float4 SPToCam[TCOUNTER];\n",
	"	mem_fence(CLK_GLOBAL_MEM_FENCE);\n",

	"	SPToCam[GID].xyz=CamPos.xyz-Vertex[DltIdx[GID].x].xyz;\n",
	"	float m[TCOUNTER];\n",
	"	mem_fence(CLK_GLOBAL_MEM_FENCE);\n",

	"	m[GID]=SPToCam[GID].x*NmVect[DltIdx[GID].w].x+SPToCam[GID].y*NmVect[DltIdx[GID].w].y+SPToCam[GID].z*NmVect[DltIdx[GID].w].z;\n",
	"	mem_fence(CLK_GLOBAL_MEM_FENCE);\n",

	"	(m[GID]>0)?(Polar[GID]=true):(Polar[GID]=false);\n",
	"}\n",



	"__kernel void Hierarchization(\n",
	"__global ushort2 *ScrPos,\n",
	"const float4 CamPos,\n",
	"const float4 CamNorV1,\n",					//W represents horizontal resolution.
	"const float4 CamNorV3,\n",					//W represents diagonal resolution.
	"__global float4 *AllVert,\n",
	"__global ushort4 *DltIdx,\n",
	"__global float4 *PixVect,\n",
	"__global bool *Polar,\n",
	"__global int *TopDltIdx)\n",
	"{\n",
	"	float Deep[SCOUNTER1*SCOUNTER2],Distance[SCOUNTER1*SCOUNTER2];\n",
	"	int GID1=(int)get_global_id(0);\n",
	"	int GID2=(int)get_global_id(1);\n",
	"	int2 v,u;\n",
	"	int a[SCOUNTER1*SCOUNTER2],b[SCOUNTER1*SCOUNTER2];\n",
	"	float4 m,n,l;\n",
	"	float4 p1[SCOUNTER1*SCOUNTER2],p2[SCOUNTER1*SCOUNTER2];\n",
	"	float t[SCOUNTER1*SCOUNTER2];",
	"	float4 focus[SCOUNTER1*SCOUNTER2];",
	"	Deep[GID1+SCOUNTER1*GID2]=-1;\n",
	"	for(uint i=0;i<TCOUNTER;i++){\n",
	"		if(Polar[i]==true){\n",
	"			v.xy=(int)(ScrPos[DltIdx[i].y].xy-ScrPos[DltIdx[i].x].xy);\n",
	"			u.xy=(int)(ScrPos[DltIdx[i].z].xy-ScrPos[DltIdx[i].x].xy);\n",
	//			Simplify:	Px=Vx*a+Ux*b,
	//						Py=Vy*a+Uy*b.
	"			b[GID1+SCOUNTER1*GID2]=(GID2*v.x-GID1*v.y)/(u.y*v.x-u.x*v.y);\n",
	"			a[GID1+SCOUNTER1*GID2]=(GID1-u.x*b[GID1+SCOUNTER1*GID2])/v.x;\nmem_fence(CLK_GLOBAL_MEM_FENCE);\n",
	"			if(a[GID1+SCOUNTER1*GID2]>=0&&b[GID1+SCOUNTER1*GID2]>=0&&a[GID1+SCOUNTER1*GID2]+b[GID1+SCOUNTER1*GID2]<=1){\n",
	//				Plane Equation
	"				m=AllVert[DltIdx[i].y]-AllVert[DltIdx[i].x];\n",
	"				n=AllVert[DltIdx[i].z]-AllVert[DltIdx[i].x];\n",
	"				l=cross(m,n);\n",
	"				l.w=l.x*(-m.x)+l.y*(-m.y)+l.z*(-m.z);\n",
	//				Two Points in Linear Equation
	"				p1[GID1+SCOUNTER1*GID2]=CamPos;\n",
	"				p2[GID1+SCOUNTER1*GID2]=p1[GID1+SCOUNTER1*GID2]+PixVect[GID1+SCOUNTER1*GID2];",
	//				(x-x1)(x2-x1)=(y-y1)(y2-y1)=(z-z1)(z2-z1)=t
	//				ax+by+cz+d=0
	"				t[GID1+SCOUNTER1*GID2]=(l.x*p1[GID1+SCOUNTER1*GID2].x+l.y*p1[GID1+SCOUNTER1*GID2].y+l.z*p1[GID1+SCOUNTER1*GID2].z+l.w)/(l.x*(p1[GID1+SCOUNTER1*GID2].x-p2[GID1+SCOUNTER1*GID2].x)+l.y*(p1[GID1+SCOUNTER1*GID2].y-p2[GID1+SCOUNTER1*GID2].y)+l.z*(p1[GID1+SCOUNTER1*GID2].z-p2[GID1+SCOUNTER1*GID2].z));\n",
	"				focus[GID1+SCOUNTER1*GID2]=(p2[GID1+SCOUNTER1*GID2]-p1[GID1+SCOUNTER1*GID2])*t[GID1+SCOUNTER1*GID2]+p1[GID1+SCOUNTER1*GID2];\n",
	"				p1[GID1+SCOUNTER1*GID2].w=0;\n",
	"				focus[GID1+SCOUNTER1*GID2].w=0;\n",
	"				Distance[GID1+SCOUNTER1*GID2]=fast_distance(focus[GID1+SCOUNTER1*GID2],p1[GID1+SCOUNTER1*GID2]);\nmem_fence(CLK_GLOBAL_MEM_FENCE);\n",
	"				if(Deep[GID1+SCOUNTER1*GID2]<0||Deep[GID1+SCOUNTER1*GID2]>Distance[GID1+SCOUNTER1*GID2]){\n"
	"					TopDltIdx[GID1+SCOUNTER1*GID2]=i;\nmem_fence(CLK_GLOBAL_MEM_FENCE);\n",
	"				}\nmem_fence(CLK_GLOBAL_MEM_FENCE);\n",
	"			}\nmem_fence(CLK_GLOBAL_MEM_FENCE);\n",
	"		}\nmem_fence(CLK_GLOBAL_MEM_FENCE);\n",
	"	}\nmem_fence(CLK_GLOBAL_MEM_FENCE);\n",
	"}\n",



	"__kernel void Illumination(\n",
	"__global float *Reflection,\n",
	"__global ushort4 *DltIdx,\n",
	"__global float4 *NmVect)\n",
	"{\n",
	"	float4 Light=(float4)(-0.5f,1.0f,-2.0f,0.0f);\n",
	"	int GID=(int)get_global_id(0);\n",
	"	Reflection[GID]=dot(Light,NmVect[DltIdx[GID].w])/(fast_length(Light)*fast_length(NmVect[DltIdx[GID].w]));\n",
	"}\n",



	"__kernel void Coloration(\n",
	"__global ushort4 *Bitmap,\n",
	"__global float *Reflection,\n",
	"__global int *TopDltIdx)\n",
	"{\n",
	"	int GID1=(int)get_global_id(0);\n",
	"	int GID2=(int)get_global_id(1);\n",
	"	Bitmap[GID1+SCOUNTER1*GID2].xyz=(ushort)(Reflection[TopDltIdx[GID1+SCOUNTER1*GID2]]*255);\n",
	"	Bitmap[GID1+SCOUNTER1*GID2].w=255;\n",
	"}\n"
};

//------------------------------
#endif