/**
*���ļ�����Layer���Ա������ʵ��
*/

#include "layer.h"

Layer::Layer(bool visible,int level)
{
	m_visible=visible;
	m_level=level;
}

void Layer::SetVisible(bool visible)
{
	m_visible=visible;
}

void Layer::SetLevel(int level)
{
	m_level=level;
}

void Layer::Draw()
{
	//TODO:�ڴ˴���ӳ�Ա�����ľ���ʵ��
}

bool Layer::Response(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//TODO:�ڴ˴���ӳ�Ա�����ľ���ʵ��
}

Layer::~Layer()
{
	//TODO:�ڴ˴�������������ľ���ʵ��
}