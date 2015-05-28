/**
*
*��ͷ�ļ�����Layer�������
*���������Ļ��ƺͽ���
*�ɴ���������PanelLayer���ImageLayer��
*�߼����Layer�����ڵͼ������
*
*/

#ifndef CLASS_LAYER_H

#define CLASS_LAYER_H

#include <windows.h>

class Layer
{
public:
	///���캯��,ͨ����ʼ�ɼ��Ժͼ�����ͼ��
	Layer(bool visible,int level);

	///�ýӿ������޸�ͼ��ɼ���
	void SetVisible(bool visible);

	///�ýӿ������޸�ͼ����ʾ����
	void SetLevel(int level);

	///���麯��,����ͼ��Ļ���ˢ��,����ʵ��������������
	virtual void Draw()=0;

	///���麯��,����ͼ�����Ϣ����Ӧ
	///�������������е�WndProc()�Լ�Container�е�DispatchMSG()����һ��
	virtual bool Response(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)=0;
	
	///���麯��,ִ��ͼ������ʱ����Դ�ͷ�
	virtual ~Layer()=0;
private:
	///��ʾͼ��Ŀɼ���,ֵΪfalseʱ���ٽ��л���,ֱ����ֵΪtrue
	bool m_visible;

	///��ʾͼ����ʾ����,�߼���ͼ�㸲���ڵͼ���ͼ���Ϸ�
	int m_level;
};

#endif