/*!
 * \file imagelayer.cpp
 * \date 2015/05/29 19:17
 *
 * \author Lincifer
 * Contact: linlihao159@gmail.com
 *
 * \brief ���ļ�����ImageLayer���Ա������ʵ��
 *
*/

#include "imagelayer.h"

ImageLayer::ImageLayer(bool visible,int level):Layer(visible,level)
{
	//TODO:�ڴ˴���ӹ��캯��ʵ��
}

void Draw(HWND hwnd)
{
	//TODO:�ڴ˴���ӻ�ͼ����ʵ��
}

bool ImageLayer::Response(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//TODO:�ڴ˴������Ϣ��Ӧ����
}

ImageLayer::~ImageLayer()
{
	//TODO:�ڴ˴����ImageLayer����������
	//ע�������Դ���ͷ�
}