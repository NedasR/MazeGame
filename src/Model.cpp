#include "Model.hpp"
#include <iostream>
#include "Vendors/glm/glm.hpp"

void Model::loadModel(const std::string& path)
{
	Assimp::Importer importer;
	scene = importer.ReadFile(path,aiProcess_Triangulate);
	if (!scene || scene->mFlags && AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "assimp ERROR: " << importer.GetErrorString()<< std::endl;
	}

	//m_directory = path.substr(0,path.find_last_of('/'));

	if (scene)
	{
	processNodes(scene->mRootNode,scene);
	}
}

void Model::processNodes(const aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_meshes.push_back(processMeshes(mesh));
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNodes(node->mChildren[i], scene);
	}
}

Mesh Model::processMeshes(aiMesh* mesh)
{
	std::vector<Vertex> 	 vertices;
	std::vector<unsigned int> indices;

	for (size_t i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		vertex.m_postions.x = mesh->mVertices[i].x;
		vertex.m_postions.y = mesh->mVertices[i].y;
		vertex.m_postions.z = mesh->mVertices[i].z;

		vertex.m_normals.x = mesh->mNormals[i].x;
		vertex.m_normals.y = mesh->mNormals[i].y;
		vertex.m_normals.z = mesh->mNormals[i].z;

		vertex.m_texture.x = mesh->mTextureCoords[0][i].x;
		vertex.m_texture.y = mesh->mTextureCoords[0][i].y;

		vertices.push_back(vertex);
	}
	
	for (size_t i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (size_t y = 0; y < face.mNumIndices; y++)
		{
			indices.push_back(face.mIndices[y]);
		}
	}

	return Mesh(vertices, indices);
}

Model::Model(const std::string& path)
{
	loadModel(path);
}

void Model::draw(Shader* shader)
{
	// draws each mesh inside the model
	for (unsigned int i = 0; i < m_meshes.size(); i++)
	{
		m_meshes[i].drawElements(shader);
	}
}

void Model::drawArray(Shader* shader)
{
	for (int i = 0; i < m_meshes.size(); i++)
	{
		m_meshes[i].drawArray(shader);
	}
}
