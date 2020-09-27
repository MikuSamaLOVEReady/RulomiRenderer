#pragma once
namespace test {

	//Test class的目标就是 在之后用imgui面板 快速查看效果
	//所有VB VA都应该开在stack 上 这样关闭或者切换过后 就可自动回收了
	class Test
	{
	  public:
		  Test() {};
		  virtual ~Test(){}

		  virtual void OnUpdate(float deltTime){}
		  virtual void OnRender(){}
		  virtual void OnImGuiRender(){}
	};
}

