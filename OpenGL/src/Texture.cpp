#include "Texture.h"
//#include "vendor/stb_image/stb_image.h"
#include "stb_image/stb_image.h"


Texture::Texture(const std::string& path)
	:m_TextureID(0),m_FilePath(path),m_Localbuffer(nullptr),
	m_Witdth(0),m_Height(0),m_BPP(0)
{
	//opengl�Ǵ� ���½ǿ�ʼ��������0.0
	//��������Ϥ��ͼƬ�����Ǵ����Ͻǿ�ʼ
	//���������������תһ��
	stbi_set_flip_vertically_on_load(1);
	 
	 
	m_Localbuffer = stbi_load(path.c_str(), &m_Witdth, &m_Height, &m_BPP, 4);

	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);

	//��texture �ߴ��surface ���ʱ��
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//��texture �ĳߴ��surface С��ʱ��
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//S  T�൱�� �����xy���ꣿ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	//internal fomat ������������ʾOPENGL ����δ洢 RGB 8��������ֱ�ʾ�Ƕ���λɫ��8
	//���������� format ��ʾ���������ṩ���ز�Դ��ɫ�ʸ�ʽ
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Witdth, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Localbuffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	//�Ѵ�����ڴ��е� ͼ�����ݸ��ͷ���
	//��Ϊ��glTeximage��ʱ��Ͱ��ṩ����Դת������opengl �洢���Դ�������������
	if (m_Localbuffer)
		stbi_image_free(m_Localbuffer);

}

Texture::~Texture()
{
	//�ͷ�GPU�ϵ���Դ
	glDeleteTextures(1, &m_TextureID);
}

void Texture::Bind(unsigned int slot) const
{
	//ÿ������ ���������ٸ� ��λ��������
	glActiveTexture(GL_TEXTURE0+slot);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);

}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
