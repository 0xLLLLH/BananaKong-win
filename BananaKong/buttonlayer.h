#ifndef COMMANDLAYER_H
#define COMMANDLAYER_H

#include "commom.h"
#include "layer.h"
#include "button.h"

class ButtonLayer:public Layer
{
public:
	//���캯��
	ButtonLayer();

	//��ͼ
	void Draw(HDC hdc,RECT rect);

	//��Ϣ��Ӧ
	bool Response(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	//״̬����
	void GetNext();

	//��������
	~ButtonLayer();
private:
	
}

#endif