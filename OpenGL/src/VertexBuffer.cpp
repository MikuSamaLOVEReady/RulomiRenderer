#include "VertexBuffer.h"

#include "renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    glGenBuffers(1, &m_RendererID);
    //选择对应buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    //为buffer 填充相应的数值 （这个数据则是在cpu上的）

    glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), data, GL_STATIC_DRAW);


}

VertexBuffer::~VertexBuffer()
{

    glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::UnBind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
