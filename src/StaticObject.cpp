#include "StaticObject.hpp"
#include "Game.hpp"
#include "Vendors/glm/glm.hpp"
#include "Vendors/glm/gtc/matrix_transform.hpp"
#include "Vendors/glm/gtc/type_ptr.hpp"

void StaticObject::draw(Shader* shader)
{
	m_modelMesh->draw(shader);
}

void StaticObject::setRotation(glm::vec3 rotateAxis, float angle)
{
	m_rotation = glm::rotate(glm::mat4(1.0f), angle, rotateAxis);
}

void StaticObject::setPosition(glm::vec3 Pos)
{
	m_position = Pos;
	m_translate = glm::translate(glm::mat4(1.0f), Pos);
}

void StaticObject::setScale(glm::vec3 scale)
{

	m_scale = glm::scale(glm::mat4(1.0f), scale);
}

void StaticObject::setShader(const std::string& shaderIndex)
{
	setShader(shaderIndex,Game::m_shaders);
}

void StaticObject::setShader(const std::string& shaderIndex, std::map<std::string, std::shared_ptr<Shader>>& shaderList)
{
	m_shader = shaderList[shaderIndex];
}

glm::vec3 StaticObject::getPosition()
{
	return m_position;
}

void StaticObject::updateTransform()
{
	m_transform = m_translate * m_rotation * m_scale;
}

void StaticObject::updateMVP(glm::mat4 prespective, glm::mat4 view)
{
	m_shader->BindShader();
	m_shader->setUniformvmatrix4f("model", m_transform);
	m_shader->setUniformvmatrix4f("prespective", prespective);
	m_shader->setUniformvmatrix4f("view", view);
}

StaticObject::StaticObject()
{
	m_position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_modelMesh = nullptr;
	m_transform = glm::mat4(1.0f);

	m_scale		= glm::mat4(1.0f);
	m_rotation	= glm::mat4(1.0f);
	m_translate	= glm::mat4(1.0f);
}

void StaticObject::draw()
{
	draw(m_shader.get());
}
