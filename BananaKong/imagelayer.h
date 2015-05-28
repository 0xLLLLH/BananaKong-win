/*
*
*该头文件包含ImageLayer类的声明
*由Layer类派生
*对应的成员函数实现在ImageLayer.cpp中
*/

#ifndef IMAGE_CLASS_LAYER_H

#define IMAGE_CLASS_LAYER_H

#include <windows.h>
#include "layer.h"

class ImageLayer:public Layer
{
	ImageLayer(bool visible,int level);
	virtual bool Response(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
};

#endif