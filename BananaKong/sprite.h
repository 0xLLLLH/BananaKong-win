#ifndef _SPRITE_H

#define _SPRITE_H


#include <windows.h>
#include <vector>
#include "obstacle.h"
#include "commom.h"


//标志sprite的状态,对于每一个状态,应当有对应的位图数组
#define SPRITE_RUN		0x0000
#define SPRITE_JUMP		0x0001
#define SPRITE_SLIDE	0x0002
#define SPRITE_DOWN		0x0003
#define SPRITE_DASH		0x0004
#define SPRITE_CRASH	0x0005
#define SPRITE_DROP		0x0006

//碰撞状态
#define CRASH_TOP				0x0010
#define CRASH_RIGHTTOP			0x0020
#define CRASH_RIGHT				0x0030
#define CRASH_RIGHTBOTTOM		0x0040
#define CRASH_BOTTOM			0x0050
#define NOCRASH					0x0060

class Sprite
{
public:
	//构造函数
	Sprite(int x,int y,int rx,int ry,int cx[7],int cy[7],
		HBITMAP hrun,
		HBITMAP hjump,
		HBITMAP hslide,
		HBITMAP hdown,
		HBITMAP hdash,
		HBITMAP hcrash,
		HBITMAP hparachute,
		int g,int jumpspeed,int slidespeed,int downspeed,int showratio);

	//显示
	void show(HDC hdc);

	void KeyCheckAndReponse();

	int GetStatus();

	// 对控制消息进行响应
	// W跳跃,S下落,D冲刺
	// 按住空格将进行滑翔
	//bool Response(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Jump();

	void Run();

	void Slide();

	void Down();

	void Dash();

	void Drop();

	void CrashRight();

	void CrashRightBottom();

	//更新状态
	void GetNext();

	//检查是否和物体碰撞
	//若与非soft类型的物体发生接触,返回碰撞类型,否则返回-1
	int CrashCheck(Obstacle & obj);

	//析构函数
	~Sprite();
private:
	int m_x,m_y;		//显示位置坐标
	int m_rx,m_ry;		//显示大小
	int m_cx[7],m_cy[7];//图片大小
	int m_step;			//当前状态下的步数
	int m_status;		//标志精灵当前的状态
	HBITMAP m_hrun;		//跑动位图
	HBITMAP m_hjump;		//跳跃位图
	HBITMAP m_hslide;		//滑翔位图
	HBITMAP m_hdown;		//下落位图
	HBITMAP m_hdash;		//冲刺位图
	HBITMAP m_hcrash;		//碰撞死亡位图
	HBITMAP m_hparachute;		//滑翔伞
	int m_v;				//速度,小于0为向上,运动时重力加速度影响
	int m_g;				//重力加速度,大于0
	int m_jumpspeed;		//跳跃时向上的速度
	int m_slidespeed;		//滑翔时的速度
	int m_downspeed;		//滚动下落的速度,当下落速度达到滚动下落速度时,状态将变为SPRITE_DOWN
	int m_showratio;		//刷新率
	DWORD cnt;				//计时用
};

#endif