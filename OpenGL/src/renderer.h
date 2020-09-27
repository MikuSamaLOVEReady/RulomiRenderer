#pragma once
#include <GL/glew.h>
#include"VertexArray.h"
#include"IndexBuffer.h"
#include"Shader.h"



//清除其他函数的error 影响
static void GLClearError();
static bool GLCheckError();


class Renderer {
public:
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader&shader ) const;
	void Clear ()const;

};