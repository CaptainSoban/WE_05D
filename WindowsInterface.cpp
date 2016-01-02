/***********************************************
*2015/3/1建立
*Warp Engine最初的开发试验版本
*WARP_ENTITY_ENGINE Test Version0.0.5d
***********************************************/

/*structure
main
	
*/

//目标：
//在单平台单设备上
//

#include <Windows.h>
#include"Console.h"
#include "WindowsMenu.h"
//#include "Open.h"
#include "DrawingProcess.h"
#include "Camera.h"

LRESULT CALLBACK MainWindowProc(HWND MainFrame,UINT uMsg,WPARAM wParam,LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	AllocConsole();
	ConsoleHandle=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTitle("WarpEngine Test Version_0.05d Console");
	COORD ConBuf={127,1024};
	SetConsoleScreenBufferSize(ConsoleHandle,ConBuf);
	SMALL_RECT Rect={0,0,128,36};
	SetConsoleWindowInfo(ConsoleHandle,TRUE,&Rect);
	SetConsoleTextAttribute(ConsoleHandle,FOREGROUND_GREEN);

	WNDCLASS MainWinClass;
	MainWinClass.cbClsExtra=0;
	MainWinClass.cbWndExtra=0;
	MainWinClass.hbrBackground=(HBRUSH)GetStockObject(GRAY_BRUSH);
	MainWinClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	MainWinClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	MainWinClass.hInstance=hInstance;
	MainWinClass.lpfnWndProc=MainWindowProc;
	MainWinClass.lpszClassName="TestForm";
	MainWinClass.lpszMenuName="Option";
	MainWinClass.style=CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS|CS_OWNDC;
	if(RegisterClass(&MainWinClass))
	{
		HMENU Option=CreateMenu();
		HMENU File=CreateMenu();
		HMENU View=CreateMenu();
		HMENU Shader=CreateMenu();
		HMENU About=CreateMenu();
		AppendMenu(Option,MF_POPUP,(UINT_PTR)File,"&File(F)");
		AppendMenu(Option,MF_POPUP,(UINT_PTR)View,"&View(V)");
		AppendMenu(Option,MF_POPUP,(UINT_PTR)Shader,"&Shader(S)");
		AppendMenu(Option,MF_POPUP,(UINT_PTR)About,"&About(A)");
		AppendMenu(File,MF_STRING,IDM_OPEN,"&Open(O)");
		AppendMenu(View,MF_STRING,IDM_FULLSCREEN,"&Full Screen(F)");
		AppendMenu(Shader,MF_STRING,IDM_TEXTURE,"&Texture(T)");
		AppendMenu(Shader,MF_STRING,IDM_TRANSPARENT,"T&ransparent(R)");
		AppendMenu(Shader,MF_STRING,IDM_LIGHT,"&Light(L)");
		AppendMenu(About,MF_STRING,IDM_HELP,"&Help(H)");

		HWND MainWindow=NULL;
		int length=GetSystemMetrics(SM_CXSCREEN);
		int width=GetSystemMetrics(SM_CYSCREEN);
		if(length>=1024&&width>=768)
		{
			int Xpoint=(length-800)/2;
			int Ypoint=(width-600)/2;
			RECT Rc={Xpoint,Ypoint,Xpoint+800,Ypoint+600};
			if(AdjustWindowRect(&Rc,WS_OVERLAPPEDWINDOW^WS_THICKFRAME^WS_MAXIMIZEBOX,TRUE))
				MainWindow=CreateWindow("TestForm","Warp Entity Engine (Version0.0.5) - TestWindow",WS_OVERLAPPEDWINDOW^WS_THICKFRAME^WS_MAXIMIZEBOX,Rc.left,Rc.top,Rc.right-Rc.left,Rc.bottom-Rc.top,NULL,Option,hInstance,NULL);
			else
			{
				MessageBox(NULL,"Cannot Adjust the Main Window!","Error",MB_OK|MB_ICONERROR|MB_SETFOREGROUND);
				return 0;
			}
		}
		else
		{
			MessageBox(NULL,"Current Screen Resolution is Too Low to Contain the Main Window!","Error",MB_OK|MB_ICONERROR|MB_SETFOREGROUND);
			return 0;
		}

		if(MainWindow)
		{
			ShowWindow(MainWindow,SW_SHOWNORMAL);
			UpdateWindow(MainWindow);

			MSG msg;
			while(GetMessage(&msg,NULL,0,0))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			MessageBox(NULL,"Fail to Create the Main Window!","Error",MB_OK|MB_ICONERROR|MB_SETFOREGROUND);
			return 0;
		}
	}
	else
	{
		MessageBox(NULL,"Registration Failed!","Error",MB_OK|MB_ICONERROR|MB_SETFOREGROUND);
		return 0;
	}
	return 0;
}

static BITMAPINFO StandardBitMap;
static HDC Canvas;
static void *BitMemory;

LRESULT CALLBACK MainWindowProc(HWND MainFrame,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_CREATE:
		//OpenModel();
		
		//创建控制台

		StandardBitMap.bmiHeader.biSize=sizeof(StandardBitMap.bmiHeader);
		StandardBitMap.bmiHeader.biWidth=800;
		StandardBitMap.bmiHeader.biHeight=600;
		StandardBitMap.bmiHeader.biBitCount=32;
		StandardBitMap.bmiHeader.biPlanes=1;
		StandardBitMap.bmiHeader.biCompression=BI_RGB;
		if(!CreateDIBSection(Canvas,&StandardBitMap,DIB_RGB_COLORS,&BitMemory,NULL,NULL))
		{
			if(IDABORT==MessageBox(MainFrame,"Cannot Create a DIB!","Error",MB_ABORTRETRYIGNORE|MB_ICONERROR|MB_SETFOREGROUND))
			{
				DestroyWindow(MainFrame);
			}
		}

		Initialization();
		break;
	case WM_PAINT:
		PAINTSTRUCT Paint;
		Canvas=BeginPaint(MainFrame,&Paint);
		//开始绘制
		Draw();
		if(GDI_ERROR==StretchDIBits(Canvas,Paint.rcPaint.left,Paint.rcPaint.top,800,600,0,0,800,600,BitMemory,&StandardBitMap,DIB_RGB_COLORS,SRCCOPY))
		{
			if(IDABORT==MessageBox(MainFrame,"GDI_ERROR!","Error",MB_ABORTRETRYIGNORE|MB_ICONERROR|MB_SETFOREGROUND))
			{
				DestroyWindow(MainFrame);
			}
		}
		//结束绘制
		EndPaint(MainFrame,&Paint);
		break;
	case WM_KEYDOWN:
		switch(wParam)
		{
		case 16:			//shift
			MoveCam(0);		//go front
			break;
		case 17:			//ctrl
			MoveCam(1);		//go back
			break;
		case 38:			//arrow up
			MoveCam(2);		//go up
			break;
		case 40:			//arrow down
			MoveCam(3);		//go down
			break;
		case 37:			//arrow left
			MoveCam(4);		//go left
			break;
		case 39:			//arrow right
			MoveCam(5);		//go right
			break;
		case 87:			//w
			MoveCam(6);		//pitch up
			break;
		case 83:			//s
			MoveCam(7);		//pitch down
			break;
		case 65:			//a
			MoveCam(8);		//yaw left
			break;
		case 68:			//d
			MoveCam(9);		//yaw right
			break;
		case 81:			//q
			MoveCam(10);	//roll left
			break;
		case 69:			//e
			MoveCam(11);	//roll right
			break;
		case 33:			//page up
			MoveCam(12);	//zoom in
			break;
		case 34:			//page down
			MoveCam(13);	//zoom out
		default:
			break;
		}
		InvalidateRgn(MainFrame,NULL,true);
		UpdateWindow(MainFrame);
		break;
	case WM_KEYUP:
		break;
	case WM_COMMAND:
		switch(wParam)
		{
		case IDM_OPEN:
			break;
		case IDM_FULLSCREEN:
			break;
		case IDM_TEXTURE:
			break;
		case IDM_TRANSPARENT:
			break;
		case IDM_LIGHT:
			break;
		case IDM_HELP:
			break;
		}
		break;
	case WM_ACTIVATEAPP:
		break;
	case WM_CLOSE:
		if(IDYES==MessageBox(MainFrame,"Really Want To Quit?","1174Test EXIT",MB_YESNO|MB_ICONHAND|MB_SETFOREGROUND))
		{
			DestroyWindow(MainFrame);
		}
		break;
	case WM_DESTROY:
		CloseHandle(ConsoleHandle);
		FreeConsole();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(MainFrame,uMsg,wParam,lParam);
	}
	return 0;
}

//评估：
//目标基本完成

//问题：
//1.
//2.
//3.

//Copyright Elck. All rights reserved