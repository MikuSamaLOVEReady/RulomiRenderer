#pragma once

#include <string>
#include<unordered_map>
#include"glm/glm.hpp"


//return mutiple type
struct ShaderProgramSource {
	std::string vertexSource;
	std::string fragmentSoruce;
};

class Shader {
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_uniformLocation;
public:
	//先ParseShader -》CreateShader-》ComplieShader
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void UnBind() const;

	//让shader 理解texture 的sloat
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

	

private:
	ShaderProgramSource ParseShader(const std::string& filepath);
	 int GetUniformLocation(const std::string& unifor_name);
	unsigned int ComplieShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

};