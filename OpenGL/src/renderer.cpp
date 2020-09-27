#include"renderer.h"
#include <iostream>
//�������������error Ӱ��
static void GLClearError()
{
    //glGetError() ����unsigned int 0 ��ʾû��error ���������ͱ�ʾ������
    while (glGetError() != GL_NO_ERROR);
}

static bool  GLCheckError()
{
    while (GLenum error = glGetError())
    {
        //opengl �� error enum ������16���� �ĸ�ʽ ����Ҫ��decimal�� ����ת������glew�ֲ鿴
        std::cout << "[OpenGL Error] (" << error << ")" << std::endl;
        return false;
    }
    return true;
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    va.Bind();
    ib.Bind();
    shader.Bind();
    glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);

}

void Renderer::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}
