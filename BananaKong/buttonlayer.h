#ifndef COMMANDLAYER_H
#define COMMANDLAYER_H

#include "commom.h"
#include "layer.h"
#include "button.h"

class ButtonLayer:public Layer
{
public:
	//构造函数
	ButtonLayer();

	//绘图
	void Draw(HDC hdc,RECT rect);

	//消息响应
	bool Response(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	//状态更新
	void GetNext();

	//析构函数
	~ButtonLayer();
private:
	
}

#endif