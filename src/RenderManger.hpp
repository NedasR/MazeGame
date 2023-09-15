#pragma once
#include <vector>
#include "StaticObject.hpp"
class RenderManger
{
	private:

	public:

	static std::vector<StaticObject*> m_renderList;

	static std::vector<StaticObject*> m_renderListProjectiles;

	RenderManger();

	static void addToRenderList(StaticObject* object);
};