#pragma once
#include "AI.hpp"
#include <vector>
#include "StaticObject.hpp"

class Mob : public AI, public StaticObject
{
	private:

	glm::ivec2 m_PostionInMaze;

	std::vector<glm::vec3> m_path;

	public:

	void goToPoint();

	void findPath();

};