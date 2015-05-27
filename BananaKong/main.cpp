/** *********************************
*                                   *
*			测试用文件				*
*                                   *
********************************* **/
#include <windows.h>
LRESULT CALLBACK WndProc(HWND , UINT , WPARAM , LPARAM);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance , PSTR szCmdLine , int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("HelloWindows!");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;
	wndclass.style          = CS_HREDRAW | CS_VREDRAW;                  //类风格
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
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	switch(message)
	{
	case WM_CREATE :
		//PlaySound(TEXT("hellowin.wav"),NULL,SND_FILENAME|SND_ASYNC);
		return 0;
	case WM_PAINT:          //必须进行绘制以消除无效矩形,否则将死循环
		hdc = BeginPaint(hwnd , &ps);
		//==========
		//在接下来的部分进行绘制
		GetClientRect(hwnd , &rect);
		DrawText(hdc, TEXT("Hello Windows 8.1!"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hwnd, &ps);        //结束绘图并释放设备环境句柄
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);         //将退出消息插入消息队列以结束循环
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}