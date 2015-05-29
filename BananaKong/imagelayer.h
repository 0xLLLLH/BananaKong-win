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
 *
*/

#ifndef IMAGE_CLASS_LAYER_H

#define IMAGE_CLASS_LAYER_H

#include <windows.h>
#include "layer.h"

class ImageLayer:public Layer
{
	//ImageLayer类的构造函数
	ImageLayer(bool visible,int level);

	//该函数负责绘制
	virtual void Draw(HWND hwnd);

	//消息响应函数
	virtual bool Response(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	~ImageLayer();
};

#endif