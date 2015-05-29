/** *********************************
*                                   *
*			测试用文件				*
*                                   *
********************************* **/

#include <windows.h>
#include "container.h"

//全局变量
Container box;

//用于初始化资源及对象
void InitResource(HWND hwnd);

//窗口对应的消息响应函数
LRESULT CALLBACK WndProc(HWND , UINT , WPARAM , LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance , PSTR szCmdLine , int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("Banana Kong");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;
	wndclass.style          = CS_HREDRAW | CS_VREDRAW |CS_DBLCLKS;                  //类风格
	wndclass.lpfnWndProc    = WndProc ;                                 //窗口对应的消息处理函数
	wndclass.cbClsExtra     = 0;                                        //额外空间
	wndclass.cbWndExtra     = 0;                                        //同上
	wndclass.hInstance      = hInstance;                                //实例句柄
	wndclass.hIcon          = LoadIcon(NULL, IDI_APPLICATION);          //设置图标样式
	wndclass.hCursor        = LoadCursor(NULL, IDC_ARROW);              //设置鼠标样式
	wndclass.hbrBackground  = (HBRUSH) GetStockObject(WHITE_BRUSH);     //设置背景色
	wndclass.lpszMenuName   = NULL;                                     //指定窗口类的菜单
	wndclass.lpszClassName  = szAppName;                                //
	if(!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"), szAppName, MB_ICONERROR | MB_OK);
		return 0;
	}
	hwnd = CreateWindow(szAppName ,                         //窗口类名称
		TEXT("The Hello Program"),          //窗口标题
		WS_OVERLAPPEDWINDOW,                //窗口风格,或窗口格式
		CW_USEDEFAULT,                      //初始 x 坐标
		CW_USEDEFAULT,                      //初始 y 坐标
		CW_USEDEFAULT,                      //初始 x 方向尺寸
		CW_USEDEFAULT,                      //初始 y 方向尺寸
		NULL,                               //父窗口句柄
		NULL,                               //窗口菜单句柄
		hInstance,                          //程序实例句柄
		NULL                                //创建参数
		);
	InitResource(hwnd);
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (box.DispatchMSG(hwnd,message,wParam,lParam))
	{
		//若消息有图层响应

	}
	else
	{
		//否则调用默认的窗口处理函数
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
}

void InitResource(HWND hwnd)
{
	//TODO:初始化资源及对象
	box.SetHandle(hwnd);
}