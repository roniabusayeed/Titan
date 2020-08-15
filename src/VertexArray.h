#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
private:
    unsigned int m_id;
public:
    VertexArray(const VertexBuffer& vb, const VertexBufferLayout& layout);
    void Bind()const;
    void Unbind()const;
    ~VertexArray();
};

#endif  // VERTEX_ARRAY_H