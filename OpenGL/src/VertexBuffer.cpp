#include "VertexBuffer.h"

#include "renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    glGenBuffers(1, &m_RendererID);
    //ѡ���Ӧbuffer
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    //Ϊbuffer �����Ӧ����ֵ ���������������cpu�ϵģ�

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
