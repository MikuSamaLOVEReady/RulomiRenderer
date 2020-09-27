#include "Texture.h"
//#include "vendor/stb_image/stb_image.h"
#include "stb_image/stb_image.h"


Texture::Texture(const std::string& path)
	:m_TextureID(0),m_FilePath(path),m_Localbuffer(nullptr),
	m_Witdth(0),m_Height(0),m_BPP(0)
{
	//opengl是从 左下角开始给的坐标0.0
	//但我们熟悉的图片加载是从左上角开始
	//这个函数帮我们旋转一哈
	stbi_set_flip_vertically_on_load(1);
	 
	 
	m_Localbuffer = stbi_load(path.c_str(), &m_Witdth, &m_Height, &m_BPP, 4);

	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);

	//当texture 尺寸比surface 大的时候
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//当texture 的尺寸比surface 小的时候
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//S  T相当于 纹理的xy坐标？
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	//internal fomat 第三个参数表示OPENGL 是如何存储 RGB 8后面的数字表示是多少位色彩8
	//第六个参数 format 表示的是我们提供的素材源的色彩格式
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Witdth, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Localbuffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	//把存放在内存中的 图形数据给释放了
	//因为再glTeximage的时候就把提供的资源转换成了opengl 存储在显存上理解的内容了
	if (m_Localbuffer)
		stbi_image_free(m_Localbuffer);

}

Texture::~Texture()
{
	//释放GPU上的资源
	glDeleteTextures(1, &m_TextureID);
}

void Texture::Bind(unsigned int slot) const
{
	//每个顶点 能有最多多少个 槽位用于纹理。
	glActiveTexture(GL_TEXTURE0+slot);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);

}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
