#include "Texture.hpp"
#include "Vendors/stb_image/stb_image.h"
//#include <stb_image.h>
#include <iostream>
#include "glew.h"
#include "Game.hpp"

Texture::Texture()
{
	m_initialized = false;
	m_width = 0;
	m_height = 0;
	m_BBB = 0;
	m_textureID = 0;
	m_fileDataID = nullptr;
}

Texture::~Texture()
{
	if (m_initialized)
	{
		glDeleteTextures(1, &m_textureID);
	}
}

void Texture::loadTextureFromFile(const std::string& filepath)
{
	stbi_set_flip_vertically_on_load(true);
	m_fileDataID = stbi_load(filepath.c_str(), &m_width, &m_height, &m_BBB, 4);
	if (!m_fileDataID)
	{
		std::cout << "Failed to load from file Fuction name: loadTextureFromFile "<< std::endl;
	}
}

void Texture::createTexture()
{

	glGenTextures(1,&m_textureID);
	glBindTexture(GL_TEXTURE_2D,m_textureID);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,m_width,m_height,0,GL_RGBA,GL_UNSIGNED_BYTE,m_fileDataID);

	glGenerateMipmap(GL_TEXTURE_2D);

	m_initialized = true;

	stbi_image_free(m_fileDataID);
}

void Texture::loadTexture(const std::string& newIndex,const std::string& filePath)
{
	loadTexture(newIndex, filePath,Game::m_textures);
}

void Texture::loadTexture(const std::string& newIndex, const std::string& filePath, std::map<std::string, std::shared_ptr<Texture>>& textureList)
{
	textureList[newIndex] = std::make_shared<Texture>();
	std::shared_ptr<Texture> TexturePointer = textureList[newIndex];
	TexturePointer.get()->loadTextureFromFile(filePath);
	TexturePointer.get()->createTexture();
}