/*!
 * \file container.cpp
 * \date 2015/05/29 19:33
 *
 * \author Lincifer
 * Contact: linlihao159@gmail.com
 *
 * \brief 该文件包含Container类成员函数的实现
 *
*/


#include "container.h"

Container::Container()
{
	//TODO:在此处添加Container类的构造函数实现
}

Container::Container(HWND hwnd)
{
	m_hwnd=hwnd;
}

void Container::SetHandle(HWND hwnd)
{
	m_hwnd=hwnd;
}

void Container::AddLayer(Layer * layer)
{
	Layers.push_back(layer);
	SortLayer();			//每次添加新图层后重新排序,默认level由高到低
}

void Container::SortLayer()
{
	//调用Layer类的比较函数进行排序
	std::sort(Layers.begin(),Layers.end(),LayerCmp);
}

void Container::DrawAll()
{
	int NumOfLayer=Layers.size();
	for (int i=NumOfLayer;i>=0;i--)
	{
		Layers[i]->Draw(m_hwnd);
	}
}

bool Container::DispatchMSG(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int NumOfLayer=Layers.size();
	bool NoResponse=true;
	for (int i=0;i<NumOfLayer;i++)
	{
		if (Layers[i]->Response(hwnd,message,wParam,lParam))
		{
			//若某一图层对消息进行响应,则消息传递终止
			//注意:某些图层可能响应后仍然返回false,以让消息继续向下传递
			NoResponse=false;
			break;
		}
	}
	//返回函数执行情况
	if (NoResponse)
		return false;
	else
		return true;
}

Container::~Container()
{
	//TODO:在此处添加Container类的析构函数实现
}