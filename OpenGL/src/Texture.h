#pragma once
#include "renderer.h"

class Texture {

private:
	unsigned int m_TextureID;
	std::string m_FilePath;
	unsigned char* m_Localbuffer;
	int m_Witdth, m_Height, m_BPP;
public:
	Texture(const std::string& path);
	~Texture();

	//给定 哪个 slot ID 是想让textre 绑定的。
 	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return m_Witdth; }
	inline int GetHeight() const { return m_Height; }


};