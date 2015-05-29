/*!
 * \file container.cpp
 * \date 2015/05/29 19:33
 *
 * \author Lincifer
 * Contact: linlihao159@gmail.com
 *
 * \brief ���ļ�����Container���Ա������ʵ��
 *
*/


#include "container.h"

Container::Container()
{
	//TODO:�ڴ˴����Container��Ĺ��캯��ʵ��
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
	SortLayer();			//ÿ�������ͼ�����������,Ĭ��level�ɸߵ���
}

void Container::SortLayer()
{
	//����Layer��ıȽϺ�����������
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
			//��ĳһͼ�����Ϣ������Ӧ,����Ϣ������ֹ
			//ע��:ĳЩͼ�������Ӧ����Ȼ����false,������Ϣ�������´���
			NoResponse=false;
			break;
		}
	}
	//���غ���ִ�����
	if (NoResponse)
		return false;
	else
		return true;
}

Container::~Container()
{
	//TODO:�ڴ˴����Container�����������ʵ��
}