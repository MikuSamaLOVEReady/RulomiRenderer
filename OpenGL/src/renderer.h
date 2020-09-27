#pragma once
#include <GL/glew.h>
#include"VertexArray.h"
#include"IndexBuffer.h"
#include"Shader.h"



//�������������error Ӱ��
static void GLClearError();
static bool GLCheckError();


class Renderer {
public:
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader&shader ) const;
	void Clear ()const;

};