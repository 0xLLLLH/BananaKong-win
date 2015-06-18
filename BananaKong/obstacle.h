#ifndef _OBSTACLE_H
#define _OBSTACLE_H

#include "commom.h"
#include <windows.h>
#include <vector>

//����״̬
#define OBSTACLE_NORM		0x0000
#define OBSTACLE_BREAKING	0x0001
#define OBSTACLE_BROKEN		0x0002

//��������
#define OBSTACLE_SOFT		0x0001		//��������,��ײʱ����
#define OBSTACLE_HARD		0x0002		//��Ӳ����,��ײʱ����
#define OBSTACLE_WATER		0x0003		//ˮ,��ײʱ����
#define OBSTACLE_PLATFORM	0x0004		//ƽ̨
#define OBSTACLE_LAND		0x0005		//����

class Obstacle 
{
public:
	//����SpriteΪObstacle����Ԫ��
	friend class Sprite;

	//���캯��
	Obstacle(int x,int y,int rx,int ry, int cx, int cy,int speed, HBITMAP hbmp,int type);
	
	//���ƹ��캯��
	Obstacle(const Obstacle & obs);

	//��ʾ
	void Show(HDC hdc);

	//��ȡ��߽�
	int GetPosLeftX();

	//��ȡ�ұ߽�
	int GetPosRightX();

	//����dis�ľ���
	void MoveLeft(int dis);

	//״̬����
	void GetNext();

	//�������鼰״̬�ı�
	void Break();

	//�ж������Ƿ����
	bool OutOfDate();

	//�Ƿ�����Ļ��
	bool InScreen(int rx,int ry);

	//��������
	~Obstacle();
private:
	int m_x,m_y;					//��ʾλ��
	int m_rx,m_ry;					//��ʾ��С
	int m_cx,m_cy;					//ͼƬ��С
	int m_speed;					//�ƶ��ٶ�,����Ϊ��
	HBITMAP m_hbmp;					//�������������ͼƬ
	int m_step;						//��ǰͼƬ����
	int m_status;					//���嵱ǰ״̬
	int m_type;						//��������
};

#endif