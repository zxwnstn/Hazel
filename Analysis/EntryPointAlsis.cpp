
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

//결국 Entry Point는 Hazel Engine에서 정의한 main이 실행되는 것은 맞지만,
//중요한것은 Application을 상속받은 SandBox클래스를 SandBox프로젝트에서 정의하고 잇다는 것이다.
//다시말해 사용자는 비록 Entry Point를 정의하는 것은 아니지만 
//Hazel Engine에서 쓸 기능들을 자체적으로 설정하고 있는것이다.
Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}

//end SandBox