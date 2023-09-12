#include "Camera.hpp"
#include <math.h>

Camera::Camera()
{
	m_yaw = 0.0f;
	m_pitch  = 0.0f;
	m_sensitivity = 0.1f;
	m_firstMouse = true;
	m_cameraPostion = glm::vec3(0.0f, 0.0f, 0.0f);
	m_upPos = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::yawAndPitchUpdate(GLFWwindow* window, float xPos, float yPos)
{
	if (m_firstMouse)
	{
		m_lastXPos = xPos;
		m_lastYPos = yPos;

		m_firstMouse = false;
	}

	int offsetX = m_lastXPos - xPos;
	int offsetY = m_lastYPos - yPos;

	m_lastXPos = xPos;
	m_lastYPos = yPos;

	m_yaw += -offsetX * m_sensitivity;
	m_pitch += offsetY * m_sensitivity;

	if (m_pitch > 89.0f)
	{
		m_pitch = 89.0f;
	}
	if (m_pitch < -89.0f)
	{
		m_pitch = -89.0f;
	}

	glm::vec3 diraction;
	diraction.x = std::cos(glm::radians(m_yaw)) * std::cos(glm::radians(m_pitch));
	diraction.y = std::sin(glm::radians(m_pitch));
	diraction.z = std::cos(glm::radians(m_pitch)) * std::sin(glm::radians(m_yaw));
	m_cameraFront = glm::normalize(diraction);
}

void Camera::setSensitivity(float sensitivity)
{
	m_sensitivity = sensitivity;
}

glm::mat4 Camera::freeCam(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		m_cameraPostion += m_sensitivity * m_cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		m_cameraPostion -= m_sensitivity * m_cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		m_cameraPostion += glm::normalize(glm::cross(m_cameraFront, glm::vec3(0.0f, 1.0f, 0.0f))) * m_sensitivity;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		m_cameraPostion -= glm::normalize(glm::cross(m_cameraFront, glm::vec3(0.0f, 1.0f, 0.0f))) * m_sensitivity;
	}
	return glm::lookAt(m_cameraPostion, m_cameraPostion + m_cameraFront, m_upPos);
}

glm::mat4 Camera::setPerspective(const float fov, const float screenHeight, const float screenWidth, const float nearPlane, const float FarPlane)
{
	return glm::perspective(glm::radians(fov), screenWidth / screenHeight, nearPlane, FarPlane);
}

void mousePostioncallback(GLFWwindow* window)
{
	Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	camera->yawAndPitchUpdate(window, x, y);
	camera = nullptr;
	delete camera;
}

void mouseClickCallback(GLFWwindow* window)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}