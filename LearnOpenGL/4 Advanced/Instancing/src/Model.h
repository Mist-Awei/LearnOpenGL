#pragma once

#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
public:
	std::vector<Mesh> meshes;
	std::unordered_map<std::string, Material> materials_loaded;
	std::string directory;
	bool gammaCorrection;
	Model(std::string const& path, bool gamma = false);
	~Model();
	void Draw(Shader &shader);
private:
	void loadModel(std::string const& path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Material> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	unsigned int MaterialFromFile(const char* path, const std::string& directory, bool gamma = false);
};