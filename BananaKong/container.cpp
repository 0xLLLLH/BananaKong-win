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

void Container::Clear()
{
	int cnt=Layers.size();
	for (int i=0;i<cnt;i++)
	{
		delete Layers[i];
	}
	Layers.clear();
}

void Container::Next()
{
	int cnt=Layers.size();
	for (int i=0;i<cnt;i++)
	{
		try
		{
		Layers[i]->GetNext();
		}
		catch (...)
		{
			throw -1;
		}
	}
}

void Container::DrawAll()
{
	RECT rect;
	HDC hdc=GetDC(m_hwnd);
	HDC mdc=CreateCompatibleDC(hdc);
	GetClientRect(m_hwnd,&rect);
	int rx=rect.right-rect.left;
	int ry=rect.bottom-rect.top;
	HGDIOBJ oldpen,oldbrush,oldbmp;
	HBITMAP bmp=CreateCompatibleBitmap(hdc,rx,ry);
	oldbmp=SelectObject(mdc,bmp);
	HPEN hPen=CreatePen(PS_SOLID,0,RGB(RRR,GGG,BBB));
	HBRUSH hBrush=CreateSolidBrush(RGB(RRR,GGG,BBB));
	oldpen=SelectObject(mdc,hPen);
	oldbrush=SelectObject(mdc,hBrush);
	Rectangle(mdc,0,0,rx,ry);
	int NumOfLayer=Layers.size();
	for (int i=NumOfLayer-1;i>=0;i--)
	{
		if (Layers[i]->isVisible())
			Layers[i]->Draw(mdc,rect);
	}
	BitBlt(hdc,0,0,rx,ry,mdc,0,0,SRCCOPY);
	SelectObject(mdc,(HBITMAP)oldbmp);
	SelectObject(mdc,(HPEN)oldpen);
	SelectObject(mdc,(HBRUSH)oldbrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);
	DeleteObject(bmp);
	DeleteDC(mdc);
	ReleaseDC(m_hwnd,hdc);
}

Layer * Container::GetTop()
{
	return Layers[0];
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

void Container::SpeedUp()
{
	//TODO:����ͼ���SpeedUp()��Ա��������ͼ���˶�
}

Container::~Container()
{
	//TODO:�ڴ˴����Container�����������ʵ��
	int NumOfLayer=Layers.size();
	for (int i=0;i<NumOfLayer;i++)
	{
		Layers[i]->~Layer();
		delete Layers[i];
	}
}