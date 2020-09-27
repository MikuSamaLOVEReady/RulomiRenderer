#include "TestClearColor.h"
#include<GL/glew.h>

//src Ŀ¼���� vs��includeĿ¼��
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
	// glClearColor (0.0, 0.0, 0.0, 0.0);//���������ɫ
	// glClear(GL_COLOR_BUFFER_BIT);//�Ѵ������Ϊ��ǰ��ɫ
	//   glClearDepth(1.0);//ָ����Ȼ�������ÿ��������Ҫ��ֵ
	//   glClear(GL_DEPTH_BUFFER_BIT);//�����Ȼ�����


}

void test::TestClearColor::OnImGuiRender()
{
	//editer��������Ҽ��򿪵�ɫ��
	ImGui::ColorEdit4("Clear Color", m_clearColor);
}
