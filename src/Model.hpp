#pragma once
#include <vector>
#include <string>
#include "Mesh.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


class Shader;

class Model
{
private:
	std::vector<Mesh> m_meshes;
	//std::string m_directory;
	const aiScene* scene;

	void loadModel(const std::string& path);

	void processNodes(const aiNode* node, const aiScene* scene);

	Mesh processMeshes(aiMesh* mesh);

public:
	Model(const std::string& path);

	void draw(Shader* shader);

	void drawArray(Shader* shader);
};