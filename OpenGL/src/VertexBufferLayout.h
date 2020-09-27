#pragma once
#include <vector>
#include "renderer.h"

//每一个属性 是一个 element
struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type) {
		switch (type)
		{
				case GL_FLOAT:                  return 4;
				case GL_UNSIGNED_INT:    return 4;
				case GL_UNSIGNED_BYTE:  return 1;

		}
		return 0;
	}

};


class VertexBufferLayout {
private:
	//这个数组中放的是每一种VB 所对应的所有属性解释 这里
	//只是一个容器的作用，并没有绑定
	std::vector<VertexBufferElement> m_Elments;
	//这个是每个顶点的总属性 空间大小
	unsigned int m_Stride;
public:
	VertexBufferLayout()
		:m_Stride(0){}

	template<typename T>
	void push(unsigned int count) {
		static_assert(false);
	}

	template<>
	void push<float>(unsigned int count ) {
		m_Elments.push_back({ GL_FLOAT,count,GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}



	inline const	std::vector<VertexBufferElement> GetElements() const { return m_Elments; }
	inline unsigned int GetStride() const { return m_Stride; }
};