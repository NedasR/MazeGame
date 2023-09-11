#include "VertexBuffer.hpp"
#include <glew.h>

VertexBuffer::VertexBuffer(const void* data, const int size)
{
    glGenBuffers(1, &m_rendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer()
{

}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1,&m_rendererID);
}

void VertexBuffer::createVertexBuffer(const void* data, const int size)
{
    glGenBuffers(1, &m_rendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
}

void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
