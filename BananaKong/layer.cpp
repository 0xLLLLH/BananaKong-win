/*!
 * \file layer.cpp
 * \date 2015/05/29 19:34
 *
 * \author Lincifer
 * Contact: linlihao159@gmail.com
 *
 * \brief ���ļ�����Layer���Ա������ʵ��
 *

*/
#include "layer.h"

Layer::Layer(bool visible,int level)
{
	m_visible=visible;
	m_level=level;
}

void Layer::SetVisible(bool visible)
{
	m_visible=visible;
}

void Layer::SetLevel(int level)
{
	m_level=level;
}

 bool LayerCmp(Layer * a,Layer * b)
{
	return (a->m_level)>(b->m_level);
}

 Layer::~Layer()
 {
	 //TODO:�ڴ˴����Layer�����������ʵ��
 }