#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include <cstddef>

class IndexBuffer
{
private:
    size_t m_count;
    unsigned int m_id;
public:
    IndexBuffer(unsigned int* indices, size_t count);
    void Bind()const;
    void Unbind()const;
    size_t Count()const;
    ~IndexBuffer();
};

#endif  // INDEX_BUFFER_H