#include "Object.hpp"

void Object::updateMVP(Shader* shader, glm::mat4 prespective, glm::mat4 view)
{
    shader->BindShader();
    shader->setUniformvmatrix4f("model", m_transform);
    shader->setUniformvmatrix4f("prespective", prespective);
    shader->setUniformvmatrix4f("view", view);
}