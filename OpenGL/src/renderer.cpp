#include"renderer.h"
#include <iostream>
//清除其他函数的error 影响
static void GLClearError()
{
    //glGetError() 返回unsigned int 0 表示没有error 其他整数就表示有问题
    while (glGetError() != GL_NO_ERROR);
}

static bool  GLCheckError()
{
    while (GLenum error = glGetError())
    {
        //opengl 的 error enum 都是以16进制 的格式 所以要把decimal的 数字转换后再glew种查看
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
