#pragma once
namespace test {

	//Test class��Ŀ����� ��֮����imgui��� ���ٲ鿴Ч��
	//����VB VA��Ӧ�ÿ���stack �� �����رջ����л����� �Ϳ��Զ�������
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

