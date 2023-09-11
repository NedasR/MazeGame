#pragma once

#include <vector>
#include <string>
#include "Vendors/glm/glm.hpp"
#include <glew.h>
#include <GLFW/glfw3.h>
#include "VertexArray.hpp"
#include "ElementArray.hpp"
#include "VertexBuffer.hpp"


class Shader;

struct Vertex
{
	glm::vec3 m_postions;
	glm::vec2 m_texture;
	glm::vec3 m_normals;
};

struct TextureIds
{
	unsigned int m_ID;
	std::string m_textureName;

};

class Mesh
{
private:

	std::vector<Vertex>       m_vertices;
	//std::vector<TextureIds>   m_textures;
	std::vector<unsigned int> m_indices;

	VertexArray  m_vao;
	ElementArray m_eao;
	VertexBuffer m_vbo;
	unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

public:
	Mesh(std::vector<Vertex>& vertices/*, std::vector<TextureIds> textures*/, std::vector<unsigned int>& indices);

	~Mesh();

	void setUpMesh();

	void drawElements(Shader* shader);

	void drawArray(Shader* shader);
};