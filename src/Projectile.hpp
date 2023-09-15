#pragma once
#include "StaticObject.hpp"
#include <vector>
#include "Model.hpp"
#include <memory>

struct ProjectileInfo
{
	std::shared_ptr<StaticObject> m_projectile;
	glm::vec3 m_diraction;
};

class Projectile : public StaticObject
{
private:

	std::shared_ptr<StaticObject> m_projectileModel;

public:

	std::vector<ProjectileInfo> m_projectiles;

	void setProjectile(StaticObject* projectile);

	void projectileUpdate();

	void spawnProjectile(glm::vec3 diraction, glm::vec3 pos, GLFWwindow* m_window);
};