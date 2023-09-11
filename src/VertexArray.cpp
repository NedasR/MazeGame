#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include <glew.h>
#include "Render.hpp"

VertexArray::VertexArray()
{
    GLCALL(glGenVertexArrays(1, &m_renderID));
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_renderID);
}

void VertexArray::makeID()
{
    GLCALL(glGenVertexArrays(1, &m_renderID));
}

void VertexArray::addBuffer(const VertexBuffer& vb, VertexBufferLayout& Layout)
{
    Bind();
    vb.bind();
    const std::vector<VertexBufferElements>& elements = Layout.getElements();
    unsigned int offset = 0;
    for (int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        GLCALL(glEnableVertexAttribArrayARB(i));
        GLCALL(glVertexAttribPointer(i, element.m_count, element.m_type, element.m_normalized, Layout.getStride(), (void*)offset));
        offset += element.m_count * VertexBufferElements::getSizeOfType(element.m_type);
    }
    vb.unbind();
    Unbind();
}

void VertexArray::Bind() const
{
    GLCALL(glBindVertexArray(m_renderID));
}

void VertexArray::Unbind() const
{ 
    GLCALL(glBindVertexArray(0));
}
