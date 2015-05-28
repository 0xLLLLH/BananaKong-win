/**
*��ͷ�ļ�����Container��
*Container���ɶ��Layer�����,������Ϣ�ַ�����ͬ��ͼ���Լ�ˢ��ͼ��
*�ַ���Ϣʱ�ߵȼ�ͼ������
*/
#ifndef CONTAINER_H

#define CONTAINER_H

#include <vector>
#include "layer.h"

class Container
{
public:
	///���캯��
	Container();

	///���𽫽��յ�����Ϣ�������·ַ���ÿһ��ͼ��
	void DispatchMSG(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	///������Container�����ͼ��
	void AddLayer(Layer * layer);

	///���ڶ�ͼ�㰴��������
	void SortLayer();

	///ˢ������ͼ��
	void DrawAll();

	///��������,�ͷ���Դ
	~Container();
private:
	///���ڴ���ͼ��ָ��
	vector <Layer *> Layers; 
};

#endif