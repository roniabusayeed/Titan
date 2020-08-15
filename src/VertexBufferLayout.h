#ifndef VERTEX_BUFFER_LAYOUT_H
#define VERTEX_BUFFER_LAYOUT_H
#include <cstddef>
#include <cassert>
#include <iostream>
#include <vector>

#include <glad/glad.h>

struct Attribute
{
    size_t count;
    unsigned int type;
    unsigned char normalized;

    inline static size_t GetSizeOfType(unsigned int type)
    {
        switch (type)
        {
            case GL_FLOAT:              return sizeof(GLfloat);
            case GL_UNSIGNED_INT:       return sizeof(GLuint);
            case GL_UNSIGNED_BYTE:      return sizeof(GLubyte);
        }

        // Add support for more types.
        assert(false);
        return 0;
    }
};

class VertexBufferLayout
{
private:
    size_t m_stride;
    std::vector<Attribute> m_attributes;
public:
    VertexBufferLayout();
    inline size_t GetStride()const { return m_stride; }
    inline std::vector<Attribute> GetAttributes()const { return m_attributes; }

    template <typename T>
    inline void Push(size_t count)
    {
        assert(false);
    }

    // gcc seems to have problem with this type of specialization.
    // But VC++ and clang works fine.
    template <>
    inline void Push<float>(size_t count)
    {
        m_attributes.push_back({ count, GL_FLOAT, GL_FALSE });
        m_stride += count * Attribute::GetSizeOfType(GL_FLOAT);
    }
    
    // Add template specializations of Push for other types.
};

#endif  // VERTEX_BUFFER_LAYOUT_H