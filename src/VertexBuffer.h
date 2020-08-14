#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H
#include <cstddef>

class VertexBuffer
{
private:
    unsigned int m_id;
public:
    VertexBuffer(const float* vertices, size_t size);
    void Bind()const;
    void Unbind()const;
    ~VertexBuffer();
};

#endif  // VERTEX_BUFFER_H