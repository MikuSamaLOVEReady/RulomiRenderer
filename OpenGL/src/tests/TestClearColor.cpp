#include "TestClearColor.h"
#include<GL/glew.h>

//src 目录不在 vs的include目录下
#include "renderer.h"
#include "imgui/imgui.h"


test::TestClearColor::TestClearColor()
	:m_clearColor{0.2f, 0.3f, 0.8f, 1.0f}
{
}

test::TestClearColor::~TestClearColor()
{
}

void test::TestClearColor::OnUpdate(float deltTime)
{
}

void test::TestClearColor::OnRender()
{
	glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]);
	glClear(GL_COLOR_BUFFER_BIT);
	// glClearColor (0.0, 0.0, 0.0, 0.0);//设置清除颜色
	// glClear(GL_COLOR_BUFFER_BIT);//把窗口清除为当前颜色
	//   glClearDepth(1.0);//指定深度缓冲区中每个像素需要的值
	//   glClear(GL_DEPTH_BUFFER_BIT);//清除深度缓冲区


}

void test::TestClearColor::OnImGuiRender()
{
	//editer组件可以右键打开调色板
	ImGui::ColorEdit4("Clear Color", m_clearColor);
}
