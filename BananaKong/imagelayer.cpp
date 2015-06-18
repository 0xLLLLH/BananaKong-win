/*!
 * \file imagelayer.cpp
 * \date 2015/05/29 19:17
 *
 * \author Lincifer
 * Contact: linlihao159@gmail.com
 *
 * \brief 该文件包含ImageLayer类成员函数的实现
 *
*/

#include "imagelayer.h"

ImageLayer::ImageLayer(vector<HBITMAP> hbmp,vector<vector<int> >follow,int cx,int cy,bool visible,int level,int speed):
	Layer(visible,level),
	m_bmps(hbmp.begin(),hbmp.end()),
	m_follow(follow.begin(),follow.end())
{
	m_cx=cx;
	m_cy=cy;
	m_speed=speed;
	m_startpos=0;
	//构建初始位图
	srand(time(NULL));
	int width=0;
	BITMAP bmp;
	//int nextbmp=rand()%m_bmps.size();
	int nextbmp=0;
	m_showqueue.push_back(nextbmp);
	GetObject(m_bmps[nextbmp],sizeof(BITMAP),&bmp);
	width+=bmp.bmWidth;
	while (width-m_startpos<m_cx)
	{
		nextbmp=m_follow[m_showqueue.back()][rand()%(m_follow[m_showqueue.back()].size())];	//从可以连接的位图中选出一张
		m_showqueue.push_back(nextbmp);
		GetObject(m_bmps[nextbmp],sizeof(BITMAP),&bmp);
		width+=bmp.bmWidth;
	}
	m_width=width;
}

void ImageLayer::Draw(HDC hdc,RECT rect)
{
	//TODO:在此处添加绘图函数实现
	HDC mdc=CreateCompatibleDC(hdc);
	HBITMAP hold;
	int rx=rect.right-rect.left;
	int ry=rect.bottom-rect.top;
	SetStretchBltMode(hdc,COLORONCOLOR);
	hold=(HBITMAP)SelectObject(mdc,m_bmps[m_showqueue.front()]);
	int rpos=0;
	int cpos=m_startpos;
	for (deque<int>::iterator iter=m_showqueue.begin();iter!=m_showqueue.end();++iter)
	{
		HBITMAP hbmp_now=m_bmps[*iter];
		BITMAP bmp;
		SelectObject(mdc,hbmp_now);
		GetObject(hbmp_now,sizeof (BITMAP),&bmp);
		TransparentBlt(hdc,rpos,0,rx*(bmp.bmWidth-cpos)/m_cx,ry,mdc,cpos,0,bmp.bmWidth-cpos,m_cy,RGB(RRR,GGG,BBB));
		rpos+=rx*(bmp.bmWidth-cpos)/m_cx;
		cpos=0;
	}
	SelectObject(mdc,hold);
	DeleteDC(mdc);
}

void ImageLayer::GetNext()
{
	srand(time(NULL));
	//目前只处理从右向左移动,即m_speed>=0的情况
	if (m_speed>=0)
	{
		//先更新m_startpos
		m_startpos+=m_speed;

		//从队列中将已经过期的(在显示范围外的)位图出队,并更新m_startpos和m_width
		BITMAP bmp;
		GetObject(m_bmps[m_showqueue.front()],sizeof (BITMAP),&bmp);
		while (bmp.bmWidth<=m_startpos&&m_showqueue.size()!=0)
		{
			m_showqueue.pop_front();
			m_startpos-=bmp.bmWidth;
			m_width-=bmp.bmWidth;
			GetObject(m_bmps[m_showqueue.front()],sizeof (BITMAP),&bmp);
		}

		//若过期位图出队后不能铺满屏幕,则添加新位图到队列中
		while (m_width-m_startpos<m_cx)
		{
			int nextbmp=m_follow[m_showqueue.back()][rand()%(m_follow[m_showqueue.back()].size())];	//从可以连接的位图中选出一张
			m_showqueue.push_back(nextbmp);
			GetObject(m_bmps[nextbmp],sizeof(BITMAP),&bmp);
			m_width+=bmp.bmWidth;
		}
	}
}

bool ImageLayer::Response(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (isVisible())
		return false;
	return false;
}

ImageLayer::~ImageLayer()
{
	//TODO:在此处添加ImageLayer的析构函数
}