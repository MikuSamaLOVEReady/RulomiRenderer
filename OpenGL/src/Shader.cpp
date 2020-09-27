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



//Ƭ����ɫ���붥����ɫ���ı��뷽ʽ��ͬ�����������������
 unsigned int Shader::ComplieShader(unsigned int type, const std::string& source)
{
    //����һ����shader����
    unsigned int id = glCreateShader(type);
    /*
    �����ص�ǰ�ַ��������ַ���ַ������˵����c_str()��������һ��ָ������C�ַ�����ָ�볣����
    �����뱾string����ͬ��
    ����Ϊ����C���Լ��ݣ���C������û��string���ͣ�
    �ʱ���ͨ��string�����ĳ�Ա����c_str()��string����ת����C�е��ַ�����ʽ��*/
    const char* src = source.c_str();
    //��һ��������shader��һ��ʼ�ǿյģ� 
    //�ڶ��������� ����Ҫд���string ���� 
    //�������� Դ��string 
    //���ĸ� ��NULL ���Զ���ȡ��  ������������ ��ֹ��
    glShaderSource(id, 1, &src, NULL);
    //����shader
    glCompileShader(id);

    //������Ϣ����
    int result;
    //glGetshaderiv ���������ڷ��� shader object Īһ����Ϣ
    //���ﷵ�ر����Ƿ�ͨ��
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        //�鿴 shader obj����־����
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        //��ȡ shaderid  
        //�ڶ��������Ǵ��λ��log��buffer ��С
        //�������� Ҫ��ȡ��log ����
        //���ĸ���  ���ص�buffer��λ��
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
     //����hashmap����û��֮ǰ�Ѿ�get����uniformID 
     if (m_uniformLocation.find(unifor_name) != m_uniformLocation.end()) {
         return m_uniformLocation[unifor_name];
     }
    int location = glGetUniformLocation(m_RendererID, unifor_name.c_str());
    if (location == -1)
        std::cout << "Can't find the uniform" << unifor_name << std::endl;
    m_uniformLocation[unifor_name] = location;
    return location;
}

