#include "Object.hpp"

void Object::updateMVP(glm::mat4 prespective, glm::mat4 view, Shader* shader)
{
    shader->BindShader();
    shader->setUniformvmatrix4f("model", m_transform);
    shader->setUniformvmatrix4f("prespective", prespective);
    shader->setUniformvmatrix4f("view", view);
}