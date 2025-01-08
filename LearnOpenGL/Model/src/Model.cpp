#include "Model.h"

Model::Model(std::string const& path, bool gamma) : gammaCorrection(gamma)
{
	loadModel(path);
}

void Model::Draw(Shader shader)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Draw(shader);
	}
}

void Model::loadModel(std::string const& path)
{
	Assimp::Importer importer;
	// aiProcess_Triangulate 如果模型不全部由三角形组成，则将所有图元形状变换为三角形
	// aiProcess_FlipUVs 反转y轴的纹理坐标
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	// 检查场景和根节点不为NULL，并检查了FLAG来查看返回的数据是否完整
	if (!scene || scene->mFlags && AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}
	// 获取文件路径的目录路径
	directory = path.substr(0, path.find_last_of('/'));

	// 处理场景中所有节点
	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	// 处理节点的所有网格
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	// 对它子节点也进行相同操作
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	glm::vec3 vertexInfo; // 临时变量
	// 顶点（处理mesh中的每个顶点）
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		// 处理顶点位置，法线和纹理坐标
		Vertex vertex;
		// 位置
		vertexInfo.x = mesh->mVertices[i].x;
		vertexInfo.y = mesh->mVertices[i].y;
		vertexInfo.z = mesh->mVertices[i].z;
		vertex.Position = vertexInfo;
		// 法线
		vertexInfo.x = mesh->mNormals[i].x;
		vertexInfo.y = mesh->mNormals[i].y;
		vertexInfo.z = mesh->mNormals[i].z;
		vertex.Normal = vertexInfo;
		// 纹理坐标(Assimp允许一个顶点有8个纹理坐标，我们只关注第一组)
		if (mesh->mTextureCoords[0])
		{
			glm::vec2 texcoords;
			texcoords.x = mesh->mTextureCoords[0][i].x;
			texcoords.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = texcoords;
		}
		else
		{
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		}
		if (mesh->HasTangentsAndBitangents())
		{
			// tangent
			vertexInfo.x = mesh->mTangents[i].x;
			vertexInfo.y = mesh->mTangents[i].y;
			vertexInfo.z = mesh->mTangents[i].z;
			vertex.Tangent = vertexInfo;
			// bitangent
			vertexInfo.x = mesh->mBitangents[i].x;
			vertexInfo.y = mesh->mBitangents[i].y;
			vertexInfo.z = mesh->mBitangents[i].z;
			vertex.Bitangent = vertexInfo;
		}
		vertices.push_back(vertex); // 将读取到的顶点数据压入vertices中
	}
	// 索引（处理mesh中的Face）
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}
	// 材质（一个网格只包含一个指向材质对象的索引，获取网格的真正材质需要索引场景的mMaterials数组，网格索引位于mMaterialIndex中）
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		// diffuse maps
		std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		// specular maps
		std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		// normal maps
		std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
		// height maps
		std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
		textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
	}
	return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str); // 获得每个纹理的文件位置
		std::string path = str.C_Str();

		// 判断纹理是否被加载过
		if (textures_loaded.find(path) != textures_loaded.end())
		{
			textures.push_back(textures_loaded[path]);
		}
		else // 未被加载则加载
		{
			Texture texture(path, directory);
			texture.SetType(typeName);
			textures.push_back(texture);
			textures_loaded[path] = texture;
		}
	}

	return textures;
}

void Model::Delete()
{
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Delete();
	}
}
