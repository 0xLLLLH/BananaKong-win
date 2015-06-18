#include "sprite.h"

Sprite::Sprite(int x,int y,int rx,int ry,int cx[7],int cy[7],
	HBITMAP hrun,
	HBITMAP hjump,
	HBITMAP hslide,
	HBITMAP hdown,
	HBITMAP hdash,
	HBITMAP hcrash,
	HBITMAP hparachute,
	int g,int jumpspeed,int slidespeed,int downspeed,int showratio)
{
	m_x=x;
	m_y=y;
	m_rx=rx;
	m_ry=ry;
	for (int i=0;i<6;i++)
	{
		m_cx[i]=cx[i];
		m_cy[i]=cy[i];
	}
	m_v=0;
	m_jumpspeed=jumpspeed;
	m_g=g;
	m_hrun=hrun,
	m_hjump=hjump,
	m_hslide=hslide,
	m_hdown=hdown,
	m_hdash=hdash,
	m_hcrash=hcrash,
	m_hparachute=hparachute;
	m_slidespeed=slidespeed;
	m_downspeed=downspeed;
	m_status=SPRITE_RUN;
	m_step=0;
	m_showratio=showratio;
	cnt=0;
}

void Sprite::show(HDC hdc)
{
	HDC mdc=CreateCompatibleDC(hdc);
	HBITMAP hold;
	BITMAP bmp;
	int x,y;
	//判断状态
	if((m_status&0x000F)==SPRITE_RUN)
	{
		GetObject(m_hrun,sizeof(BITMAP),&bmp);
		x=bmp.bmWidth/m_cx[(m_status&0x000F)];
		y=bmp.bmHeight/m_cy[(m_status&0x000F)];
		m_step%=x*y;
		hold=(HBITMAP)SelectObject(mdc,m_hrun);
	}
	else if((m_status&0x000F)==SPRITE_JUMP)
	{
		GetObject(m_hjump,sizeof(BITMAP),&bmp);
		x=bmp.bmWidth/m_cx[(m_status&0x000F)];
		y=bmp.bmHeight/m_cy[(m_status&0x000F)];
		m_step%=x*y;
		hold=(HBITMAP)SelectObject(mdc,m_hjump);
	}
	else if((m_status&0x000F)==SPRITE_SLIDE)
	{
		GetObject(m_hslide,sizeof(BITMAP),&bmp);
		x=bmp.bmWidth/m_cx[(m_status&0x000F)];
		y=bmp.bmHeight/m_cy[(m_status&0x000F)];
		m_step%=x*y;
		hold=(HBITMAP)SelectObject(mdc,m_hslide);
// 		if (m_step>=0)
// 		{
// 			SelectObject(mdc,m_hparachute);
// 			TransparentBlt(hdc,m_x,m_y-36,m_rx,m_ry,mdc,0,0,m_cx[7],m_cy[7],RGB(RRR,GGG,BBB));
// 			SelectObject(mdc,m_hslide);
// 		}

	}
	else if((m_status&0x000F)==SPRITE_DOWN)
	{
		GetObject(m_hdown,sizeof(BITMAP),&bmp);
		x=bmp.bmWidth/m_cx[(m_status&0x000F)];
		y=bmp.bmHeight/m_cy[(m_status&0x000F)];
		m_step%=x*y;
		hold=(HBITMAP)SelectObject(mdc,m_hdown);
	}
	else if ((m_status&0x000F)==SPRITE_DASH)
	{
		GetObject(m_hdash,sizeof(BITMAP),&bmp);
		x=bmp.bmWidth/m_cx[(m_status&0x000F)];
		y=bmp.bmHeight/m_cy[(m_status&0x000F)];
		m_step%=x*y;
		hold=(HBITMAP)SelectObject(mdc,m_hdash);
	}
	else
	{
		//否则是碰撞后的状态
		GetObject(m_hcrash,sizeof(BITMAP),&bmp);
		x=bmp.bmWidth/m_cx[(m_status&0x000F)];
		y=bmp.bmHeight/m_cy[(m_status&0x000F)];
		m_step%=x*y;
		hold=(HBITMAP)SelectObject(mdc,m_hcrash);
	}	
	TransparentBlt(hdc,m_x,m_y,m_rx,m_ry,mdc,(m_step%x)*m_cx[(m_status&0x000F)],(m_step/x)*m_cy[(m_status&0x000F)],m_cx[(m_status&0x000F)],m_cy[(m_status&0x000F)],RGB(RRR,GGG,BBB));
	SelectObject(mdc,hold);
	DeleteDC(mdc);
}


void Sprite::KeyCheckAndReponse()
{
	if (GetAsyncKeyState('W')&0x8000&&(m_status&0x000F)==SPRITE_JUMP)
	{
		Slide();
	}
	else if ((GetAsyncKeyState(VK_SPACE)&0x8000)&&(m_status&0x000F)!=SPRITE_JUMP&&(m_status&0x000F)!=SPRITE_DOWN&&(m_status&0x000F)!=SPRITE_DROP&&(m_status&0x000F)!=SPRITE_SLIDE)
			Jump();
	else if (GetAsyncKeyState('S')&0x8000)
			Down();
	else if (GetAsyncKeyState('D')&0x8000)
			Dash();
}

int Sprite::CrashCheck(Obstacle & obj)
{
	if (obj.m_type==OBSTACLE_SOFT)
	{
		if (((m_x>=obj.m_x&&m_x<=obj.m_x+obj.m_rx)||(m_x+m_rx>=obj.m_x&&m_x+m_rx <= obj.m_x+obj.m_rx))&&m_y>=obj.m_y&&m_y<=obj.m_y+obj.m_ry)
		{
			//或者CRASH_RIGHTTOP
			obj.Break();
			return CRASH_TOP;
		}
		if (m_x+m_rx>=obj.m_x&&m_x+m_rx<=obj.m_x+obj.m_rx&&m_y>=obj.m_y&&m_y+m_ry<=obj.m_y+obj.m_ry)
		{
			obj.Break();
			return CRASH_RIGHT;
		}
		if(m_x<=obj.m_x&&m_x+m_cx[(m_status&0x000F)]>=obj.m_x&&m_y<=obj.m_y&&m_y+m_cy[(m_status&0x000F)]>=obj.m_y)
		{
			obj.Break();
			if ((m_status&0x000F)==SPRITE_JUMP)
			{
				return CRASH_RIGHTBOTTOM;
			}
			else
			{
				if ((m_status&0x000F)!=SPRITE_RUN)
				{
					return CRASH_BOTTOM;
				}
			}
		}
	}else if (obj.m_type==OBSTACLE_LAND||obj.m_type==OBSTACLE_HARD||obj.m_type==OBSTACLE_PLATFORM)
	{
		//TODO :找出此处将cy改完ry反而出错的原因
		if ((m_x+m_rx>=obj.m_x&&m_x+m_rx<=obj.m_x+obj.m_rx)
			&&!(m_y>=obj.m_y+obj.m_ry||m_y+m_ry<=obj.m_y))
		{
			if (m_v>0)
			{
				m_y=obj.m_y-m_ry+20;
				obj.m_type=OBSTACLE_PLATFORM;
				Run();
				return CRASH_BOTTOM;
			}
			else if (obj.m_type==OBSTACLE_HARD)
			{
				obj.Break();
				CrashRight();
				return CRASH_RIGHT;
			}
			else
			{
				return CRASH_RIGHTBOTTOM;
			}
		}

	}
// 	if (m_status==SPRITE_RUN)
// 		Drop();
	return NOCRASH;
}

void Sprite::GetNext()
{
	if ((m_status&0x000F)==SPRITE_CRASH&&m_step==3)
	{
		throw -1;
	}

	cnt++;
	if (cnt>=(RUNSPEEDMAX-m_showratio)/2)
	{
		cnt=0;
		if ((m_status&0x000F)==SPRITE_SLIDE)
		{
			m_y+=m_v;
			if (!(GetAsyncKeyState('W')&0x8000))
			{
				Drop();
			}
		}else if ((m_status&0x000F)==SPRITE_JUMP||(m_status&0x000F)==SPRITE_DOWN)
		{
			m_y+=m_v;
			m_v+=m_g;
		}
		
		if (m_v>=m_downspeed)
			m_status=SPRITE_DOWN;
		if (!((m_status&0x000F)==SPRITE_SLIDE&&m_step>0))
		{
			m_step++;
		}
		
		KeyCheckAndReponse();
	}
}

void Sprite::Jump()
{
	m_status=SPRITE_JUMP;
	m_v=m_jumpspeed;
	m_step=0;
}

void Sprite::Run()
{
	m_status=SPRITE_RUN;
	m_v=0;
	m_step=0;
}

void Sprite::Slide()
{
	m_status=SPRITE_SLIDE;
	m_v=m_slidespeed;
	m_step=0;
}

void Sprite::Down()
{
	m_status=SPRITE_DOWN;
	m_v=m_downspeed;
	m_step=0;
}

void Sprite::Dash()
{
	m_status=SPRITE_DASH;
	m_v=0;
	m_step=0;
}

void Sprite::Drop()
{
	m_status=SPRITE_JUMP;
	m_step=0;
}

void Sprite::CrashRight()
{
	PlaySound(TEXT("..\\Resource\\BK-Crashed-1_01.wav"),NULL,SND_FILENAME|SND_ASYNC);
	m_status=SPRITE_CRASH+CRASH_RIGHT;
	m_v=0;
	m_step=0;
}

void Sprite::CrashRightBottom()
{
	PlaySound(TEXT("..\\Resource\\BK-Crashed-1_01.wav"),NULL,SND_FILENAME|SND_ASYNC);
	m_status=SPRITE_CRASH+CRASH_RIGHTBOTTOM;
	m_v=m_jumpspeed;
	m_step=0;
}

int Sprite::GetStatus()
{
	return (m_status&0x000F);
}

Sprite::~Sprite()
{
	//TODO:
}