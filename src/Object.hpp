#pragma once
#include "Vendors/glm/glm.hpp"
#include "Vendors/glm/gtc/matrix_transform.hpp"
#include "Vendors/glm/gtc/type_ptr.hpp"

#include "Shader.hpp"

class Model;

class Object
{
private:

public:

	glm::mat4 m_transform;

	virtual void draw() = 0;
	virtual void draw(Shader* shader) = 0;
	virtual void setModel(Model& model) = 0;
	virtual void setRotation(glm::vec3 rotateAxis, float angle) = 0;
	virtual void setPosition(glm::vec3 Pos) = 0;
	virtual void setScale(glm::vec3 scale) = 0;
	virtual void setShader(const std::string& shaderIndex) = 0;
	virtual void setShader(const std::string& shaderIndex, std::map<std::string, std::shared_ptr<Shader>>& shaderList) = 0;
	virtual void updateTransform() = 0;
	virtual glm::vec3 getPosition() = 0;

	virtual void updateMVP(glm::mat4 prespective, glm::mat4 view, Shader* shader);
	virtual void updateMVP(glm::mat4 prespective, glm::mat4 view) = 0;
};