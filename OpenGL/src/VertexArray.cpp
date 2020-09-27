#include "VertexArray.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_RendererID);

}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout layout)
{
	//绑定VAO  ------》 其实VAO的作用就是让VBO的数据与属性解释 打包化
	Bind();
	//绑定对应VB 
	vb.Bind();
	//取出 一个VB的 所有解释指针 即解释每个属性
	const auto& elements = layout.GetElements();
	//一个一个属性解释
	unsigned int offset = 0;
	for (unsigned int i = 0;i < elements.size(); i++) {
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(	i , element.count, element.type, element.normalized
			, layout.GetStride(),(const void*) offset);
		offset += element.count*VertexBufferElement::GetSizeOfType(element.type);
	}


}

void VertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::UnBind() const
{
	glBindVertexArray(0);
}
