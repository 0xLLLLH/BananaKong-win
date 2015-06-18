/*!
 * \file imagelayer.h
 * \date 2015/05/29 19:15
 *
 * \author Lincifer
 * Contact: linlihao159@gmail.com
 *
 * \brief 该头文件包含ImageLayer类的声明
 *
 *ImageLayer类由Layer类派生
 *主要用于动画及图像的显示
 *对应的成员函数实现在ImageLayer.cpp中
 *使用时注意个别参数
 *
*/

#ifndef IMAGE_CLASS_LAYER_H

#define IMAGE_CLASS_LAYER_H

#include <windows.h>
#include <vector>
#include <deque>
#include <cstdlib>
#include <time.h>
#include "layer.h"
#include "commom.h"

using namespace std;

class ImageLayer:public Layer
{
public:
	// ImageLayer类的构造函数
	ImageLayer(
		vector< HBITMAP > bmps,
		vector<vector<int> >follow,
		int cx,
		int cy,
		bool visible,
		int level,
		int speed=0);			

	//该函数负责绘制
	virtual void Draw(HDC hdc,RECT rect);

	//类对象更新到下一状态
	virtual void GetNext();

	//消息响应函数
	virtual bool Response(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
 
	~ImageLayer();
private:
	vector<HBITMAP> m_bmps;			// ImageLayer对应的位图
	vector<vector<int> >m_follow;	// 每张位图后可接的位图在m_bmps中的位置k
	deque<int> m_showqueue;			// 当前显示位图在m_bmps中的位置
	int m_cx,m_cy;					// 图像大小
	int m_speed;					// 图像移动速度(向右为正方向单位像素),默认为0(静止)
	int m_startpos;					// 图像显示开始位置
	int m_width;					// 当前队列中位图的总宽度
};

#endif