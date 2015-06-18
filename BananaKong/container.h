/*!
 * \file container.h
 * \date 2015/05/29 19:14
 *
 * \author Lincifer
 * Contact: linlihao159@gmail.com
 *
 * \brief ��ͷ�ļ�����Container��
 *
 *Container���ɶ��Layer�����,������Ϣ�ַ�����ͬ��ͼ���Լ�ˢ��ͼ��
 *�ַ���Ϣʱ�ߵȼ�ͼ������
*/
#ifndef CONTAINER_H

#define CONTAINER_H

#include <vector>
#include <algorithm>
#include "layer.h"
#include "imagelayer.h"
#include "spritelayer.h"
#include "commom.h"

using namespace std;

class Container
{
public:
	//���캯��
	Container();

	//���캯��
	Container(HWND hwnd);

	//����������Ӧ�Ĵ��ھ��
	void SetHandle(HWND hwnd);

	//������Container�����ͼ��
	void AddLayer(Layer * layer);

	//���ڶ�ͼ�㰴��������
	void SortLayer();

	Layer * GetTop();

	//���𽫽��յ�����Ϣ�������·ַ���ÿһ��ͼ��
	bool DispatchMSG(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	//ˢ������ͼ�����ʾ
	void DrawAll();

	//��������ͼ���״̬
	void Next();

	//���ͼ��
	void Clear();

	//�˶��ٶȼӿ�
	void SpeedUp();

	//��������,�ͷ���Դ
	~Container();
private:
	//Container��Ӧ�Ĵ��ھ��
	HWND m_hwnd;

	//���ڴ���ͼ��ָ��
	vector < Layer * > Layers; 
};

#endif