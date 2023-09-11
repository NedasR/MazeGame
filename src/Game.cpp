#include "Game.hpp"
#include "RenderManger.hpp"

std::map<std::string, std::shared_ptr<Shader>> Game::m_shaders;
std::map<std::string, std::shared_ptr<Texture>> Game::m_textures;

void Game::gameInit()
{
	glfwSetWindowUserPointer(m_window, &m_camera);
	glfwSetCursorPosCallback(m_window, (GLFWcursorposfun)mousePostioncallback);

	// settings 

	// texture loading 

	Texture::loadTexture("CubeTex", "res/Textures/container.jpg");
	Texture::loadTexture("CoffeeTex", "res/Textures/Coffee.png");
	//Shaders here

	Shader::loadShader("cubeShader", "res/Shaders/Basic.shader");
	m_shaders["cubeShader"].get()->setTexture(0, "CubeTex");
	m_shaders["cubeShader"].get()->setTexture(1, "CoffeeTex");
	Shader::loadShader("tankShader","res/Shaders/Default.shader");
	m_shaders["tankShader"].get()->setTexture(0, "CubeTex");

	//Model loading here since it is the init
	Model tank("res/Models/tank.obj");
	m_objects["tankobj"] = std::make_shared<StaticObject>();
	m_objects["tankobj"].get()->setModel(tank);
	m_objects["tankobj"].get()->setShader("tankShader");
	//m_objects["tankobj"].get()->setPosition(glm::vec3(0.0f,0.0f,-5.0f));
	RenderManger::addToRenderList(m_objects["tankobj"].get());
	//object.setModel();

	// bool stuff
}

Game::Game(const float windowHeightm, const float windowWidth, const std::string& windowName) :
	m_height(windowHeightm),
	m_width(windowWidth),
	m_windowName(windowName)
{
	m_cameraView = glm::mat4(1.0f);
	m_perspective = glm::mat4(1.0f);
	m_updatePerspective = true; //updates the Perspective when first time the program runs and if changes are needed on run time
	m_fov = 45.0f;
	m_window = nullptr;

	if (!glfwInit()){return;}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(m_width ,m_height,m_windowName.c_str(), nullptr, nullptr);

	if (!m_window)
	{
		glfwTerminate();
		return ;
	}

	glfwMakeContextCurrent(m_window);

	glfwSwapInterval(1);

	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (glewInit() != GLEW_OK)
	{
		std::cout << " is not okey";
	}
	// render thing needed for GL_DEPTH_BUFFER_BIT to be available
	glEnable(GL_DEPTH_TEST);

}

void Game::gameLoop()
{
	gameInit();

	while (!glfwWindowShouldClose(m_window))
	{
		//Game logic update stuff like controls
		update();

		render();

		glfwPollEvents();
	}
	glfwTerminate();
}

void Game::render()
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Render here
	for ( auto& Object : RenderManger::m_renderList)
	{
		Object->draw();
		Object->updateTransform();
		Object->updateMVP(m_shaders["tankShader"].get(), m_perspective, m_cameraView);
	}
	
	glfwSwapBuffers(m_window);
}

void Game::cameraUpdate(const CameraMode mode)
{
	switch (mode)
	{
		case CameraMode::NONE:
		{

		}
		case CameraMode::FREECAM:
		{
			m_camera.getCameraFront();
			m_cameraView = m_camera.freeCam(m_window);
		}
		case CameraMode::THIRD_PERSON:
		{
			// implement soon in camera class
		}
	}

	if (m_updatePerspective)
	{
		m_perspective = m_camera.setPerspective(m_fov, m_height, m_width, 0.1f, 100.0f);
		m_updatePerspective = false;
	}
}

void Game::update()
{
	cameraUpdate(CameraMode::FREECAM);
}
