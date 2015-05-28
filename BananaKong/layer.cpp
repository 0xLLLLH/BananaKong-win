/**
*该文件包含Layer类成员函数的实现
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
	//TODO:在此处添加成员函数的具体实现
}

bool Layer::Response(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//TODO:在此处添加成员函数的具体实现
}

Layer::~Layer()
{
	//TODO:在此处添加析构函数的具体实现
}