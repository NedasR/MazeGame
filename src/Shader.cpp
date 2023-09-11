#include "Shader.hpp"
#include <fstream>
#include <sstream>
#include "glew.h"
#include <iostream>
#include "Render.hpp"
#include "Game.hpp"
Shader::Shader()
{
    m_shaderID = 0;
}

Shader::~Shader()
{
    glDeleteProgram(m_shaderID);
}

Shaders Shader::getSahderSrc(const std::string& filepath)
{
    std::fstream file(filepath);
    std::string line;
    std::string newline;
    std::stringstream shader[2];
    ShaderType type;
    while (std::getline(file, line))
    {
        if (line.find("shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            shader[(int)type] << line << "\n";
        }
    }
    file.close();
    return { shader[0].str(),shader[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    int status;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* msg = new char[length];
        std::cout << msg << std::endl;
        glGetShaderInfoLog(id, length, &length, msg);
        std::cout << "failed to compile shader: " << (type == GL_VERTEX_SHADER ? "vertex " : "fragment ") << msg << std::endl;
        delete[] msg;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    int status;
    glGetLightiv(program, GL_LINK_STATUS, &status);
    if (!status)
    {
        std::cout << status << " program link status" << std::endl;
    }
    glValidateProgram(program);
    glDeleteShader(vs);
    glDeleteShader(fs);
    m_shaderID = program;
    return program;
}

void Shader::BindShader()
{
    glUseProgram(m_shaderID);
}

void Shader::UnbindShader()
{
    glUseProgram(0);
}

unsigned int Shader::getUniformLoction(const char* uniformName)
{
    const auto& chacedUniforms = getCache();
    for (int i = 0; i < chacedUniforms.size(); i++)
    {
        if (chacedUniforms[i].uniformName == uniformName)
        {
            return chacedUniforms[i].locationID;
        }
    }
    unsigned int location = glGetUniformLocation(m_shaderID, uniformName);
    m_Cache.push_back({ uniformName,location });

    return location;
}

void Shader::setUniformv3(const char* varibalName, float v0, float v1, float v2)
{
    BindShader();
    glUniform3f(getUniformLoction(varibalName),v0,v1,v2);
}

void Shader::setUniformv1i(const char* varibalName, int v0)
{
    BindShader();
    glUniform1i(getUniformLoction(varibalName),v0);
}

void Shader::setUniformvmatrix4f(const char* varibalName, glm::mat4& value)
{
    BindShader();
    glUniformMatrix4fv(getUniformLoction(varibalName),1,GL_FALSE, glm::value_ptr(value));
}

void Shader::setTexture(int textureLayer, const std::string& textureIndex)
{
    setTexture(textureLayer, textureIndex, Game::m_textures);
}

void Shader::setTexture(int textureLayer, const std::string& textureIndex, std::map<std::string, std::shared_ptr<Texture>>& textureList)
{  
    if (textureLayer > 1){std::cout << "invalid textureLayer Function: setTexture" << std::endl; return;}

    this->BindShader();
    glActiveTexture(GL_TEXTURE0 + textureLayer);
    std::string ourTexture = "ourTexture" + std::to_string(textureLayer);
    this->setUniformv1i(ourTexture.c_str(), textureLayer);
    glBindTexture(GL_TEXTURE_2D, textureList[textureIndex].get()->getTextureID());
}

void Shader::loadShader(const std::string& newIndex, const std::string& filePath)
{
    loadShader(newIndex, filePath,Game::m_shaders);
}

void Shader::loadShader(const std::string& newIndex, const std::string& filePath, std::map<std::string, std::shared_ptr<Shader>>& shaderList)
{
    shaderList[newIndex] = std::make_shared<Shader>();
    std::shared_ptr<Shader> TexturePointer = shaderList[newIndex];
    Shaders shadersrc = Shader::getSahderSrc(filePath);
    TexturePointer.get()->CreateShader(shadersrc.vertex, shadersrc.framgent);
}
