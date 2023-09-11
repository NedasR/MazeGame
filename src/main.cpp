#include <iostream>
#include <string>
#include <glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>

#include "Render.hpp"
#include "ElementArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

#include "Vendors/glm/glm.hpp"
#include "Vendors/glm/gtc/matrix_transform.hpp"
#include "Vendors/glm/gtc/type_ptr.hpp"

#include "Model.hpp"

#include "Camera.hpp"
#include <map>
#include <memory>
#include "Game.hpp"

//#include "assimp/scene.h"
//#include "assimp/postprocess.h"

#define M_PI 3.14159265358979323846f
int main()
{
    Game game(480, 640, "Coffie's Game");

    game.gameLoop();
}

int main2()
{

    GLFWwindow* window;
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(640, 480, "Coffie's Game", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (glewInit() != GLEW_OK)
    {
        std::cout << " is not okey";
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    Shaders shadersrc = Shader::getSahderSrc("res/Shaders/Basic.shader");
    Shader defShader;
    defShader.CreateShader(shadersrc.vertex, shadersrc.framgent);

    defShader.BindShader();

    Texture Tex;
    Tex.loadTextureFromFile("res/Textures/container.jpg");
    Tex.createTexture();
    Texture Tex2;
    Tex2.loadTextureFromFile("res/Textures/Coffee.png");
    Tex2.createTexture();

    defShader.UnbindShader();

    Renderer renderer;
    /*
    glm::vec4 vec(1.0f,0.0f,0.0f,1.0f);
    glm::mat4 trans(1.0f);
    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    vec = trans * vec;
    

    std::cout << vec.x << vec.y << vec.z << std::endl;
    */

    glm::mat4 model = glm::mat4(1.0);
    model = glm::rotate(model,glm::radians(-23.0f),glm::vec3(1.0,0.0,0.0));

    glm::mat4 prespective;
    prespective = glm::perspective(glm::radians(45.0f), 640.0f / 480.0f ,0.1f,100.0f);

    glm::mat4 view(1.0f);
    view = glm::translate(view,glm::vec3(0.0f,0.0f,-3.0f));

    glm::vec3 camera(0.0f,0.0f,-3.0f);
    glEnable(GL_DEPTH_TEST);

    Camera lookatCamera;
    glfwSetWindowUserPointer(window, &lookatCamera);
    glfwSetCursorPosCallback(window, (GLFWcursorposfun)mousePostioncallback);
    /* Loop until the user closes the window */

    Model tank("res/Models/tank.obj");

    Model cube("res/Models/cube.obj");

    Shaders shaderstuff = Shader::getSahderSrc("res/Shaders/Default.shader");

    Shader tankShader;
    tankShader.CreateShader(shaderstuff.vertex, shaderstuff.framgent);
    bool gg= true;
    while (!glfwWindowShouldClose(window))

    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window,true);
        }

        //model = glm::rotate(model, M_PI*2 / 6, glm::vec3(1.0, 0.0, 0.0));

        //camera
        lookatCamera.getCameraFront();
        view = lookatCamera.freeCam(window);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if(gg)
        {
            defShader.BindShader();
            defShader.setUniformv3("CsetColor", cos(glfwGetTime()), 0.5, 0.7);
            glActiveTexture(GL_TEXTURE0);
            defShader.setUniformv1i("ourTexture1", 0);
            glBindTexture(GL_TEXTURE_2D, Tex.getTextureID());
            glActiveTexture(GL_TEXTURE1);
            defShader.setUniformv1i("ourTexture2", 1);
            glBindTexture(GL_TEXTURE_2D, Tex2.getTextureID());
            glActiveTexture(GL_TEXTURE0);
        }
            defShader.setUniformvmatrix4f("model", model);
            defShader.setUniformvmatrix4f("prespective", prespective);
            defShader.setUniformvmatrix4f("view", view);
        
            cube.draw(&defShader);
        
        glm::mat4 model4 = glm::translate(glm::mat4(1.0f),glm::vec3(-5.0f, 0.0f, 0.0f));
        model4 = glm::scale(model4,glm::vec3(0.2f, 0.2f, 0.2f));
        tankShader.setUniformvmatrix4f("model", model4);
        tankShader.setUniformvmatrix4f("prespective", prespective);
        tankShader.setUniformvmatrix4f("view", view);

        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        {
            tankShader.BindShader();
            glActiveTexture(GL_TEXTURE1);
            tankShader.setUniformv1i("ourTexture1", 1);
            glBindTexture(GL_TEXTURE_2D, Tex2.getTextureID());
        }
        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        {
           tankShader.BindShader();
           glActiveTexture(GL_TEXTURE0);
           tankShader.setUniformv1i("ourTexture1", 0);
           glBindTexture(GL_TEXTURE_2D, Tex.getTextureID());
        }

        if (gg)
        //tank.drawArray(&tankShader);
        {
            tankShader.BindShader();
            glActiveTexture(GL_TEXTURE0);
            tankShader.setUniformv1i("ourTexture1", 0);
            glBindTexture(GL_TEXTURE_2D, Tex.getTextureID());
        }
        tank.draw(&tankShader);
        gg = false;
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

    }

    glfwTerminate();
    return 0;
}

// to do list 
/*
make a 3rd person camera mode inside of camera class.
make a maze for the game.
make an object class where we will have pure virtal fuctions that will be used
for rendering for a render manger maby like a queue that you need to push to in order 
for it to be renderd.

future todo list make collision detection AABB,
*/