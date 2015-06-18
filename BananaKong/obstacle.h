#ifndef _OBSTACLE_H
#define _OBSTACLE_H

#include "commom.h"
#include <windows.h>
#include <vector>

//物体状态
#define OBSTACLE_NORM		0x0000
#define OBSTACLE_BREAKING	0x0001
#define OBSTACLE_BROKEN		0x0002

//物体类型
#define OBSTACLE_SOFT		0x0001		//柔软物体,碰撞时减速
#define OBSTACLE_HARD		0x0002		//坚硬物体,碰撞时死亡
#define OBSTACLE_WATER		0x0003		//水,碰撞时死亡
#define OBSTACLE_PLATFORM	0x0004		//平台
#define OBSTACLE_LAND		0x0005		//地面

class Obstacle 
{
public:
	//定义Sprite为Obstacle的友元类
	friend class Sprite;

	//构造函数
	Obstacle(int x,int y,int rx,int ry, int cx, int cy,int speed, HBITMAP hbmp,int type);
	
	//复制构造函数
	Obstacle(const Obstacle & obs);

	//显示
	void Show(HDC hdc);

	//获取左边界
	int GetPosLeftX();

	//获取右边界
	int GetPosRightX();

	//左移dis的距离
	void MoveLeft(int dis);

	//状态更新
	void GetNext();

	//物体破碎及状态改变
	void Break();

	//判断物体是否过期
	bool OutOfDate();

	//是否在屏幕内
	bool InScreen(int rx,int ry);

	//析构函数
	~Obstacle();
private:
	int m_x,m_y;					//显示位置
	int m_rx,m_ry;					//显示大小
	int m_cx,m_cy;					//图片大小
	int m_speed;					//移动速度,向右为正
	HBITMAP m_hbmp;					//从正常到破碎的图片
	int m_step;						//当前图片索引
	int m_status;					//物体当前状态
	int m_type;						//物体类型
};

#endif