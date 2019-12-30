
//For analysis, I did disolve preprocessor #include


#pragma once

//start Hazel Engine src
#define HZ_PLATFORM_WINDOWS
#define HZ_BUILD_DLL

// For use by Hazel applications
#include <stdio.h>
//#include "Hazel/Application.h"
//#include "Core.h"
#pragma once

#ifdef HZ_PLATFORM_WINDOWS
	#ifdef HZ_BUILD_DLL
		#define HAZEL_API __declspec(dllexport)
	#else
		#define HAZEL_API __declspec(dllimport)
	#endif
#else
	#error Hazel only supports Windows!
#endif

namespace Hazel {

	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//To be defined in CLIENT
	Application* CreateApplication();
}

namespace Hazel {

	Application::Application()
	{
	}


	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (true);
	}

}

// -----------Entry Point --------------
//#include "Hazel/EntryPoint.h"
#pragma once

#ifdef HZ_PLATFORM_WINDOWS

//this is kind of Front Declare
extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv)
{
	printf("Hazel Engine\n");
	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}

#endif 
// ------------------------------------- 
//End Hazel



//start SandBox src
#undef HZ_BUILD_DLL
class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
	}

	~Sandbox()
	{
	}

};

//�ᱹ Entry Point�� Hazel Engine���� ������ main�� ����Ǵ� ���� ������,
//�߿��Ѱ��� Application�� ��ӹ��� SandBoxŬ������ SandBox������Ʈ���� �����ϰ� �մٴ� ���̴�.
//�ٽø��� ����ڴ� ��� Entry Point�� �����ϴ� ���� �ƴ����� 
//Hazel Engine���� �� ��ɵ��� ��ü������ �����ϰ� �ִ°��̴�.
Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}

//end SandBox