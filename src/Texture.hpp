#pragma once

#include <string>
#include <map>
#include <memory>

class Texture
{
	private:
	int m_width,m_height,m_BBB;
	std::string m_filePath;
	unsigned char* m_fileDataID;
	unsigned int m_textureID;
	bool m_initialized;


	public:

	Texture();
	~Texture();

	void loadTextureFromFile(const std::string& filepath);

	void createTexture();

	inline const unsigned int getTextureID() const {if (m_initialized) {return m_textureID;} return NULL;}

	static void loadTexture(const std::string& newIndex, const std::string& filePath, std::map<std::string, std::shared_ptr<Texture>>& textureList);

	static void loadTexture(const std::string& newIndex, const std::string& filePath);

};