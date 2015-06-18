#ifndef SPRITELAYER
#define SPRITELAYER

#include <cstdlib>
#include <time.h>
#include <deque>
#include "layer.h"
#include "sprite.h"
#include "obstacle.h"
#include "commom.h"

class SpriteLayer:public Layer
{
public:
	//构造函数
	SpriteLayer(Sprite sprite,std::deque<std::deque<Obstacle> > objs,bool visible,int level);
	
	//响应消息
	bool Response(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	//绘图
	void Draw(HDC hdc,RECT rect);

	//更新状态
	void GetNext();

	//析构函数
	~SpriteLayer();

private:
	Sprite m_kong;						//就是kong啦
	std::deque<Obstacle> m_objnow;			//当前屏幕范围内的物体
	std::deque<std::deque<Obstacle> > m_objs;		//所有可能的物体组合
	int m_rx,m_ry;						//当前屏幕范围,由第一次绘图时确定
};

#endif