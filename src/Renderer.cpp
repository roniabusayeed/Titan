#include "Renderer.h"
#include <glad/glad.h>

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)const
{
    va.Bind();
    ib.Bind();
    shader.Bind();
    glDrawElements(GL_TRIANGLES, ib.Count(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Clear()const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}