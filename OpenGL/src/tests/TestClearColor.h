#pragma once


#include "Test.h"

namespace test {

	// 从 Test 继承而来的具有独立特点的测试
	//色彩测试
	class TestClearColor :public Test 
	{
	public:
		TestClearColor();
		~TestClearColor();

		void OnUpdate(float deltTime) override;
		void OnRender()  override;
		void OnImGuiRender() override;
	private:
		//指定默认颜色 RGBA
		float m_clearColor[4];

	};	
}