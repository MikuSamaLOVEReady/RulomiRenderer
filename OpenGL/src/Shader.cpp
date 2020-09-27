#include "Shader.h"

#include<iostream>
#include "renderer.h"
#include <fstream>
#include<string>
#include<sstream>




 ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);
    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };


    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            ss[(int)type] << line << '\n';
        }
    }
    return { ss[0].str() , ss[1].str() };

}



//片段着色器与顶点着色器的编译方式相同，这里抽象出这个方法
 unsigned int Shader::ComplieShader(unsigned int type, const std::string& source)
{
    //创建一个空shader容器
    unsigned int id = glCreateShader(type);
    /*
    它返回当前字符串的首字符地址。换种说法，c_str()函数返回一个指向正规C字符串的指针常量，
    内容与本string串相同。
    这是为了与C语言兼容，在C语言中没有string类型，
    故必须通过string类对象的成员函数c_str()把string对象转换成C中的字符串样式。*/
    const char* src = source.c_str();
    //第一个参数是shader（一开始是空的） 
    //第二个参数是 我们要写入的string 数量 
    //第三个是 源码string 
    //第四个 给NULL 将自动读取到  第三个参数的 终止符
    glShaderSource(id, 1, &src, NULL);
    //编译shader
    glCompileShader(id);

    //错误消息反馈
    int result;
    //glGetshaderiv 作用是用于返回 shader object 莫一项信息
    //这里返回编译是否通过
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        //查看 shader obj的日志长度
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        //获取 shaderid  
        //第二个参数是存放位置log的buffer 大小
        //第三个是 要读取的log 长度
        //第四个是  返回的buffer的位置
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to complie " <<
            (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
            << "shader" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;

}


 unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = ComplieShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = ComplieShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}





Shader::Shader( const std::string& filepath)
	:m_FilePath(filepath),m_RendererID(0)
{
    ShaderProgramSource source = ParseShader(filepath);
    m_RendererID = CreateShader(source.vertexSource, source.fragmentSoruce);

}

Shader::~Shader()
{
    glDeleteProgram(m_RendererID);
}

void Shader::Bind() const
{
    glUseProgram(m_RendererID);
}

void Shader::UnBind() const
{
    glUseProgram(0);
}

void Shader::SetUniform1i(const std::string& name, int value)
{
    glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform1f(const std::string& name, float value)
{
    glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);

}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    glUniformMatrix4fv(GetUniformLocation(name),1,GL_FALSE,&matrix[0][0]);

}

 int Shader::GetUniformLocation(const std::string& unifor_name)
{
     //查找hashmap找有没有之前已经get到的uniformID 
     if (m_uniformLocation.find(unifor_name) != m_uniformLocation.end()) {
         return m_uniformLocation[unifor_name];
     }
    int location = glGetUniformLocation(m_RendererID, unifor_name.c_str());
    if (location == -1)
        std::cout << "Can't find the uniform" << unifor_name << std::endl;
    m_uniformLocation[unifor_name] = location;
    return location;
}

