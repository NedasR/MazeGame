#include "Projectile.hpp"
#include "RenderManger.hpp"
#include <iostream>
#include <glew.h>
#include <GLFW/glfw3.h>
#include <cmath>

void Projectile::setProjectile(StaticObject* projectile)
{
	m_projectileModel = std::make_shared<StaticObject>(*projectile);
}

void Projectile::projectileUpdate()
{
	bool noting = false;
	int saved = 0;
	for (int i = 0; i < m_projectiles.size(); i++)
	{
		glm::vec3 current = m_projectiles[i].m_projectile.get()->getPosition();
		if (current.x >= 100.0f || current.x <= -100.0f ||
			current.y >= 100.0f || current.y <= -100.0f ||
			current.z >= 100.0f || current.z <= -100.0f)
		{
			m_projectiles.erase(m_projectiles.begin() + i);
			RenderManger::m_renderListProjectiles.erase(RenderManger::m_renderListProjectiles.begin() + i);
			// need to remove from render list
			//i--;
			continue;
		}
		glm::vec3 diraction = m_projectiles[i].m_diraction;
		m_projectiles[i].m_projectile.get()->setPosition(current + diraction);
	}
}

void Projectile::spawnProjectile(glm::vec3 direction, glm::vec3 pos, GLFWwindow* window)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		ProjectileInfo chach;
		chach.m_diraction = direction;
		m_projectileModel->setPosition(pos);
		chach.m_projectile = std::make_shared<StaticObject>(*m_projectileModel);

		m_projectiles.push_back(chach);
		glm::mat4 angle(glm::quatLookAt(direction,glm::vec3(0.0f, 1.0f, 0.0f)));
		angle = glm::rotate(angle,glm::radians(90.f), glm::vec3(0.0f, 1.0f, 0.0f));
		m_projectiles.back().m_projectile.get()->m_rotation = angle;
		RenderManger::m_renderListProjectiles.push_back(chach.m_projectile.get());
	}
}