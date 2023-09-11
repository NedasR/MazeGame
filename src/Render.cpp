#include "Render.hpp"
#include <iostream>
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "ElementArray.hpp"

void GlClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLPrintError(const char* function, int line, const char* filepath)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OPENGL ERROR]" << " LINE : " << line << " error: " << error << " filepath: " << filepath << std::endl;
        return true;
    }
	return false;
}

void Renderer::draw(VertexArray& vertexArray, ElementArray& indexBuffer, Shader& shader)
{

    vertexArray.Bind();
    indexBuffer.Bind();
    shader.BindShader();
    GLCALL(glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::drawArrays(VertexArray& vertexArray, Shader& shader)
{
    vertexArray.Bind();
    shader.BindShader();
    glDrawArrays(GL_TRIANGLES,0,36);
    glBindVertexArray(0);
}
