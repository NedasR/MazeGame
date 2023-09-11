#include "ElementArray.hpp"
#include <glew.h>

ElementArray::ElementArray(const unsigned int* data, const unsigned int count) 
:m_count(count)
{
    glGenBuffers(1, &m_rendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

ElementArray::ElementArray()
{
    m_count = 0;
}

ElementArray::~ElementArray()
{
    glDeleteBuffers(1,&m_rendererID);
}

void ElementArray::createElementArray(const unsigned int* data, const unsigned int count)
{
    m_count = count;
    glGenBuffers(1, &m_rendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

void ElementArray::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
}

void ElementArray::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
