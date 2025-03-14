#pragma once

#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
public:
	Model(std::string const& path, bool gamma = false);
	void Draw(Shader shader);
	void Delete();
private:
	std::vector<Mesh> meshes;
	std::unordered_map<std::string, Texture> textures_loaded;
	std::string directory;
	bool gammaCorrection;

	void loadModel(std::string const& path);
	void loadModelFromMemory(const char* path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};