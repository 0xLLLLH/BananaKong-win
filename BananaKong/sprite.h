#ifndef _SPRITE_H

#define _SPRITE_H


#include <windows.h>
#include <vector>
#include "obstacle.h"
#include "commom.h"


//��־sprite��״̬,����ÿһ��״̬,Ӧ���ж�Ӧ��λͼ����
#define SPRITE_RUN		0x0000
#define SPRITE_JUMP		0x0001
#define SPRITE_SLIDE	0x0002
#define SPRITE_DOWN		0x0003
#define SPRITE_DASH		0x0004
#define SPRITE_CRASH	0x0005
#define SPRITE_DROP		0x0006

//��ײ״̬
#define CRASH_TOP				0x0010
#define CRASH_RIGHTTOP			0x0020
#define CRASH_RIGHT				0x0030
#define CRASH_RIGHTBOTTOM		0x0040
#define CRASH_BOTTOM			0x0050
#define NOCRASH					0x0060

class Sprite
{
public:
	//���캯��
	Sprite(int x,int y,int rx,int ry,int cx[7],int cy[7],
		HBITMAP hrun,
		HBITMAP hjump,
		HBITMAP hslide,
		HBITMAP hdown,
		HBITMAP hdash,
		HBITMAP hcrash,
		HBITMAP hparachute,
		int g,int jumpspeed,int slidespeed,int downspeed,int showratio);

	//��ʾ
	void show(HDC hdc);

	void KeyCheckAndReponse();

	int GetStatus();

	// �Կ�����Ϣ������Ӧ
	// W��Ծ,S����,D���
	// ��ס�ո񽫽��л���
	//bool Response(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Jump();

	void Run();

	void Slide();

	void Down();

	void Dash();

	void Drop();

	void CrashRight();

	void CrashRightBottom();

	//����״̬
	void GetNext();

	//����Ƿ��������ײ
	//�����soft���͵����巢���Ӵ�,������ײ����,���򷵻�-1
	int CrashCheck(Obstacle & obj);

	//��������
	~Sprite();
private:
	int m_x,m_y;		//��ʾλ������
	int m_rx,m_ry;		//��ʾ��С
	int m_cx[7],m_cy[7];//ͼƬ��С
	int m_step;			//��ǰ״̬�µĲ���
	int m_status;		//��־���鵱ǰ��״̬
	HBITMAP m_hrun;		//�ܶ�λͼ
	HBITMAP m_hjump;		//��Ծλͼ
	HBITMAP m_hslide;		//����λͼ
	HBITMAP m_hdown;		//����λͼ
	HBITMAP m_hdash;		//���λͼ
	HBITMAP m_hcrash;		//��ײ����λͼ
	HBITMAP m_hparachute;		//����ɡ
	int m_v;				//�ٶ�,С��0Ϊ����,�˶�ʱ�������ٶ�Ӱ��
	int m_g;				//�������ٶ�,����0
	int m_jumpspeed;		//��Ծʱ���ϵ��ٶ�
	int m_slidespeed;		//����ʱ���ٶ�
	int m_downspeed;		//����������ٶ�,�������ٶȴﵽ���������ٶ�ʱ,״̬����ΪSPRITE_DOWN
	int m_showratio;		//ˢ����
	DWORD cnt;				//��ʱ��
};

#endif