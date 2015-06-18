#ifndef SPRITELAYER
#define SPRITELAYER

#include <cstdlib>
#include <time.h>
#include <deque>
#include "layer.h"
#include "sprite.h"
#include "obstacle.h"
#include "commom.h"

class SpriteLayer:public Layer
{
public:
	//���캯��
	SpriteLayer(Sprite sprite,std::deque<std::deque<Obstacle> > objs,bool visible,int level);
	
	//��Ӧ��Ϣ
	bool Response(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	//��ͼ
	void Draw(HDC hdc,RECT rect);

	//����״̬
	void GetNext();

	//��������
	~SpriteLayer();

private:
	Sprite m_kong;						//����kong��
	std::deque<Obstacle> m_objnow;			//��ǰ��Ļ��Χ�ڵ�����
	std::deque<std::deque<Obstacle> > m_objs;		//���п��ܵ��������
	int m_rx,m_ry;						//��ǰ��Ļ��Χ,�ɵ�һ�λ�ͼʱȷ��
};

#endif