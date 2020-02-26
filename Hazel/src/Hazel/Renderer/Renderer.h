#pragma once

#include "RenderCommand.h"
#include "OthographicCamera.h"
#include "Shader.h"

namespace Hazel {

	class Renderer
	{
	public:
		static void BeginScene(OthographicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}