#pragma once
#include <vector>
#include "renderer.h"

//ÿһ������ ��һ�� element
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
	//��������зŵ���ÿһ��VB ����Ӧ���������Խ��� ����
	//ֻ��һ�����������ã���û�а�
	std::vector<VertexBufferElement> m_Elments;
	//�����ÿ������������� �ռ��С
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