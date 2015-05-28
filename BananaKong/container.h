/**
*该头文件定义Container类
*Container类由多个Layer类组成,负责将消息分发给不同的图层以及刷新图层
*分发消息时高等级图层优先
*/
#ifndef CONTAINER_H

#define CONTAINER_H

#include <vector>
#include "layer.h"

class Container
{
public:
	///构造函数
	Container();

	///负责将接收到的消息自上向下分发给每一个图层
	void DispatchMSG(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	///用于在Container中添加图层
	void AddLayer(Layer * layer);

	///用于对图层按级别排序
	void SortLayer();

	///刷新所有图层
	void DrawAll();

	///析构函数,释放资源
	~Container();
private:
	///用于储存图层指针
	vector <Layer *> Layers; 
};

#endif