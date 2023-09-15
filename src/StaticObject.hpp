#pragma once
#include "Object.hpp"
#include "Model.hpp"
#include "Shader.hpp"
#include <memory>
#include <map>

class StaticObject : public Object
{
	private:
	Model* m_modelMesh;
	glm::vec3 m_position;

	public:
	glm::mat4 m_scale;
	glm::mat4 m_rotation;
	glm::mat4 m_translate;

	public:

	std::shared_ptr<Shader> m_shader;

	StaticObject();

	void draw();

	void draw(Shader* shader);

	inline void setModel(Model& model) { m_modelMesh = &model;}

	void setRotation(glm::vec3 rotateAxis, float angle);

	void setPosition(glm::vec3 Pos);

	void setScale(glm::vec3 scale);

	void setShader(const std::string& shaderIndex);

	void setShader(const std::string& shaderIndex,std::map<std::string, std::shared_ptr<Shader>>& shaderList);

	glm::vec3 getPosition();

	void updateTransform();

	void updateMVP(glm::mat4 prespective, glm::mat4 view);
};