/*
*
*��ͷ�ļ�����ImageLayer�������
*��Layer������
*��Ӧ�ĳ�Ա����ʵ����ImageLayer.cpp��
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