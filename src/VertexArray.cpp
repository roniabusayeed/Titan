#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    glGenVertexArrays(1, &m_id);
    glBindVertexArray(m_id);
    vb.Bind();
    
    auto attributes = layout.GetAttributes();
    size_t stride = layout.GetStride();
    size_t offset = 0;
    for (int i = 0, n = attributes.size(); i < n;i++)
    {
        glVertexAttribPointer(i, attributes[i].count, attributes[i].type,
         attributes[i].normalized, stride, (const void*)(offset));
        glEnableVertexAttribArray(i);

        offset += attributes[i].count * Attribute::GetSizeOfType(attributes[i].type);
    }
    vb.Unbind();
    glBindVertexArray(0);
}

void VertexArray::Bind()const
{
    glBindVertexArray(m_id);
}

void VertexArray::Unbind()const
{
    glBindVertexArray(0);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_id);
}