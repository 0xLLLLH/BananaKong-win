/*!
 * \file imagelayer.h
 * \date 2015/05/29 19:15
 *
 * \author Lincifer
 * Contact: linlihao159@gmail.com
 *
 * \brief ��ͷ�ļ�����ImageLayer�������
 *
 *ImageLayer����Layer������
 *��Ҫ���ڶ�����ͼ�����ʾ
 *��Ӧ�ĳ�Ա����ʵ����ImageLayer.cpp��
 *ʹ��ʱע��������
 *
*/

#ifndef IMAGE_CLASS_LAYER_H

#define IMAGE_CLASS_LAYER_H

#include <windows.h>
#include <vector>
#include <deque>
#include <cstdlib>
#include <time.h>
#include "layer.h"
#include "commom.h"

using namespace std;

class ImageLayer:public Layer
{
public:
	// ImageLayer��Ĺ��캯��
	ImageLayer(
		vector< HBITMAP > bmps,
		vector<vector<int> >follow,
		int cx,
		int cy,
		bool visible,
		int level,
		int speed=0);			

	//�ú����������
	virtual void Draw(HDC hdc,RECT rect);

	//�������µ���һ״̬
	virtual void GetNext();

	//��Ϣ��Ӧ����
	virtual bool Response(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
 
	~ImageLayer();
private:
	vector<HBITMAP> m_bmps;			// ImageLayer��Ӧ��λͼ
	vector<vector<int> >m_follow;	// ÿ��λͼ��ɽӵ�λͼ��m_bmps�е�λ��k
	deque<int> m_showqueue;			// ��ǰ��ʾλͼ��m_bmps�е�λ��
	int m_cx,m_cy;					// ͼ���С
	int m_speed;					// ͼ���ƶ��ٶ�(����Ϊ������λ����),Ĭ��Ϊ0(��ֹ)
	int m_startpos;					// ͼ����ʾ��ʼλ��
	int m_width;					// ��ǰ������λͼ���ܿ��
};

#endif