#pragma once
#include <iostream>
#include <glew.h>
#include <GLFW/glfw3.h>
#include "Vendors/glm/glm.hpp"
#include "Vendors/glm/gtc/matrix_transform.hpp"
#include "Vendors/glm/gtc/type_ptr.hpp"
#include "Camera.hpp"
#include <map>
#include <memory>
#include "Texture.hpp"
#include "Shader.hpp"
#include "StaticObject.hpp"

enum class CameraMode
{
	NONE = 0,
	FREECAM = 1,
	THIRD_PERSON = 2
};

class Game
{
	private:
	float m_height, m_width;
	float m_fov;
	std::string m_windowName;

	GLFWwindow* m_window;
	Camera m_camera;
	glm::mat4 m_cameraView;
	glm::mat4 m_perspective;
	bool m_updatePerspective;


	public:

    static std::map<std::string, std::shared_ptr<Texture>> m_textures;
	static std::map<std::string, std::shared_ptr<Shader>> m_shaders;
	std::map<std::string, std::shared_ptr<StaticObject>> m_objects;

	void gameInit();

	Game(const float windowHeightm, const float windowWidth, const std::string& windowName);
		 
	void gameLoop();

	void render();

	void cameraUpdate(const CameraMode mode);

	void update();
	
	static bool isInsideMazeWalls(glm::vec3 pos);
};