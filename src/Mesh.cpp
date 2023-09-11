#include "Mesh.hpp"

#include "Texture.hpp"
#include "Shader.hpp"
#include "Render.hpp"
#include <iostream>

Mesh::Mesh(std::vector<Vertex>& vertices/*, std::vector<TextureIds> textures*/, std::vector<unsigned int>& indices)
{
	m_vertices = vertices;
	//m_textures = textures;
	m_indices  =  indices;

	setUpMesh();
}

Mesh::~Mesh()
{
	GLCALL(glDeleteBuffers(1, &m_vbo.getID()));
	GLCALL(glDeleteBuffers(1, &m_eao.getID()));
	GLCALL(glDeleteVertexArrays(1, &m_vao.getID()));
}

void Mesh::setUpMesh()
{
	/*
	m_vao.Bind();
	m_eao.createElementArray(&m_indices[0], m_indices.size());
	m_vbo.createVertexBuffer(&m_vertices[0], m_vertices.size() * sizeof(Vertex) );

	VertexBufferLayout layout;
	layout.Push<float>(3, false);
	layout.Push<float>(2, false);
	layout.Push<float>(3, false);
	m_vao.addBuffer(m_vbo, layout);
	*/
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	// load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// A great thing about structs is that their memory layout is sequential for all its items.
	// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
	// again translates to 3/2 floats which translates to a byte array.
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

	// set the vertex attribute pointers
	// vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_texture));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_normals));
	glBindVertexArray(0);
}

void Mesh::drawElements(Shader* shader)
{
	GLCALL(glBindVertexArray(VAO));
	shader->BindShader();
	GLCALL(glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(m_indices.size()), GL_UNSIGNED_INT, nullptr));
	GLCALL(glBindVertexArray(0));
}

void Mesh::drawArray(Shader* shader)
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);
	shader->BindShader();
	glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
}
