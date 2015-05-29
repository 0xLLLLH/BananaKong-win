/*!
 * \file imagelayer.cpp
 * \date 2015/05/29 19:17
 *
 * \author Lincifer
 * Contact: linlihao159@gmail.com
 *
 * \brief 该文件包含ImageLayer类成员函数的实现
 *
*/

#include "imagelayer.h"

ImageLayer::ImageLayer(bool visible,int level):Layer(visible,level)
{
	//TODO:在此处添加构造函数实现
}

void Draw(HWND hwnd)
{
	//TODO:在此处添加绘图函数实现
}

bool ImageLayer::Response(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//TODO:在此处添加消息相应函数
}

ImageLayer::~ImageLayer()
{
	//TODO:在此处添加ImageLayer的析构函数
	//注意基类资源的释放
}