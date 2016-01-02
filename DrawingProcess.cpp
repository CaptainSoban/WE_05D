#include <stdlib.h>
#include "Console.h"
#include "Renderer.h"
#include "Object.h"
#include "TertiaryArithmeticAlgorithms.h"

//#define CL_USE_DEPRECATED_OPENCL_2_0_APIS
#pragma warning(disable:4996)
#if defined(__APPLE__) || defined(__MACOSX)
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.h>
#endif

#include "Camera.h"

cl_int status;

cl_command_queue CommandQueue;
cl_mem BufIdx[12];
cl_kernel Planarization,Polarization,Hierarchization,Illumination,Coloration;

cl_mem tempcheck;
void ska();

bool Initialization(){
	ConWrite("======== OpenCL Initializing ========\n");

	//Obtian the quantity of platforms
	cl_platform_id ThePlatformID=NULL;
	cl_uint NumPlatforms;
	
	if(CL_INVALID_VALUE==clGetPlatformIDs(NULL,NULL,&NumPlatforms)){
		ConWrite("ERROR: Fail to Get the Number of Available Items in Platform List! The Number of Available Items in Platform List Equal to 0 and Platform List is NULL OR Both Platform List and the Exact Number of Items in Platform List are NULL.\n");
		ConWrite("=== OpenCL Initialization Failed! ===\n");
		return 1;
	}
	else{
		ConWrite("The Number of Items in Platform List is ");
		ConWrite(&NumPlatforms);
		ConWrite(".\n");
	}

	//Obtian the platform list
	cl_platform_id *PlatformList;
	if(NumPlatforms>0){
		PlatformList=(cl_platform_id*)malloc(NumPlatforms*sizeof(cl_platform_id));
		if(CL_INVALID_VALUE==clGetPlatformIDs(NumPlatforms,PlatformList,NULL)){
			ConWrite("ERROR: Fail to Get the Platform List! The Number of Available Items in Platform List Equal to 0 and Platform List is NULL OR Both Platform List and the Exact Number of Items in Platform List are NULL.\n");
			ConWrite("=== OpenCL Initialization Failed! ===\n");
			return 1;
		}
		else{
			ConWrite("Platform List Obtained.\n");
		}
	}
	else{
		ConWrite("ERROR: The Number of Available Items in Platform List is not Greater than 0!\n");
		ConWrite("=== OpenCL Initialization Failed! ===\n");
		return 1;
	}

	/*
	Obtain the information about all platforms 
	*/
	for (unsigned short int i=0;i<NumPlatforms;i++){
		unsigned int Convert=(unsigned int)(i+1);
		ConWrite("-------- Status of Platform ");
		ConWrite(&Convert);
		ConWrite(" -------\n");

		//Platform Name
		size_t NameLength;
		if(CL_SUCCESS==(status=clGetPlatformInfo(PlatformList[i],CL_PLATFORM_NAME,NULL,NULL,&NameLength))){
			ConWrite("The Length of the Platform Name is ");
			ConWrite(&NameLength);
			ConWrite(".\n");
		}
		else{
			if(status==CL_INVALID_PLATFORM){
				ConWrite("ERROR: Cannot Get Length of the Platform Name! The Platform is Invalid.\n");
			}
			else{
				ConWrite("ERROR: Cannot Get Length of the Platform Name! The Information Type is not supported OR The Returned Value Size is Smaller Than the Relevant Minimum Size and the Text Buffer is not NULL.\n");
			}
			ConWrite("-------------------------------------\n");
			ConWrite("=== OpenCL Initialization Failed! ===\n");
			return 1;
		}
		char *Name=(char*)malloc(NameLength);
		if(CL_SUCCESS==(status=clGetPlatformInfo(PlatformList[i],CL_PLATFORM_NAME,NameLength,Name,NULL))){
			ConWrite("#Platform Name: ");
			ConWrite(Name);
			ConWrite(".\n");
		}
		else{
			if(status==CL_INVALID_PLATFORM){
				ConWrite("ERROR: Cannot Get the Name! The Platform is Invalid.\n");
			}
			else{
				ConWrite("ERROR: Cannot Get the Name! The Information Type is not supported OR The Returned Value Size is Smaller Than the Relevant Minimum Size and the Text Buffer is not NULL.\n");
			}
			ConWrite("-------------------------------------\n");
			ConWrite("=== OpenCL Initialization Failed! ===\n");
			return 1;
		}
		free(Name);

		//Platform Version
		size_t VersionLength;
		if(CL_SUCCESS==(status=clGetPlatformInfo(PlatformList[i],CL_PLATFORM_VERSION,NULL,NULL,&VersionLength))){
			ConWrite("The Length of the Version is ");
			ConWrite(&VersionLength);
			ConWrite(".\n");
		}
		else{
			if(status==CL_INVALID_PLATFORM){
				ConWrite("ERROR: Cannot Get Length of the Version! The Platform is Invalid.\n");
			}
			else{
				ConWrite("ERROR: Cannot Get Length of the Version! The Information Type is not supported OR The Returned Value Size is Smaller Than the Relevant Minimum Size and the Text Buffer is not NULL.\n");
			}
			ConWrite("-------------------------------------\n");
			ConWrite("=== OpenCL Initialization Failed! ===\n");
			return 1;
		}
		char *Version=(char*)malloc(VersionLength);
		if(CL_SUCCESS==(status=clGetPlatformInfo(PlatformList[i],CL_PLATFORM_VERSION,VersionLength,Version,NULL))){
			ConWrite("#Version: ");
			ConWrite(Version);
			ConWrite(".\n");
		}
		else{
			if(status==CL_INVALID_PLATFORM){
				ConWrite("ERROR: Cannot Get the Version! The Platform is Invalid.\n");
			}
			else{
				ConWrite("ERROR: Cannot Get the Version! The Information Type is not supported OR The Returned Value Size is Smaller Than the Relevant Minimum Size and the Text Buffer is not NULL.\n");
			}
			ConWrite("-------------------------------------\n");
			ConWrite("=== OpenCL Initialization Failed! ===\n");
			return 1;
		}
		free(Version);
		
		//Platform Profile
		size_t ProfileLength;
		if(CL_SUCCESS==(status=clGetPlatformInfo(PlatformList[i],CL_PLATFORM_PROFILE,NULL,NULL,&ProfileLength))){
			ConWrite("The Length of the Profile is ");
			ConWrite(&ProfileLength);
			ConWrite(".\n");
		}
		else{
			if(status==CL_INVALID_PLATFORM){
				ConWrite("ERROR: Cannot Get Length of the Profile! The Platform is Invalid.\n");
			}
			else{
				ConWrite("ERROR: Cannot Get Length of the Profile! The Information Type is not supported OR The Returned Value Size is Smaller Than the Relevant Minimum Size and the Text Buffer is not NULL.\n");
			}
			ConWrite("-------------------------------------\n");
			ConWrite("=== OpenCL Initialization Failed! ===\n");
			return 1;
		}
		char *Profile=(char*)malloc(ProfileLength);
		if(CL_SUCCESS==(status=clGetPlatformInfo(PlatformList[i],CL_PLATFORM_PROFILE,ProfileLength,Profile,NULL))){
			ConWrite("#Profile Type: ");
			ConWrite(Profile);
			ConWrite(".\n");
		}
		else{
			if(status==CL_INVALID_PLATFORM){
				ConWrite("ERROR: Cannot Get the Profile! The Platform is Invalid.\n");
			}
			else{
				ConWrite("ERROR: Cannot Get the Profile! The Information Type is not supported OR The Returned Value Size is Smaller Than the Relevant Minimum Size and the Text Buffer is not NULL.\n");
			}
			ConWrite("-------------------------------------\n");
			ConWrite("=== OpenCL Initialization Failed! ===\n");
			return 1;
		}
		free(Profile);

		//Platform Extensions
		size_t ExtensionLength;
		if(CL_SUCCESS==(status=clGetPlatformInfo(PlatformList[i],CL_PLATFORM_EXTENSIONS,NULL,NULL,&ExtensionLength))){
			ConWrite("The Length of Extension is ");
			ConWrite(&ExtensionLength);
			ConWrite(".\n");
		}
		else{
			if(status==CL_INVALID_PLATFORM){
				ConWrite("ERROR: Cannot Get Length of Extensions! The Platform is Invalid.\n");
			}
			else{
				ConWrite("ERROR: Cannot Get Length of Extensions! The Information Type is not supported OR The Returned Value Size is Smaller Than the Relevant Minimum Size and the Text Buffer is not NULL.\n");
			}
			ConWrite("-------------------------------------\n");
			ConWrite("=== OpenCL Initialization Failed! ===\n");
			return 1;
		}
		char *Extension=(char*)malloc(ExtensionLength);
		if(CL_SUCCESS==(status=clGetPlatformInfo(PlatformList[i],CL_PLATFORM_EXTENSIONS,ExtensionLength,Extension,NULL))){
			ConWrite("#Extensions Information: ");
			ConWrite(Extension);
			ConWrite(".\n");
		}
		else{
			if(status==CL_INVALID_PLATFORM){
				ConWrite("ERROR: Cannot Get Extensions! The Platform is Invalid.\n");
			}
			else{
				ConWrite("ERROR: Cannot Get Extensions! The Information Type is not supported OR The Returned Value Size is Smaller Than the Relevant Minimum Size and the Text Buffer is not NULL.\n");
			}
			ConWrite("-------------------------------------\n");
			ConWrite("=== OpenCL Initialization Failed! ===\n");
			return 1;
		}
		free(Extension);

		//Platform Vendor
		size_t VendorLength;
		if(CL_SUCCESS==(status=clGetPlatformInfo(PlatformList[i],CL_PLATFORM_VENDOR,NULL,NULL,&VendorLength))){
			ConWrite("The Length of Vendor is ");
			ConWrite(&VendorLength);
			ConWrite(".\n");
		}
		else{
			if(status==CL_INVALID_PLATFORM){
				ConWrite("ERROR: Cannot Get Length of Extensions! The Platform is Invalid.\n");
			}
			else{
				ConWrite("ERROR: Cannot Get Length of Extensions! The Information Type is not supported OR The Returned Value Size is Smaller Than the Relevant Minimum Size and the Text Buffer is not NULL.\n");
			}
			ConWrite("-------------------------------------\n");
			ConWrite("=== OpenCL Initialization Failed! ===\n");
			return 1;
		}
		char *Vendor=(char*)malloc(VendorLength);
		if(CL_SUCCESS==(status=clGetPlatformInfo(PlatformList[i],CL_PLATFORM_VENDOR,VendorLength,Vendor,NULL))){
			ConWrite("#Vendor Name: ");
			ConWrite(Vendor);
			ConWrite(".\n");
		}
		else{
			if(status==CL_INVALID_PLATFORM){
				ConWrite("ERROR: Cannot Get Vendor! The Platform is Invalid.\n");
			}
			else{
				ConWrite("ERROR: Cannot Get Vendor! The Information Type is not supported OR The Returned Value Size is Smaller Than the Relevant Minimum Size and the Text Buffer is not NULL.\n");
			}
			ConWrite("-------------------------------------\n");
			ConWrite("=== OpenCL Initialization Failed! ===\n");
			return 1;
		}
		free(Vendor);
		ConWrite("-------------------------------------\n");
	}

	//Choose a platform
	ConWrite("Choose One Platform for Implementation.\nPress Enter to Continue After Typing in the Ordinal of Platforms: ");
	unsigned short digit=1;
	float Temp=(float)NumPlatforms;
	while((Temp=Temp/10)>=1){
		digit++;
	}
	char *Which=(char*)malloc(digit+1);
	int Choice;
	ConRead(Which,digit);
	if((Choice=atoi(Which))<=0){
		ConWrite("ERROR: Cannot Identify Input! Input Ordinal is Smaller Than 0 OR No Ordinal Detected.\n");
		ConWrite("=== OpenCL Initialization Failed! ===\n");
		return 1;
	}
	else{
		if(Choice>(int)NumPlatforms){
			ConWrite("ERROR: Input Out of Range! Input Ordinal is Larger Than the Total Amount of Platforms.\n");
			ConWrite("=== OpenCL Initialization Failed! ===\n");
			return 1;
		}
	}
	free(Which);
	ThePlatformID=PlatformList[Choice-1];
	ConWrite("Platform ");
	unsigned int ConvertChoice=(unsigned int)Choice;
	ConWrite(&ConvertChoice);
	ConWrite(" Selected!\n");
	/*
	*/

	//Create context from type
	cl_context_properties PropertyText[3] = {CL_CONTEXT_PLATFORM,(cl_context_properties)ThePlatformID,0};
	cl_context_properties *Property=(NULL!=ThePlatformID)?PropertyText:NULL;
	cl_context Context=clCreateContextFromType(Property,CL_DEVICE_TYPE_GPU,NULL,NULL,&status);
	switch(status){
	case CL_SUCCESS:
		ConWrite("CODE: CL_SUCCESS. NOTE: Context Created Successfully!\n");
		break;
	case CL_INVALID_VALUE:
		ConWrite("ERROR: Fail to Create Context! Properties Are Not Available and There Are No Platforms Can Be Use OR The Platform the Properties Provide Is Invalid.\n");
		ConWrite("=== OpenCL Initialization Failed! ===\n");
		return FALSE;
	case CL_INVALID_DEVICE_TYPE:
		ConWrite("ERROR: Fail to Create Context! Invalid Device Type.\n");
		ConWrite("=== OpenCL Initialization Failed! ===\n");
		return FALSE;
	case CL_DEVICE_NOT_AVAILABLE:
		ConWrite("ERROR: Fail to Create Context! No Available Devices Match the Specific Type Currently.\n");
		ConWrite("=== OpenCL Initialization Failed! ===\n");
		return FALSE;
	case CL_DEVICE_NOT_FOUND:
		ConWrite("ERROR: Fail to Create Context! Did Not Find Any Devices Match the Specific Type.\n");
		ConWrite("=== OpenCL Initialization Failed! ===\n");
		return FALSE;
	case CL_OUT_OF_HOST_MEMORY:
		ConWrite("ERROR: Fail to Create Context! The Host Fails to Allocate Resources for OpenCL Implementation.\n");
		ConWrite("=== OpenCL Initialization Failed! ===\n");
		return FALSE;
	default:
		ConWrite("ERROR: Fail to Create Context! Unknown Error.\n");
		ConWrite("=== OpenCL Initialization Failed! ===\n");
		return FALSE;
	}

	//Obtain Device List
	cl_uint LengthOfDevices;
	if(CL_SUCCESS==(status=clGetContextInfo(Context,CL_CONTEXT_DEVICES,NULL,NULL,&LengthOfDevices))){
		ConWrite("The Length of Devices in Context is ");
		ConWrite(&LengthOfDevices);
		ConWrite(".\n");
	}
	else{
		if(status==CL_INVALID_CONTEXT){
			ConWrite("ERROR: Cannot Get the Length of Devices in the Context! Invalid Context.\n");
			ConWrite("=== OpenCL Initialization Failed! ===\n");
			return FALSE;
		}
		else{
			ConWrite("ERROR: Cannot Get the Length of Devices in the Context! Context Information is not Supported OR The Returned Value Size is Smaller Than the Relevant Minimum Size and the Text Buffer is not NULL.\n");
			ConWrite("=== OpenCL Initialization Failed! ===\n");
			return FALSE;
		}
	}
	cl_device_id *DeviceList;
	if(LengthOfDevices>0){
		DeviceList=(cl_device_id*)malloc(LengthOfDevices);
		if(CL_SUCCESS==(status=clGetContextInfo(Context,CL_CONTEXT_DEVICES,LengthOfDevices,DeviceList,NULL))){
			ConWrite("Device List Obtained.\n");
		}
		else{
			if(status==CL_INVALID_CONTEXT){
				ConWrite("ERROR: Fail to Get the Platform List! Invalid Context.\n");
				ConWrite("=== OpenCL Initialization Failed! ===\n");
				return FALSE;
			}
			else{
				ConWrite("ERROR: Fail to Get the Platform List! Context Information is not Supported OR The Returned Value Size is Smaller Than the Relevant Minimum Size and the Text Buffer is not NULL.\n");
				ConWrite("=== OpenCL Initialization Failed! ===\n");
				return FALSE;
			}
		}
	}
	else{
		ConWrite("ERROR: The Number of Available Devices in the Context is not Greater than 0!\n");
		ConWrite("=== OpenCL Initialization Failed! ===\n");
		return FALSE;
	}

	ConWrite("||||||||||||||||||||||||||||||||||||\n");
	for(unsigned short i=0;i<(LengthOfDevices/sizeof(cl_device_id));i++)
	{
		ConWrite("-------------------------------------\n");
		size_t valueSize;

		clGetDeviceInfo(DeviceList[i],CL_DEVICE_NAME,NULL,NULL,&valueSize);
		char *Name=(char*)malloc(valueSize);
		clGetDeviceInfo(DeviceList[i],CL_DEVICE_NAME,valueSize,Name,NULL);
		ConWrite("#DEVICE_NAME: ");
		ConWrite(Name);
		ConWrite(".\n");
		free(Name);

		clGetDeviceInfo(DeviceList[i],CL_DEVICE_VENDOR_ID,NULL,NULL,&valueSize);
		cl_uint *ID=(cl_uint*)malloc(valueSize);
		clGetDeviceInfo(DeviceList[i],CL_DEVICE_VENDOR_ID,valueSize,ID,NULL);
		ConWrite("#VENDOR_ID: ");
		ConWrite(ID);
		ConWrite(".\n");
		free(ID);

		clGetDeviceInfo(DeviceList[i],CL_DEVICE_AVAILABLE,NULL,NULL,&valueSize);
		cl_bool *Available=(cl_bool*)malloc(valueSize);
		clGetDeviceInfo(DeviceList[i],CL_DEVICE_AVAILABLE,valueSize,Available,NULL);
		ConWrite("#AVAILABLE: ");
		if(*Available==CL_TRUE){
			ConWrite("True");
		}
		else{
			ConWrite("False");
		}
		ConWrite(".\n");
		free(Available);

		/*DeviceInfoList(DeviceList[i],CL_DEVICE_ENDIAN_LITTLE);
		DeviceInfoList(DeviceList[i],CL_DEVICE_EXECUTION_CAPABILITIES);
		DeviceInfoList(DeviceList[i],CL_DEVICE_QUEUE_PROPERTIES);
		DeviceInfoList(DeviceList[i],CL_DEVICE_PROFILING_TIMER_RESOLUTION);
		DeviceInfoList(DeviceList[i],CL_DEVICE_LOCAL_MEM_SIZE);
		DeviceInfoList(DeviceList[i],CL_DEVICE_LOCAL_MEM_TYPE);
		DeviceInfoList(DeviceList[i],CL_DEVICE_GLOBAL_MEM_CACHE_SIZE);
		DeviceInfoList(DeviceList[i],CL_DEVICE_GLOBAL_MEM_CACHE_TYPE);
		DeviceInfoList(DeviceList[i],CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE);
		DeviceInfoList(DeviceList[i],CL_DEVICE_GLOBAL_MEM_SIZE);
		DeviceInfoList(DeviceList[i],CL_DEVICE_MAX_CONSTANT_ARGS);
		DeviceInfoList(DeviceList[i],CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE);
		DeviceInfoList(DeviceList[i],CL_DEVICE_SINGLE_FP_CONFIG);*/
		ConWrite("-------------------------------------\n");
	}
	//cl_int status = clGetDeviceIDs(ThePlatformID,CL_DEVICE_TYPE_GPU,0,NULL,&deviceListSize);

	cl_program K_Program=clCreateProgramWithSource(Context,114,Cartography,NULL,&status);
	if(status==NULL){
		ConWrite("NOTE: Kernel Program Created Successfully!\n");
	}
	else{
		ConWrite("Fail!\n");
	}

	//Generate Macro
	cl_uint IdxVertIn=122;
	cl_uint IdxDltIn=220;
	cl_uint SrcXIn=1024;
	cl_uint SrcYIn=768;

	int dig1,dig2,dig3,dig4;
	int TempNum=IdxVertIn;
	for(dig1=1;TempNum>=10;dig1++){
		TempNum=TempNum/10;
	}
	TempNum=IdxDltIn;
	for(dig2=1;TempNum>=10;dig2++){
		TempNum=TempNum/10;
	}
	TempNum=SrcXIn;
	for(dig3=1;TempNum>=10;dig3++){
		TempNum=TempNum/10;
	}
	TempNum=SrcYIn;
	for(dig4=1;TempNum>=10;dig4++){
		TempNum=TempNum/10;
	}
	char *IdxVert=(char*)malloc(dig1+1);
	_itoa((int)IdxVertIn,IdxVert,10);//
	char *COUNTER1=(char*)malloc(dig1+13);
	char cstt1[13]="-D VCOUNTER=";
	memcpy(COUNTER1,cstt1,13);// :D amazing
	strcat(COUNTER1,IdxVert);

	char *IdxDlt=(char*)malloc(dig2+1);
	_itoa((int)IdxDltIn,IdxDlt,10);
	char *COUNTER2=(char*)malloc(dig2+14);
	char cstt2[14]=" -D TCOUNTER=";
	memcpy(COUNTER2,cstt2,14);//
	strcat(COUNTER2,IdxDlt);
	
	char *SrcX=(char*)malloc(dig3+1);
	_itoa((int)SrcXIn,SrcX,10);
	char *COUNTER3=(char*)malloc(dig3+15);
	char cstt3[15]=" -D SCOUNTER1=";
	memcpy(COUNTER3,cstt3,15);//
	strcat(COUNTER3,SrcX);

	char *SrcY=(char*)malloc(dig4+1);
	_itoa((int)SrcYIn,SrcY,10);
	char *COUNTER4=(char*)malloc(dig4+15);
	char cstt4[15]=" -D SCOUNTER2=";
	memcpy(COUNTER4,cstt4,15);//
	strcat(COUNTER4,SrcY);

	char *COUNTER=(char*)malloc(dig1+dig2+dig3+dig4+54);
	memcpy(COUNTER,COUNTER1,13+dig1);//
	strcat(COUNTER,COUNTER2);
	strcat(COUNTER,COUNTER3);
	strcat(COUNTER,COUNTER4);
	//
	status=clBuildProgram(K_Program,LengthOfDevices/sizeof(cl_device_id*),DeviceList,COUNTER,NULL,NULL);
	if(CL_SUCCESS==status){
		ConWrite("CODE: CL_SUCCESS. NOTE: Kernel Program Built.\n");
	}
	else{
		switch(status){
		case CL_INVALID_PROGRAM:
			ConWrite("CODE: CL_INVALID_PROGRAM. ERROR: The Program is an Invalid Program Object!\n");
			break;
		case CL_INVALID_VALUE:
			ConWrite("CODE: CL_INVALID_VALUE. ERROR: Device List is Unavailable and the Number of Devices is Greater Than Zero, OR Device List is NOT NULL and the Number of Devices is Zero, OR the Pointer to Notify is NULL But User Data is NOT NULL!\n");
			break;
		case CL_INVALID_DEVICE:
			ConWrite("CODE: CL_INVALID_DEVICE. ERROR: OpenCL Devices listed in the Device List are NOT in the List of Devices Associated with the Program!\n");
			break;
		case CL_INVALID_BINARY:
			ConWrite("CODE: CL_INVALID_BINARY. ERROR: The Program was Created with Binary and Devices Listed in the Device List do NOT Have a Valid Binary Program!\n");
			break;
		case CL_INVALID_BUILD_OPTIONS:
			ConWrite("CODE: CL_INVALID_BUILD_OPTIONS. ERROR: The Build Options Specified by Options are Invalid!\n");
			break;
		case CL_INVALID_OPERATION:
			ConWrite("CODE: CL_INVALID_OPERATION. ERROR: The Build of the Program Executable for Any of the Devices Listed in the Device List by a Previous Call to the Function for the Program has NOT Completed!\n");
			break;
		//case CL_COMPILER_NOT_AVAILABLE: if program is created with clCreateProgramWithSource and a compiler is not available i.e. CL_DEVICE_COMPILER_AVAILABLE specified in the table of OpenCL Device Queries for clGetDeviceInfo is set to CL_FALSE. 
		//case CL_BUILD_PROGRAM_FAILURE: if there is a failure to build the program executable. This error will be returned if clBuildProgram does not return until the build has completed. 
		//case CL_INVALID_OPERATION: if there are kernel objects attached to program. 
		//case CL_OUT_OF_HOST_MEMORY: if there is a failure to allocate resources required by the OpenCL implementation on the host. 
		}
	}
	cl_build_status *BudStat;
	size_t StatusSize;
	clGetProgramBuildInfo(K_Program,DeviceList[0],CL_PROGRAM_BUILD_STATUS,0,NULL,&StatusSize);
	BudStat=(cl_build_status*)malloc(StatusSize);
	clGetProgramBuildInfo(K_Program,DeviceList[0],CL_PROGRAM_BUILD_STATUS,StatusSize,BudStat,NULL);
	switch (*BudStat){
	case CL_BUILD_NONE:
		ConWrite("CODE: CL_BUILD_NONE.\n");
		break;
	case CL_BUILD_ERROR:
		ConWrite("CODE: CL_BUILD_ERROR.\n");
		break;
	case CL_BUILD_SUCCESS:
		ConWrite("CODE: CL_BUILD_SUCCESS. NOTE: Kernel Program Status Recomfirmed\n");
		break;
	case CL_BUILD_IN_PROGRESS:
		ConWrite("CODE: CL_BUILD_IN_PROGRESS.\n");
	default:
		break;
	}

	char *Log;
	size_t LogSize;
	status=clGetProgramBuildInfo(K_Program,DeviceList[0],CL_PROGRAM_BUILD_LOG,0,NULL,&LogSize);
	if(status==CL_SUCCESS){
		ConWrite("CODE: CL_SUCCESS. NOTE: Kernel Program Build Infomation Obtained.\n");
	}
	else{
		switch(status){
		case CL_INVALID_DEVICE:
			ConWrite("CODE: CL_INVALID_DEVICE. ERROR: The Device is NOT in the List of Devices Associated with the Program.\n");
			break;
		case CL_INVALID_VALUE:
			ConWrite("CODE: CL_INVALID_VALUE. ERROR: The Parameter Name is Invalid, OR the Size in Bytes Specified by Parameter's Value Size is Less Than Size of Return Type and Parameter Value is NOT NULL.\n");
			break;
		case CL_INVALID_PROGRAM:
			ConWrite("CODE: CL_INVALID_PROGRAM. ERROR: The Program is an Invalid Program Object.\n");
			break;
		}
	}
	ConWrite("Build Log:\n");
	Log=(char*)malloc(LogSize+1);
	Log[LogSize]='0';
	clGetProgramBuildInfo(K_Program,DeviceList[0],CL_PROGRAM_BUILD_LOG,LogSize+1,Log,NULL);
	ConWrite(Log);

	ConWrite("||||||||||||||||||||||||||||||||||||\n");
	//Planarization
	Planarization=clCreateKernel(K_Program,"Planarization",&status);
	if(status==NULL){
		ConWrite("CODE: CL_SUCCESS. NOTE: Kernel Object Planarization Created Successful!\n");
	}
	else{
		switch(status){
		case CL_INVALID_PROGRAM:
			ConWrite("CODE: CL_INVALID_PROGRAM. ERROR: The Program is an Invalid Program Object");
			ConWrite("=== OpenCL Initialization Failed! ===\n");
			break;
		case CL_INVALID_PROGRAM_EXECUTABLE:
			ConWrite("CODE: CL_INVALID_PROGRAM_EXECUTABLE. ERROR: There is No Successfully Built for the Program");
			ConWrite("=== OpenCL Initialization Failed! ===\n");
			break;
		case CL_INVALID_KERNEL_NAME:
			ConWrite("CODE: CL_INVALID_KERNEL_NAME. ERROR: The Kernel Name cannot be Found in Program");
			ConWrite("=== OpenCL Initialization Failed! ===\n");
			break;
		case CL_INVALID_KERNEL_DEFINITION:
			ConWrite("CODE: CL_INVALID_KERNEL_DEFINITION. ERROR: if the function definition for __kernel function given by kernel_name such as the number of arguments, the argument types are not the same for all devices for which the program executable has been built");
			ConWrite("=== OpenCL Initialization Failed! ===\n");
			break;
		case CL_INVALID_VALUE:
			ConWrite("CODE: CL_INVALID_VALUE. ERROR: if kernel_name is NULL");
			ConWrite("=== OpenCL Initialization Failed! ===\n");
			break;
		case CL_OUT_OF_HOST_MEMORY:
			ConWrite("CODE: CL_OUT_OF_HOST_MEMORY. ERROR: if there is a failure to allocate resources required by the OpenCL implementation on the host");
			ConWrite("=== OpenCL Initialization Failed! ===\n");
			break;
		}
		return FALSE;
	}

	CamInitial();
	
	cl_float4 CamPosIn;
	CamPosIn.x=CamPos.x;
	CamPosIn.y=CamPos.y;
	CamPosIn.z=CamPos.z;
	CamPosIn.w=0;
	BufIdx[0]=clCreateBuffer(Context,CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR,sizeof(cl_float4),&CamPosIn,NULL);
	
	cl_float4 CamAngIn;
	CamAngIn.x=HorAng;
	CamAngIn.y=VerAng;
	CamAngIn.z=IncAng;
	CamAngIn.w=Sight;
	BufIdx[1]=clCreateBuffer(Context,CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR,sizeof(cl_float4),&CamAngIn,NULL);

	cl_float4 CamNorV1In;
	CamNorV1In.x=CamNorVect.x;
	CamNorV1In.y=CamNorVect.y;
	CamNorV1In.z=CamNorVect.z;
	CamNorV1In.w=WidthPix;
	BufIdx[2]=clCreateBuffer(Context,CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR,sizeof(cl_float4),&CamNorV1In,NULL);

	cl_float4 CamNorV2In;
	CamNorV2In.x=CamIncVect.x;
	CamNorV2In.y=CamIncVect.y;
	CamNorV2In.z=CamIncVect.z;
	CamNorV2In.w=HeightPix;
	BufIdx[3]=clCreateBuffer(Context,CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR,sizeof(cl_float4),&CamNorV2In,NULL);

	cl_float4 CamNorV3In;
	CamNorV3In.x=CamAidVect.x;
	CamNorV3In.y=CamAidVect.y;
	CamNorV3In.z=CamAidVect.z;
	CamNorV3In.w=1/InvSqrt(WidthPix*WidthPix+HeightPix*HeightPix);
	BufIdx[4]=clCreateBuffer(Context,CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR,sizeof(cl_float4),&CamNorV3In,NULL);

	LoadObject();
	cl_float4 AllVertIn[122];
	for(unsigned short i=0;i<120;i++){
		AllVertIn[i].x=AllVert[i][0];
		AllVertIn[i].y=AllVert[i][1];
		AllVertIn[i].z=AllVert[i][2];
		AllVertIn[i].w=0;
	}
	BufIdx[5]=clCreateBuffer(Context,CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR,sizeof(cl_float4)*122,AllVertIn,NULL);
	
	cl_ushort2 ScrPos[122];
	BufIdx[6]=clCreateBuffer(Context,CL_MEM_READ_WRITE|CL_MEM_ALLOC_HOST_PTR,sizeof(cl_ushort2)*122,ScrPos,NULL);
	//
	clSetKernelArg(Planarization,0,sizeof(cl_float4),&CamPosIn);
	clSetKernelArg(Planarization,1,sizeof(cl_float4),&CamAngIn);
	clSetKernelArg(Planarization,2,sizeof(cl_float4),&CamNorV1In);
	clSetKernelArg(Planarization,3,sizeof(cl_float4),&CamNorV2In);
	clSetKernelArg(Planarization,4,sizeof(cl_float4),&CamNorV3In);
	clSetKernelArg(Planarization,5,sizeof(cl_mem),(void*)&BufIdx[5]);
	clSetKernelArg(Planarization,6,sizeof(cl_mem),(void*)&BufIdx[6]);
	
	//Polarization
	Polarization=clCreateKernel(K_Program,"Polarization",&status);
	if(status==NULL){
		ConWrite("NULL\n");
	}
	else{
		if(status==CL_SUCCESS){
			ConWrite("CODE: CL_SUCCESS. NOTE: Kernel Object Polarization Created Successful!\n");
		}
		else{
			ConWrite("Fail!");
		}
	}

	cl_float4 NmVectIn[84];
	for(unsigned short i=0;i<84;i++){
		NmVectIn[i].x=NorVect[i][0];
		NmVectIn[i].y=NorVect[i][1];
		NmVectIn[i].z=NorVect[i][2];
		NmVectIn[i].w=0;
	}
	BufIdx[7]=clCreateBuffer(Context,CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR,sizeof(cl_float4)*84,NmVectIn,NULL);
	
	cl_ushort4 DltIdxIn[220];
	for(unsigned short i=0;i<220;i++){
		DltIdxIn[i].x=DeltaIndex[i][0];
		DltIdxIn[i].y=DeltaIndex[i][1];
		DltIdxIn[i].z=DeltaIndex[i][2];
		DltIdxIn[i].w=DeltaIndex[i][3];	//Planar Normal Vectors Index
	}
	BufIdx[8]=clCreateBuffer(Context,CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR,sizeof(cl_ushort4)*220,DltIdxIn,NULL);

	cl_bool Polar[220];
	BufIdx[9]=clCreateBuffer(Context,CL_MEM_READ_WRITE|CL_MEM_ALLOC_HOST_PTR,sizeof(cl_bool)*220,Polar,NULL);

	clSetKernelArg(Polarization,0,sizeof(cl_float4),&CamPosIn);
	clSetKernelArg(Polarization,1,sizeof(cl_mem),(void*)&BufIdx[7]);
	clSetKernelArg(Polarization,2,sizeof(cl_mem),(void*)&BufIdx[5]);
	clSetKernelArg(Polarization,3,sizeof(cl_mem),(void*)&BufIdx[8]);
	clSetKernelArg(Polarization,4,sizeof(cl_mem),(void*)&BufIdx[9]);
	
	//Hierarchization
	Hierarchization=clCreateKernel(K_Program,"Hierarchization",&status);
	if(status==NULL){
		ConWrite("NULL\n");
	}
	else{
		if(status==CL_SUCCESS){
			ConWrite("CODE: CL_SUCCESS. NOTE: Kernel Object Hierarchization Created Successful!\n");
		}
		else{
			ConWrite("Fail!");
		}
	}
	
	cl_float4 *PixVectIn=(cl_float4*)malloc(786432*sizeof(cl_float4));
	for(unsigned int a=0;a<1024;a++){
		for(unsigned int b=0;b<768;b++){
			PixVectIn[b*1024+a].x=PixVect[a][b].x;
			PixVectIn[b*1024+a].y=PixVect[a][b].y;
			PixVectIn[b*1024+a].z=PixVect[a][b].z;
		}
	}
	BufIdx[10]=clCreateBuffer(Context,CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR,sizeof(cl_float4)*786432,PixVectIn,NULL);
	
	cl_int *TopDltIdxIn=(cl_int*)malloc(786432*sizeof(cl_int));
	BufIdx[11]=clCreateBuffer(Context,CL_MEM_READ_WRITE|CL_MEM_ALLOC_HOST_PTR,sizeof(cl_int)*786432,TopDltIdxIn,NULL);
	
	status=clSetKernelArg(Hierarchization,0,sizeof(cl_mem),(void*)&BufIdx[6]);ska();
	status=clSetKernelArg(Hierarchization,1,sizeof(cl_float4),&CamPosIn);ska();
	status=clSetKernelArg(Hierarchization,2,sizeof(cl_float4),&CamNorV1In);ska();
	status=clSetKernelArg(Hierarchization,3,sizeof(cl_float4),&CamNorV3In);ska();
	status=clSetKernelArg(Hierarchization,4,sizeof(cl_mem),(void*)&BufIdx[5]);ska();
	status=clSetKernelArg(Hierarchization,5,sizeof(cl_mem),(void*)&BufIdx[8]);ska();
	status=clSetKernelArg(Hierarchization,6,sizeof(cl_mem),(void*)&BufIdx[10]);ska();
	status=clSetKernelArg(Hierarchization,7,sizeof(cl_mem),(void*)&BufIdx[9]);ska();
	status=clSetKernelArg(Hierarchization,8,sizeof(cl_mem),(void*)&BufIdx[11]);ska();
	
	//Illumination
	Illumination=clCreateKernel(K_Program,"Illumination",&status);
	if(status==NULL){
		ConWrite("CODE: CL_SUCCESS. NOTE: Kernel Object Illumination Created Successful!\n");
	}
	else{
		switch(status){
		case CL_INVALID_PROGRAM:
			ConWrite("CODE: CL_INVALID_PROGRAM. ERROR: The Program is an Invalid Program Object");
			ConWrite("=== OpenCL Initialization Failed! ===\n");
			break;
		case CL_INVALID_PROGRAM_EXECUTABLE:
			ConWrite("CODE: CL_INVALID_PROGRAM_EXECUTABLE. ERROR: There is No Successfully Built for the Program");
			ConWrite("=== OpenCL Initialization Failed! ===\n");
			break;
		case CL_INVALID_KERNEL_NAME:
			ConWrite("CODE: CL_INVALID_KERNEL_NAME. ERROR: The Kernel Name cannot be Found in Program");
			ConWrite("=== OpenCL Initialization Failed! ===\n");
			break;
		case CL_INVALID_KERNEL_DEFINITION:
			ConWrite("CODE: CL_INVALID_KERNEL_DEFINITION. ERROR: if the function definition for __kernel function given by kernel_name such as the number of arguments, the argument types are not the same for all devices for which the program executable has been built");
			ConWrite("=== OpenCL Initialization Failed! ===\n");
			break;
		case CL_INVALID_VALUE:
			ConWrite("CODE: CL_INVALID_VALUE. ERROR: if kernel_name is NULL");
			ConWrite("=== OpenCL Initialization Failed! ===\n");
			break;
		case CL_OUT_OF_HOST_MEMORY:
			ConWrite("CODE: CL_OUT_OF_HOST_MEMORY. ERROR: if there is a failure to allocate resources required by the OpenCL implementation on the host");
			ConWrite("=== OpenCL Initialization Failed! ===\n");
			break;
		}
		return FALSE;
	}

	cl_float *Reflection=(cl_float*)malloc(220*sizeof(cl_float));
	BufIdx[12]=clCreateBuffer(Context,CL_MEM_READ_WRITE|CL_MEM_ALLOC_HOST_PTR,sizeof(cl_float)*220,Reflection,NULL);

	clSetKernelArg(Illumination,0,sizeof(cl_mem),(void*)&BufIdx[12]);
	clSetKernelArg(Illumination,1,sizeof(cl_mem),(void*)&BufIdx[8]);
	clSetKernelArg(Illumination,2,sizeof(cl_mem),(void*)&BufIdx[7]);

	//Coloration
	Coloration=clCreateKernel(K_Program,"Coloration",&status);
	if(status==NULL){
		ConWrite("CODE: CL_SUCCESS. NOTE: Kernel Object Coloration Created Successful!\n");
	}
	else{
		switch(status){
		case CL_INVALID_PROGRAM:
			ConWrite("CODE: CL_INVALID_PROGRAM. ERROR: The Program is an Invalid Program Object");
			ConWrite("=== OpenCL Initialization Failed! ===\n");
			break;
		case CL_INVALID_PROGRAM_EXECUTABLE:
			ConWrite("CODE: CL_INVALID_PROGRAM_EXECUTABLE. ERROR: There is No Successfully Built for the Program");
			ConWrite("=== OpenCL Initialization Failed! ===\n");
			break;
		case CL_INVALID_KERNEL_NAME:
			ConWrite("CODE: CL_INVALID_KERNEL_NAME. ERROR: The Kernel Name cannot be Found in Program");
			ConWrite("=== OpenCL Initialization Failed! ===\n");
			break;
		case CL_INVALID_KERNEL_DEFINITION:
			ConWrite("CODE: CL_INVALID_KERNEL_DEFINITION. ERROR: if the function definition for __kernel function given by kernel_name such as the number of arguments, the argument types are not the same for all devices for which the program executable has been built");
			ConWrite("=== OpenCL Initialization Failed! ===\n");
			break;
		case CL_INVALID_VALUE:
			ConWrite("CODE: CL_INVALID_VALUE. ERROR: if kernel_name is NULL");
			ConWrite("=== OpenCL Initialization Failed! ===\n");
			break;
		case CL_OUT_OF_HOST_MEMORY:
			ConWrite("CODE: CL_OUT_OF_HOST_MEMORY. ERROR: if there is a failure to allocate resources required by the OpenCL implementation on the host");
			ConWrite("=== OpenCL Initialization Failed! ===\n");
			break;
		}
		return FALSE;
	}

	cl_ushort4 *Bitmap=(cl_ushort4*)malloc(sizeof(cl_ushort4)*786432);
	BufIdx[13]=clCreateBuffer(Context,CL_MEM_READ_WRITE|CL_MEM_ALLOC_HOST_PTR,sizeof(cl_ushort4)*786432,Bitmap,NULL);

	clSetKernelArg(Coloration,0,sizeof(cl_mem),(void*)&BufIdx[13]);
	clSetKernelArg(Coloration,1,sizeof(cl_mem),(void*)&BufIdx[12]);
	clSetKernelArg(Coloration,2,sizeof(cl_mem),(void*)&BufIdx[11]);
	//cl_queue_properties prop[]={CL_QUEUE_PROPERTIES,CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE|CL_QUEUE_ON_DEVICE|CL_QUEUE_ON_DEVICE_DEFAULT,CL_QUEUE_SIZE,CL_DEVICE_QUEUE_ON_DEVICE_PREFERRED_SIZE,0};
	//cl_command_queue CommandQueue=clCreateCommandQueueWithProperties(Context,DeviceList[0],prop,&status);
	CommandQueue=clCreateCommandQueue(Context,DeviceList[0],0,&status);

	cl_float4 tempdt;
	tempcheck=clCreateBuffer(Context,CL_MEM_WRITE_ONLY,sizeof(cl_float4)*122,&tempdt,NULL);
	clSetKernelArg(Planarization,7,sizeof(cl_mem),(void*)&tempcheck);

	//³õÊ¼»¯ÉãÏñ»ú
	
	ConWrite("======== OpenCL Initialized! ========\n");
	return TRUE;
}


void a(){
	if(CL_SUCCESS==status){
		ConWrite("CODE: CL_SUCCESS!\n");
	}
	else{
		switch(status){
		case CL_INVALID_PROGRAM_EXECUTABLE:
			ConWrite("CL_INVALID_PROGRAM_EXECUTABLE\n");
			break;
		case CL_INVALID_COMMAND_QUEUE :
			ConWrite("CL_INVALID_COMMAND_QUEUE\n");
			break;
		case CL_INVALID_KERNEL:
			ConWrite("CL_INVALID_KERNEL\n");
			break;
		case CL_INVALID_CONTEXT :
			ConWrite("CL_INVALID_CONTEXT\n");
			break;
		case CL_INVALID_KERNEL_ARGS :
			ConWrite("CL_INVALID_KERNEL_ARGS\n");
			break;
		case CL_INVALID_WORK_DIMENSION :
			ConWrite("CL_INVALID_WORK_DIMENSION\n");
			break;
		default:
			ConWrite("other\n");
			break;
		}
	}
}

void b(){
	if(status==CL_SUCCESS){
		ConWrite("CODE: CL_SUCCESS.\n");
	}
}

void Draw()
{
	cl_float4 CamPosIn;
	CamPosIn.x=CamPos.x;
	CamPosIn.y=CamPos.y;
	CamPosIn.z=CamPos.z;
	CamPosIn.w=0;
	status=clEnqueueWriteBuffer(CommandQueue,BufIdx[0],CL_TRUE,0,sizeof(cl_float4),&CamPosIn,0,NULL,NULL);
	b();

	cl_float4 CamAngIn;
	CamAngIn.x=HorAng;
	CamAngIn.y=VerAng;
	CamAngIn.z=IncAng;
	CamAngIn.w=Sight;
	status=clEnqueueWriteBuffer(CommandQueue,BufIdx[1],CL_TRUE,0,sizeof(cl_float4),&CamAngIn,0,NULL,NULL);
	b();

	cl_float4 CamNorV1In;
	CamNorV1In.x=CamNorVect.x;
	CamNorV1In.y=CamNorVect.y;
	CamNorV1In.z=CamNorVect.z;
	CamNorV1In.w=WidthPix;
	status=clEnqueueWriteBuffer(CommandQueue,BufIdx[2],CL_TRUE,0,sizeof(cl_float4),&CamNorV1In,0,NULL,NULL);
	b();

	cl_float4 CamNorV2In;
	CamNorV2In.x=CamIncVect.x;
	CamNorV2In.y=CamIncVect.y;
	CamNorV2In.z=CamIncVect.z;
	CamNorV2In.w=HeightPix;
	status=clEnqueueWriteBuffer(CommandQueue,BufIdx[3],CL_TRUE,0,sizeof(cl_float4),&CamNorV2In,0,NULL,NULL);
	b();

	cl_float4 CamNorV3In;
	CamNorV3In.x=CamAidVect.x;
	CamNorV3In.y=CamAidVect.y;
	CamNorV3In.z=CamAidVect.z;
	CamNorV3In.w=1/InvSqrt(WidthPix*WidthPix+HeightPix*HeightPix);
	status=clEnqueueWriteBuffer(CommandQueue,BufIdx[4],CL_TRUE,0,sizeof(cl_float4),&CamNorV3In,0,NULL,NULL);
	b();

	cl_float4 AllVertIn[122];
	for(unsigned short i=0;i<120;i++){
		AllVertIn[i].x=AllVert[i][0];
		AllVertIn[i].y=AllVert[i][1];
		AllVertIn[i].z=AllVert[i][2];
		AllVertIn[i].w=0;
	}
	status=clEnqueueWriteBuffer(CommandQueue,BufIdx[5],CL_TRUE,0,sizeof(cl_float4),AllVertIn,0,NULL,NULL);
	b();

	//Planarization
	size_t GlobalThread1[]={122};
	size_t LocalThread1[]={1};
	status=clEnqueueNDRangeKernel(CommandQueue,Planarization,1,NULL,GlobalThread1,LocalThread1,0,NULL,NULL);
	a();
	unsigned int time=0;
	while(CL_SUCCESS!=clFinish(CommandQueue)){
		time++;
	}
	ConWrite(&time);
	ConWrite("\n");

	//Polarization
	size_t GlobalThread2[1]={220};
	size_t LocalThread2[1]={1};
	status=clEnqueueNDRangeKernel(CommandQueue,Polarization,1,NULL,GlobalThread2,LocalThread2,0,NULL,NULL);
	a();
	time=0;
	while(CL_SUCCESS!=clFinish(CommandQueue)){
		time++;
	}
	ConWrite(&time);
	ConWrite("\n");

	//test read
	/*cl_ushort2 jkl[122];
	cl_float4 ckil[122];
	status=clEnqueueReadBuffer(CommandQueue,BufIdx[6],true,0,sizeof(cl_ushort2)*122,jkl,0,NULL,NULL);
	status=clEnqueueReadBuffer(CommandQueue,tempcheck,true,0,sizeof(cl_float4)*122,ckil,0,NULL,NULL);
	cl_ushort2 jkcl[122];*/


	//Hierarchization
	size_t GlobalThread3[2]={1024,768};
	size_t LocalThread3[2]={1,1};
	status=clEnqueueNDRangeKernel(CommandQueue,Hierarchization,2,NULL,GlobalThread3,LocalThread3,0,NULL,NULL);
	a();
	time=0;
	while(CL_SUCCESS!=clFinish(CommandQueue)){
		time++;
	}
	ConWrite(&time);
	ConWrite("\n");

	//Illumination
	status=clEnqueueNDRangeKernel(CommandQueue,Illumination,1,NULL,GlobalThread2,LocalThread2,0,NULL,NULL);
	a();
	time=0;
	while(CL_SUCCESS!=clFinish(CommandQueue)){
		time++;
	}
	ConWrite(&time);
	ConWrite("\n");

	//Coloration
	status=clEnqueueNDRangeKernel(CommandQueue,Coloration,2,NULL,GlobalThread3,LocalThread3,0,NULL,NULL);
	a();
	time=0;
	while(CL_SUCCESS!=clFinish(CommandQueue)){
		time++;
	}
	ConWrite(&time);
	ConWrite("\n");
}


void ska()
{
	if(CL_SUCCESS==status){
		ConWrite("CL_SUCCESS\n");
	}
	else
	{
		switch (status)
		{
		case CL_INVALID_KERNEL:
			ConWrite("CL_INVALID_KERNEL.\n");
			break;
		case CL_INVALID_ARG_INDEX:
			ConWrite("CL_INVALID_ARG_INDEX.\n");
			break;
		case CL_INVALID_ARG_VALUE:
			ConWrite("CL_INVALID_ARG_VALUE.\n");
			break;
		case CL_INVALID_MEM_OBJECT:
			ConWrite("CL_INVALID_MEM_OBJECT.\n");
			break;
		case CL_INVALID_SAMPLER:
			ConWrite("CL_INVALID_SAMPLER.\n");
			break;
		case CL_INVALID_ARG_SIZE:
			ConWrite("CL_INVALID_ARG_SIZE.\n");
			break;
		default:
			ConWrite("Other.\n");
			break;
		}
	}
}