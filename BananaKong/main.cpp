/** *********************************
*                                   *
*			测试用文件				*
*                                   *
********************************* **/
#pragma comment (lib,"winmm.lib")                   //PlaySound()需要的库
#pragma comment(lib, "Msimg32.lib")
#include <windows.h>
#include <vector>
#include "resource.h"
#include "container.h"
#include "commom.h"
//宏定义

#define REDRAWTIME 45

//全局变量
int WindowSizeX=1024;
int WindowSizeY=800;
DWORD time_now,time_pre;

bool GameRunning=false;

int runspeed=6;				//运行速度,最大值RUNSPEEDMAX
DWORD speeduptime=100;

DWORD len;

Container box;
HINSTANCE hIns;
int nCmd;
std::vector<HBITMAP> hBG1,hBG2,hBG3,hSL,hTOP;
//用于初始化资源及对象
bool InitResource(HWND hwnd);
//用于资源的清理
void CleanResource(HWND hwnd);
//窗口对应的消息响应函数
LRESULT CALLBACK WndProc(HWND , UINT , WPARAM , LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance , PSTR szCmdLine , int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("Banana Kong");
	static TCHAR szClasName[] = TEXT("MyWindowClass");
	HWND hwnd;
	WNDCLASS wndclass;
	wndclass.style          = CS_HREDRAW | CS_VREDRAW |CS_DBLCLKS;       //类风格
	wndclass.lpfnWndProc    = WndProc ;                                 //窗口对应的消息处理函数
	wndclass.cbClsExtra     = 0;                                        //额外空间
	wndclass.cbWndExtra     = 0;                                        //同上
	wndclass.hInstance      = hInstance;                                //实例句柄
	wndclass.hIcon          = LoadIcon(NULL, IDI_APPLICATION);          //设置图标样式
	wndclass.hCursor        = LoadCursor(NULL, IDC_ARROW);              //设置鼠标样式
	wndclass.hbrBackground  = (HBRUSH) GetStockObject(WHITE_BRUSH);     //设置背景色
	wndclass.lpszMenuName   = NULL;                                     //指定窗口类的菜单
	wndclass.lpszClassName  = szClasName;                                //
	if(!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"), szAppName, MB_ICONERROR | MB_OK);
		return 0;
	}
	int wndstyle=WS_OVERLAPPEDWINDOW;
	hwnd = CreateWindow(szClasName ,        //窗口类名称
		szAppName,							//窗口标题
		wndstyle,							//窗口风格,或窗口格式
		CW_USEDEFAULT,                      //初始 x 坐标
		CW_USEDEFAULT,                      //初始 y 坐标
		WindowSizeX,						//初始 x 方向尺寸
		WindowSizeY,						//初始 y 方向尺寸
		NULL,                               //父窗口句柄
		NULL,                               //窗口菜单句柄
		hInstance,                          //程序实例句柄
		NULL                                //创建参数
		);
	hIns=hInstance;
	nCmd=iCmdShow;
	//MoveWindow(hwnd, WINDOW_XPOS, WINDOW_YPOS, WINDOW_WIDTH, WINDOW_HEIGHT, true); //用于移动窗口
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	if(!InitResource(hwnd))
	{
		MessageBox(hwnd, TEXT("资源初始化失败"), TEXT("消息窗口"), MB_OK);
		return FALSE;
	}
	MSG msg = {0};
	time_pre = 0;
	DWORD tcnt=0;
	len=0;
	while(msg.message != WM_QUIT)                   //基于PeekMessage()的消息循环
	{
		if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
				time_now = GetTickCount();
				if(time_now - time_pre >= REDRAWTIME)
				{
					
					char szTemp[100];
					box.DrawAll();
					if (GameRunning)
					{
						try
						{
							box.Next();
						}
						catch(...)
						{	
							//if (i==-1)
							{
								sprintf(szTemp,"你的成绩是%d m",len);
								MessageBoxA(hwnd,szTemp,"游戏结束",MB_OK);
								box.GetTop()->SetVisible(true);
								
								CleanResource(hwnd);
								InitResource(hwnd);
								
								GameRunning=false;
								len=0;
								tcnt=0;
							}
						}
						tcnt++;
						len++;
						HDC hdc=GetDC(hwnd);
						TextOutA(hdc,0,0,szTemp,sprintf(szTemp,"%d m",len));
						ReleaseDC(hwnd,hdc);
					}
					time_pre = GetTickCount();
					
					if (tcnt>=speeduptime&&runspeed<=RUNSPEEDMAX)
					{
						tcnt=0;
						box.SpeedUp();
					}
				}
		}
	}
	UnregisterClass(szClasName, wndclass.hInstance);
	return msg.wParam;
	
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//
	// 截取消息以进行特殊处理:
	// 1.WM_DESTROY : 清理资源并退出
	// 2.鼠标左键(只处理游戏开始前)
	// 3.ESC,游戏暂停
	RECT rect;
	switch (message)
	{
	case WM_DESTROY:
		CleanResource(hwnd);
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		//box.Next();
		//box.DrawAll();
		GetClientRect(hwnd,&rect);
		ValidateRect(hwnd,&rect);
		return 0;
	}
	if (message==WM_KEYDOWN&& wParam==VK_SPACE&&!GameRunning)
	{
		GameRunning=true;
		//TODO:在此处添加声音
		PlaySound(TEXT("..\\Resource\\BK-Ingame-9_30loop.wav"),NULL,SND_FILENAME|SND_ASYNC);
		(box.GetTop())->SetVisible(false);
	}
	if (message==WM_KEYDOWN&& wParam==VK_ESCAPE)
	{
		if (GameRunning)
			GameRunning=false;
		else
			GameRunning=true;
		return 0;
	}

	if (box.DispatchMSG(hwnd,message,wParam,lParam))
	{
		//若消息有图层响应
		return 0;
	}
	else
	{
		
		//否则调用默认的窗口处理函数
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
}

bool InitResource(HWND hwnd)
{
	//TODO:初始化资源及对象
	hBG1.clear();
	hBG2.clear();
	hBG3.clear();
	hSL.clear();
	hTOP.clear();
	try
	{
		HBITMAP hbmp;
		std::vector<int>L;
		std::vector<std::vector<int> > link;

		//设置句柄
		box.SetHandle(hwnd);
		//第一层背景资源初始化
		link.clear();
		hBG1.clear();
		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_BG1_0),IMAGE_BITMAP,1024,800,LR_DEFAULTCOLOR);
		hBG1.push_back(hbmp);
		L.clear();
		L.push_back(0);
		L.push_back(1);
		L.push_back(4);
		link.push_back(L);

		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_BG1_1),IMAGE_BITMAP,512,800,LR_DEFAULTCOLOR);
		hBG1.push_back(hbmp);
		L.clear();
		L.push_back(2);
		link.push_back(L);

		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_BG1_2),IMAGE_BITMAP,1024,800,LR_DEFAULTCOLOR);
		hBG1.push_back(hbmp);
		L.clear();
		L.push_back(2);
		L.push_back(3);
		link.push_back(L);

		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_BG1_3),IMAGE_BITMAP,512,800,LR_DEFAULTCOLOR);
		hBG1.push_back(hbmp);
		L.clear();
		L.push_back(0);
		link.push_back(L);

		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_BG1_4),IMAGE_BITMAP,512,800,LR_DEFAULTCOLOR);
		hBG1.push_back(hbmp);
		L.clear();
		L.push_back(6);
		link.push_back(L);

		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_BG1_5),IMAGE_BITMAP,512,800,LR_DEFAULTCOLOR);
		hBG1.push_back(hbmp);
		L.clear();
		L.push_back(0);
		link.push_back(L);

		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_BG1_6),IMAGE_BITMAP,128,800,LR_DEFAULTCOLOR);
		hBG1.push_back(hbmp);
		L.clear();
		L.push_back(7);
		L.push_back(8);
		link.push_back(L);

		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_BG1_7),IMAGE_BITMAP,128,800,LR_DEFAULTCOLOR);
		hBG1.push_back(hbmp);
		L.clear();
		L.push_back(5);
		link.push_back(L);

		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_BG1_8),IMAGE_BITMAP,128,800,LR_DEFAULTCOLOR);
		hBG1.push_back(hbmp);
		L.clear();
		L.push_back(7);
		link.push_back(L);

		ImageLayer * IL=new ImageLayer(hBG1,link,1024,800,true,1,1*runspeed);
		box.AddLayer(IL);
		//第二层背景资源的初始化
		link.clear();
		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_BG2_0),IMAGE_BITMAP,1024,800,LR_DEFAULTCOLOR);
		hBG2.push_back(hbmp);
		L.clear();
		L.push_back(0);
		L.push_back(0);
		L.push_back(0);
		L.push_back(1);
		link.push_back(L);

		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_BG2_1),IMAGE_BITMAP,512,800,LR_DEFAULTCOLOR);
		hBG2.push_back(hbmp);
		L.clear();
		L.push_back(2);
		L.push_back(5);
		link.push_back(L);

		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_BG2_2),IMAGE_BITMAP,512,800,LR_DEFAULTCOLOR);
		hBG2.push_back(hbmp);
		L.clear();
		L.push_back(0);
		link.push_back(L);

		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_BG2_3),IMAGE_BITMAP,512,800,LR_DEFAULTCOLOR);
		hBG2.push_back(hbmp);
		L.clear();
		L.push_back(3);
		L.push_back(4);
		L.push_back(6);
		link.push_back(L);

		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_BG2_4),IMAGE_BITMAP,512,800,LR_DEFAULTCOLOR);
		hBG2.push_back(hbmp);
		L.clear();
		L.push_back(3);
		L.push_back(4);
		L.push_back(6);
		link.push_back(L);

		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_BG2_5),IMAGE_BITMAP,64,800,LR_DEFAULTCOLOR);
		hBG2.push_back(hbmp);
		L.clear();
		L.push_back(3);
		L.push_back(4);
		L.push_back(6);
		link.push_back(L);

		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_BG2_6),IMAGE_BITMAP,64,800,LR_DEFAULTCOLOR);
		hBG2.push_back(hbmp);
		L.clear();
		L.push_back(2);
		link.push_back(L);
		IL=new ImageLayer(hBG2,link,1024,800,true,2,2*runspeed);
		box.AddLayer(IL);

		//第三层背景的资源初始化
		link.clear();
		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_BG3),IMAGE_BITMAP,1024,800,LR_DEFAULTCOLOR);
		hBG3.push_back(hbmp);
		L.clear();
		L.push_back(0);
		link.push_back(L);
		IL=new ImageLayer(hBG3,link,1024,800,true,3,3*runspeed);
		box.AddLayer(IL);

		//SpriteLayer层资源加载
		//以下索引从0开始
		std::deque<Obstacle> que;
		std::deque<std::deque<Obstacle> > Q;
		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_GND_0),IMAGE_BITMAP,32,128,LR_DEFAULTCOLOR);
		hSL.push_back(hbmp);
		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_GND_1),IMAGE_BITMAP,128,128,LR_DEFAULTCOLOR);
		hSL.push_back(hbmp);
		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_GND_2),IMAGE_BITMAP,128,128,LR_DEFAULTCOLOR);
		hSL.push_back(hbmp);
		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_GND_3),IMAGE_BITMAP,128,128,LR_DEFAULTCOLOR);
		hSL.push_back(hbmp);
		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_GND_4),IMAGE_BITMAP,32,128,LR_DEFAULTCOLOR);
		hSL.push_back(hbmp);

		//以下索引从5开始
		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_PLATFORM_0),IMAGE_BITMAP,32,50,LR_DEFAULTCOLOR);
		hSL.push_back(hbmp);
		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_PLATFORM_1),IMAGE_BITMAP,64,50,LR_DEFAULTCOLOR);
		hSL.push_back(hbmp);
		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_PLATFORM_2),IMAGE_BITMAP,64,50,LR_DEFAULTCOLOR);
		hSL.push_back(hbmp);
		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_PLATFORM_3),IMAGE_BITMAP,64,50,LR_DEFAULTCOLOR);
		hSL.push_back(hbmp);
		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_PLATFORM_4),IMAGE_BITMAP,32,50,LR_DEFAULTCOLOR);
		hSL.push_back(hbmp);

		//以下索引从10开始
		//跑动时的图片,子图片135*110
		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_KONG_RUN),IMAGE_BITMAP,405,990,LR_DEFAULTCOLOR);
		hSL.push_back(hbmp);
		//跳跃时的图片,子图片115*100
		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_KONG_JUMP),IMAGE_BITMAP,460,600,LR_DEFAULTCOLOR);
		hSL.push_back(hbmp);
		//滑翔时的图片,子图片126*96
		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_KONG_SLIDE),IMAGE_BITMAP,106,208,LR_DEFAULTCOLOR);
		hSL.push_back(hbmp);
		//跳落时的图片,子图片98*98
		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_KONG_Down),IMAGE_BITMAP,100,100,LR_DEFAULTCOLOR);
		hSL.push_back(hbmp);
		//冲刺时的图片,子图片125*95
		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_KONG_DASH),IMAGE_BITMAP,125,475,LR_DEFAULTCOLOR);
		hSL.push_back(hbmp);
		//碰撞时的图片,子图片110*100
		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_KONG_CRASH),IMAGE_BITMAP,220,200,LR_DEFAULTCOLOR);
		hSL.push_back(hbmp);
		//滑翔伞
		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_PARACHUTE),IMAGE_BITMAP,106,128,LR_DEFAULTCOLOR);
		hSL.push_back(hbmp);

		//以下索引从17开始
		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_BARRIL),IMAGE_BITMAP,490,100,LR_DEFAULTCOLOR);
		hSL.push_back(hbmp);
		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_OBSTACLE_HARD_0),IMAGE_BITMAP,356,103,LR_DEFAULTCOLOR);
		hSL.push_back(hbmp);

		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_BANANA_WAVE_0),IMAGE_BITMAP,256,551,LR_DEFAULTCOLOR);
		hSL.push_back(hbmp);
		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_OBSTACLE_SOFT_0),IMAGE_BITMAP,474,976,LR_DEFAULTCOLOR);
		hSL.push_back(hbmp);

		//21
		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_OBSTACLE_HARD_1),IMAGE_BITMAP,196,122,LR_DEFAULTCOLOR);
		hSL.push_back(hbmp);
		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_OBSTACLE_HARD_2),IMAGE_BITMAP,234,130,LR_DEFAULTCOLOR);
		hSL.push_back(hbmp);
		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_OBSTACLE_HARD_3),IMAGE_BITMAP,356,132,LR_DEFAULTCOLOR);
		hSL.push_back(hbmp);
		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_OBSTACLE_HARD_4),IMAGE_BITMAP,646,90,LR_DEFAULTCOLOR);
		hSL.push_back(hbmp);
		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_OBSTACLE_BANANA),IMAGE_BITMAP,80,54,LR_DEFAULTCOLOR);
		hSL.push_back(hbmp);
		RECT rect;
		GetClientRect(hwnd,&rect);
		int x=rect.right-rect.left;
		int y=rect.bottom-rect.top;
		int landpos=y*(800-128)/800;
		que.push_back(Obstacle(0,landpos,128,128,128,128,-3*runspeed,hSL[1],OBSTACLE_LAND));
		que.push_back(Obstacle(128*1,landpos,128,128,128,128,-3*runspeed,hSL[2],OBSTACLE_LAND));
		que.push_back(Obstacle(128*2,landpos,128,128,128,128,-3*runspeed,hSL[3],OBSTACLE_LAND));
		que.push_back(Obstacle(128*3,landpos-60,75,75,98,100,-3*runspeed,hSL[17],OBSTACLE_SOFT));
		que.push_back(Obstacle(128*3,landpos,128,128,128,128,-3*runspeed,hSL[1],OBSTACLE_LAND));
		que.push_back(Obstacle(128*4,landpos-60,75,75,98,100,-3*runspeed,hSL[17],OBSTACLE_SOFT));
		que.push_back(Obstacle(128*4,landpos,128,128,128,128,-3*runspeed,hSL[3],OBSTACLE_LAND));
		que.push_back(Obstacle(128*5,landpos,128,128,128,128,-3*runspeed,hSL[2],OBSTACLE_LAND));
		que.push_back(Obstacle(128*6,landpos,128,128,128,128,-3*runspeed,hSL[1],OBSTACLE_LAND));
		que.push_back(Obstacle(128*7,landpos,128,128,128,128,-3*runspeed,hSL[2],OBSTACLE_LAND));
		//Q.push_back(que);
		que.push_back(Obstacle(128*2,landpos-120,40,54,40,54,-3*runspeed,hSL[25],OBSTACLE_SOFT));
		que.push_back(Obstacle(128*3,landpos-120,40,54,40,54,-3*runspeed,hSL[25],OBSTACLE_SOFT));
		que.push_back(Obstacle(128*4,landpos-120,40,54,40,54,-3*runspeed,hSL[25],OBSTACLE_SOFT));
		que.push_back(Obstacle(128*5,landpos-120,40,54,40,54,-3*runspeed,hSL[25],OBSTACLE_SOFT));

		que.push_back(Obstacle(128*8,landpos-60,178*2/3,103*2/3,178,103,-3*runspeed,hSL[18],OBSTACLE_HARD));
		que.push_back(Obstacle(128*8,landpos,128,128,128,128,-3*runspeed,hSL[2],OBSTACLE_LAND));
		Q.push_back(que);
		//地形
		que.clear();
		que.push_back(Obstacle(0,landpos,128,128,128,128,-3*runspeed,hSL[1],OBSTACLE_LAND));
		que.push_back(Obstacle(128*1,landpos,128,128,128,128,-3*runspeed,hSL[2],OBSTACLE_LAND));
		que.push_back(Obstacle(128*2,landpos,128,128,128,128,-3*runspeed,hSL[3],OBSTACLE_LAND));
		que.push_back(Obstacle(128*2+96,landpos-128,32,50,32,50,-3*runspeed,hSL[5],OBSTACLE_PLATFORM));
		que.push_back(Obstacle(128*3,landpos,128,128,128,128,-3*runspeed,hSL[1],OBSTACLE_LAND));
		que.push_back(Obstacle(128*3,landpos-128,128,50,64,50,-3*runspeed,hSL[6],OBSTACLE_PLATFORM));
		que.push_back(Obstacle(128*4,landpos,128,128,128,128,-3*runspeed,hSL[3],OBSTACLE_LAND));
		que.push_back(Obstacle(128*4,landpos-128,128,50,64,50,-3*runspeed,hSL[7],OBSTACLE_PLATFORM));
		que.push_back(Obstacle(128*4,landpos-60-128,75,75,98,100,-3*runspeed,hSL[17],OBSTACLE_SOFT));
		que.push_back(Obstacle(128*5,landpos,128,128,128,128,-3*runspeed,hSL[2],OBSTACLE_LAND));
		que.push_back(Obstacle(128*5,landpos-128,128,50,64,50,-3*runspeed,hSL[8],OBSTACLE_PLATFORM));
		que.push_back(Obstacle(128*6,landpos,128,128,128,128,-3*runspeed,hSL[1],OBSTACLE_LAND));
		que.push_back(Obstacle(128*6,landpos-128,32,50,32,50,-3*runspeed,hSL[9],OBSTACLE_PLATFORM));
		que.push_back(Obstacle(128*5,landpos-60,178*2/3,103*2/3,178,103,-3*runspeed,hSL[18],OBSTACLE_HARD));
		que.push_back(Obstacle(128*7,landpos,128,128,128,128,-3*runspeed,hSL[2],OBSTACLE_LAND));
		Q.push_back(que);
		que.push_back(Obstacle(128*5+96,landpos-256,32,50,32,50,-3*runspeed,hSL[5],OBSTACLE_PLATFORM));
		que.push_back(Obstacle(128*6,landpos-256,128,50,64,50,-3*runspeed,hSL[6],OBSTACLE_PLATFORM));
		que.push_back(Obstacle(128*7,landpos-256,32,50,32,50,-3*runspeed,hSL[9],OBSTACLE_PLATFORM));
		que.push_back(Obstacle(128*8,landpos,128,128,128,128,-3*runspeed,hSL[1],OBSTACLE_LAND));
		Q.push_back(que);
		que.pop_back();
		que.push_back(Obstacle(128*2+96,landpos-102,158,122,158,122,-3*runspeed,hSL[20],OBSTACLE_SOFT));
		que.push_back(Obstacle(128*8,landpos,128,128,128,128,-3*runspeed,hSL[1],OBSTACLE_LAND));
		Q.push_back(que);

		
		que.clear();

		que.push_back(Obstacle(0,landpos,128,128,128,128,-3*runspeed,hSL[1],OBSTACLE_LAND));
		que.push_back(Obstacle(128*1,landpos,128,128,128,128,-3*runspeed,hSL[2],OBSTACLE_LAND));
		que.push_back(Obstacle(128*2,landpos,128,128,128,128,-3*runspeed,hSL[3],OBSTACLE_LAND));
		que.push_back(Obstacle(128*2+96,landpos-128,32,50,32,50,-3*runspeed,hSL[5],OBSTACLE_PLATFORM));
		que.push_back(Obstacle(128*3,landpos,128,128,128,128,-3*runspeed,hSL[1],OBSTACLE_LAND));
		que.push_back(Obstacle(128*3,landpos-128,128,50,64,50,-3*runspeed,hSL[6],OBSTACLE_PLATFORM));
		que.push_back(Obstacle(128*4,landpos,128,128,128,128,-3*runspeed,hSL[3],OBSTACLE_LAND));
		que.push_back(Obstacle(128*4,landpos-128,128,50,64,50,-3*runspeed,hSL[7],OBSTACLE_PLATFORM));
		que.push_back(Obstacle(128*5,landpos-98-128,98,122,98,122,-3*runspeed,hSL[21],OBSTACLE_HARD));
		que.push_back(Obstacle(128*5,landpos,128,128,128,128,-3*runspeed,hSL[2],OBSTACLE_LAND));
		que.push_back(Obstacle(128*5,landpos-128,128,50,64,50,-3*runspeed,hSL[8],OBSTACLE_PLATFORM));
		que.push_back(Obstacle(128*6,landpos,128,128,128,128,-3*runspeed,hSL[1],OBSTACLE_LAND));
		que.push_back(Obstacle(128*6,landpos-128,32,50,32,50,-3*runspeed,hSL[9],OBSTACLE_PLATFORM));
		que.push_back(Obstacle(128*5,landpos-85,323,90,323,90,-3*runspeed,hSL[24],OBSTACLE_HARD));
		que.push_back(Obstacle(128*7,landpos,128,128,128,128,-3*runspeed,hSL[2],OBSTACLE_LAND));
		Q.push_back(que);

		//============
		int cx[]={135,115,106,100,125,110,106};
		int cy[]={110,100,104,100,95,100,128};
		Sprite kong(128,landpos-85,110,100,cx,cy,hSL[10],hSL[11],hSL[12],hSL[13],hSL[14],hSL[15],hSL[16],7,-40,3,40,runspeed);
		SpriteLayer * SL=new SpriteLayer(kong,Q,true,4);
		box.AddLayer(SL);

		hbmp=(HBITMAP)LoadImage(hIns,MAKEINTRESOURCE(IDB_TOP_LOGO),IMAGE_BITMAP,1024,800,LR_DEFAULTCOLOR);
		hTOP.push_back(hbmp);
		L.push_back(0);
		link.push_back(L);
		IL=new ImageLayer(hTOP,link,1024,800,true,6);
		box.AddLayer(IL);
	}
	catch(...)
	{
		return false;
	}
	return true;
}

void CleanResource(HWND hwnd)
{
	box.Clear();
	for (std::vector<HBITMAP>::iterator iter=hBG1.begin();iter!=hBG1.end();++iter)
	{
		DeleteObject(*iter);
	}
	for (std::vector<HBITMAP>::iterator iter=hBG2.begin();iter!=hBG2.end();++iter)
	{
		DeleteObject(*iter);
	}
	for (std::vector<HBITMAP>::iterator iter=hBG3.begin();iter!=hBG3.end();++iter)
	{
		DeleteObject(*iter);
	}
	for (std::vector<HBITMAP>::iterator iter=hSL.begin();iter!=hSL.end();++iter)
	{
		DeleteObject(*iter);
	}
	for (std::vector<HBITMAP>::iterator iter=hTOP.begin();iter!=hTOP.end();++iter)
	{
		DeleteObject(*iter);
	}
	//DeleteObject(hBG3);
}