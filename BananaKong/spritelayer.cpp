#include "spritelayer.h"



SpriteLayer::SpriteLayer(Sprite sprite,std::deque<std::deque<Obstacle> > objs,bool visible,int level):
Layer(visible,level),m_kong(sprite),
	m_objs(objs.begin(),objs.end())
{
	m_objnow=std::deque<Obstacle>(m_objs.front().begin(),m_objs.front().end());
}

void SpriteLayer::Draw(HDC hdc,RECT rect)
{
	m_kong.show(hdc);
	for (std::deque<Obstacle>::iterator iter=m_objnow.begin();iter!=m_objnow.end();++iter )
	{
		iter->Show(hdc);
	}
	m_rx=rect.right-rect.left;
	m_ry=rect.bottom-rect.top;
}

void SpriteLayer::GetNext()
{	
	try
	{
		m_kong.GetNext();
	}
	catch (...)
	{
		throw -1;
	}
	
	for (std::deque<Obstacle>::iterator iter=m_objnow.begin();iter!=m_objnow.end();++iter )
	{
		iter->GetNext();
	}

	//若最右边的物体已经到达屏幕内,则加入新一段的物体
		std::deque<Obstacle> que;
		if(m_objnow.empty()||m_objnow.back().InScreen(m_rx,m_ry))
		{
			srand(time(NULL));
			int randnum=rand()%m_objs.size();
			que=std::deque<Obstacle>(m_objs[randnum].begin(),m_objs[randnum].end());	//随机选取一段
			int dis=que.front().GetPosLeftX()-m_objnow.back().GetPosRightX();
			while (!que.empty())
			{
				que.front().MoveLeft(dis);
				m_objnow.push_back(que.front());
				que.pop_front();
			}
		}
	
		while (!m_objnow.empty()&&m_objnow.front().OutOfDate())
		{
			m_objnow.pop_front();
		}

	bool nocrash=true;
	int crash_type;
	for (std::deque<Obstacle>::iterator iter=m_objnow.begin();iter!=m_objnow.end();++iter )
	{
		crash_type=m_kong.CrashCheck(*iter);
		//if (m_kong.GetStatus()!=SPRITE_RUN&&crash_type==CRASH_BOTTOM)
		if (crash_type!=NOCRASH)
		{
			nocrash=false;
		}
	}
	if (nocrash&&m_kong.GetStatus()==SPRITE_RUN)
		m_kong.Drop();
		
}

bool SpriteLayer::Response(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//if (isVisible())
	//{
	//	m_kong.Response(hwnd,message,wParam,lParam);
	//}
	return false;
}

SpriteLayer::~SpriteLayer()
{

}