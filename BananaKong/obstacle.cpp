#include "obstacle.h"

Obstacle::Obstacle(int x,int y,int rx,int ry, int cx, int cy,int speed, HBITMAP hbmp,int type)
{
	m_x=x;
	m_y=y;
	m_cx=cx;
	m_cy=cy;
	m_rx=rx;
	m_ry=ry;
	m_hbmp=hbmp;
	m_type=type;
	m_step=0;
	m_speed=speed;
	m_status=OBSTACLE_NORM;
}

Obstacle::Obstacle( const Obstacle & obs)
{
	m_x=obs.m_x;
	m_y=obs.m_y;
	m_cx=obs.m_cx;
	m_cy=obs.m_cy;
	m_rx=obs.m_rx;
	m_ry=obs.m_ry;
	m_hbmp=obs.m_hbmp;
	m_type=obs.m_type;
	m_step=0;
	m_speed=obs.m_speed;
	m_status=OBSTACLE_NORM;
}


void Obstacle::Show(HDC hdc)
{
	HDC mdc=CreateCompatibleDC(hdc);
	HBITMAP hold;
	BITMAP bmp;
	int x,y;
	GetObject(m_hbmp,sizeof(BITMAP),&bmp);
	x=bmp.bmWidth/m_cx;
	y=bmp.bmHeight/m_cy;
	m_step%=x*y;
	hold=(HBITMAP)SelectObject(mdc,m_hbmp);
	TransparentBlt(hdc,m_x,m_y,m_rx,m_ry,mdc,(m_step%x)*m_cx,(m_step/x)*m_cy,m_cx,m_cy,RGB(RRR,GGG,BBB));
	SelectObject(mdc,hold);
	DeleteDC(mdc);
}

void Obstacle::Break()
{
	if(m_status==OBSTACLE_NORM)
		m_status=OBSTACLE_BREAKING;
}

void Obstacle::GetNext()
{
	m_x+=m_speed;
	if (m_status==OBSTACLE_NORM)
	{
		//¾²Ö¹
	}
	else if (m_status==OBSTACLE_BREAKING)
	{
		m_step++;
		BITMAP bmp;
		int x,y;
		GetObject(m_hbmp,sizeof(BITMAP),&bmp);
		x=bmp.bmWidth/m_cx;
		y=bmp.bmHeight/m_cy;
		if (m_step==x*y-1)
		{
			m_status=OBSTACLE_BROKEN;
		}
	}else if (m_status==OBSTACLE_BROKEN)
	{
		//¾²Ö¹
	}
}

bool Obstacle::OutOfDate()
{
	if (m_x+m_rx<0||m_y+m_ry<0)
	{
		return true;
	}
	return false;
}

bool Obstacle::InScreen(int rx,int ry)
{
	if (m_x+m_rx<=rx&&m_x>=0)
	{
		return true;
	}
	return false;
}

void Obstacle::MoveLeft(int dis)
{
	m_x-=dis;
}

int Obstacle::GetPosLeftX()
{
	return m_x;
}

int Obstacle::GetPosRightX()
{
	return m_x+m_rx;
}

Obstacle::~Obstacle()
{

}