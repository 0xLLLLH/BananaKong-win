/*!
 * \file layer.h
 * \date 2015/05/29 19:12
 *
 * \author Lincifer
 * Contact: linlihao159@gmail.com
 *
 * \brief ��ͷ�ļ�����Layer�������
 *
 *Layer�಻�������Ļ��ƺͽ���
 *����������ͼ����Ļ���
 *�߼����Layer�����ڵͼ������
 *
*/

#ifndef CLASS_LAYER_H

#define CLASS_LAYER_H

#include <windows.h>


class Layer
{
public:
	//���캯��,ͨ����ʼ�ɼ��Ժͼ�����ͼ��
	Layer(bool visible,int level);

	//�ýӿ������޸�ͼ��ɼ���
	void SetVisible(bool visible);

	//�ýӿ������޸�ͼ����ʾ����
	void SetLevel(int level);

	//���麯��,����ͼ��Ļ���ˢ��,����ʵ��������������
	virtual void Draw(HWND hwnd)=0;

	//���麯��,����ͼ�����Ϣ����Ӧ,����true��ʾ��Ϣ��Ӧ��ֹ,����false��ʾ����Ӧ�������Ӧ
	//�������������е�WndProc()�Լ�Container�е�DispatchMSG()����һ��
	virtual bool Response(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)=0;
	
	//���ڱȽ�ͼ�����ȼ��ĺ���
	//����Layer�ǳ�����,���Դ���������ָ����бȽ�
	friend bool LayerCmp(Layer * a,Layer * b);

	//���麯��,ִ��ͼ������ʱ����Դ�ͷ�
	virtual ~Layer();
private:
	//��ʾͼ��Ŀɼ���,ֵΪfalseʱ���ٽ��л���,ֱ����ֵΪtrue
	bool m_visible;

	//��ʾͼ����ʾ����,�߼���ͼ�㸲���ڵͼ���ͼ���Ϸ�
	int m_level;
};



#endif