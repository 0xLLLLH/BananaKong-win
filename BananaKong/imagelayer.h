/*!
 * \file imagelayer.h
 * \date 2015/05/29 19:15
 *
 * \author Lincifer
 * Contact: linlihao159@gmail.com
 *
 * \brief ��ͷ�ļ�����ImageLayer�������
 *
 *ImageLayer����Layer������
 *��Ҫ���ڶ�����ͼ�����ʾ
 *��Ӧ�ĳ�Ա����ʵ����ImageLayer.cpp��
 *
*/

#ifndef IMAGE_CLASS_LAYER_H

#define IMAGE_CLASS_LAYER_H

#include <windows.h>
#include "layer.h"

class ImageLayer:public Layer
{
	//ImageLayer��Ĺ��캯��
	ImageLayer(bool visible,int level);

	//�ú����������
	virtual void Draw(HWND hwnd);

	//��Ϣ��Ӧ����
	virtual bool Response(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	~ImageLayer();
};

#endif