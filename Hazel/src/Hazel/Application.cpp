#include "hzpch.h"
#include "Application.h"

#include "Hazel/Log.h"
#include <glad/glad.h>

#include "Input.h"

namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		HZ_CORE_ASSERT(!s_Instance, "Application arleady exist!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		
		m_ImGuilayer = new ImGuiLayer;
		PushOverlay(m_ImGuilayer);

		//triangle
		//1. Create VertexArray
		m_VertexArray.reset(VertexArray::Create());
		//2. define vertices, Indices
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			0.5f,  -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			0.0f,   0.5f, 0.0f, 0.8f, 0.7f, 0.2f, 1.0f
		};
		unsigned int indices[3] = { 
			0, 1, 2 
		};
		//3. Create VertexBuffer
		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexBuffer->SetLayout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"},
		});
		m_VertexArray->AddVertexBuffer(vertexBuffer);
		//4. Create IndexBuffer
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);
		//5. define shader
		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;			
			layout(location = 1) in vec4 a_Color;			
			
			out vec3 v_Position;			
			out vec4 v_Color;			

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";
		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;			
			
			in vec3 v_Position;			
			in vec4 v_Color;	

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";
		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

		//Square
		//1. Create VertexArray
		m_SqaureVA.reset(VertexArray::Create());
		//2. define vertices, Indices
		float squareVertices[3 * 4] = {
			-0.75f,	 -0.75f, 0.0f,
			 0.75f,  -0.75f, 0.0f,
			 0.75f,   0.75f, 0.0f,
			-0.75f,   0.75f, 0.0f
		};
		unsigned int squreIndices[6] = { 
			0, 1, 2, 2, 3, 0 
		};
		//3. Create VertexBuffer
		std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ShaderDataType::Float3, "a_Position"},
		});
		m_SqaureVA->AddVertexBuffer(squareVB);
		//4. Create IndexBuffer
		std::shared_ptr<IndexBuffer> squreIB;
		squreIB.reset(IndexBuffer::Create(squreIndices, sizeof(squreIndices) / sizeof(uint32_t)));
		m_SqaureVA->SetIndexBuffer(squreIB);
		//5. define shader
		std::string blueShadervertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;			
			
			out vec3 v_Position;			

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";
		std::string blueShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;			
			
			in vec3 v_Position;			

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";
		m_BlueShader.reset(new Shader(blueShadervertexSrc, blueShaderFragmentSrc));

	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event & e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnwindowClose));
		//HZ_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.m_Handled)
				break;
		}
	}

	void Application::PushLayer(Layer * layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer * layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_BlueShader->Bind();
			m_SqaureVA->Bind();
			glDrawElements(GL_TRIANGLES, m_SqaureVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			m_Shader->Bind();
			m_VertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuilayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuilayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnwindowClose(WindowCloseEvent & e)
	{
		m_Running = false;
		return true;
	}

}