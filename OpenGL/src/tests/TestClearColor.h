#pragma once


#include "Test.h"

namespace test {

	// �� Test �̳ж����ľ��ж����ص�Ĳ���
	//ɫ�ʲ���
	class TestClearColor :public Test 
	{
	public:
		TestClearColor();
		~TestClearColor();

		void OnUpdate(float deltTime) override;
		void OnRender()  override;
		void OnImGuiRender() override;
	private:
		//ָ��Ĭ����ɫ RGBA
		float m_clearColor[4];

	};	
}