#include "hzpch.h"
#include "OthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Hazel {
	OthographicCamera::OthographicCamera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	void OthographicCamera::RecalcultateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));
		
		/*auto translate = glm::translate(glm::mat4(1.0f), m_Position);
		auto rotate = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1)); 
		auto transform = translate * rotate;*/

		//why viewMatrix should be inverse of transform
		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}