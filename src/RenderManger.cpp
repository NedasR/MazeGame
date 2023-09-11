#include "RenderManger.hpp"

std::vector<StaticObject*> RenderManger::m_renderList;

RenderManger::RenderManger()
{

}

void RenderManger::addToRenderList(StaticObject* object)
{
	m_renderList.push_back(object);
}
