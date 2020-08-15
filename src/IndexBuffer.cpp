#include "IndexBuffer.h"

#include <glad/glad.h>

IndexBuffer::IndexBuffer(unsigned int* indices, size_t count)
    : m_count(count)
{
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::Bind()const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void IndexBuffer::Unbind()const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

size_t IndexBuffer::Count()const
{
    return m_count;
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_id);
}
