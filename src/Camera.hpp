#pragma once
#include "Vendors/glm/glm.hpp"
#include "Vendors/glm/gtc/matrix_transform.hpp"
#include "Vendors/glm/gtc/type_ptr.hpp"
#include <GLFW/glfw3.h>

class GLFWwindow;

class Camera
{
	private:
	float m_yaw, m_pitch;
	float m_sensitivity;
	bool m_firstMouse;
	float m_lastXPos, m_lastYPos;
	double m_xPos, m_yPos;
	glm::vec3 m_cameraFront;
	glm::vec3 m_cameraPostion;
	glm::vec3 m_upPos;

	public:
	Camera();

	void yawAndPitchUpdate(GLFWwindow* window, float xPos,float yPos);

	void setSensitivity(float sensitivity);

	inline void setCameraPos(glm::vec3& Pos) { m_cameraPostion = Pos; }

	glm::mat4 freeCam(GLFWwindow* window);

	inline const glm::vec3 getCameraFront() const { return m_cameraFront; }
	
	glm::mat4 setPerspective(const float fov,const float screenHeight,const float screenWidth,const float nearPlane,const float FarPlane);
};

void mousePostioncallback(GLFWwindow* window);