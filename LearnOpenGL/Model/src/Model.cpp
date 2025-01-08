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
	// aiProcess_Triangulate ���ģ�Ͳ�ȫ������������ɣ�������ͼԪ��״�任Ϊ������
	// aiProcess_FlipUVs ��תy�����������
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	// ��鳡���͸��ڵ㲻ΪNULL���������FLAG���鿴���ص������Ƿ�����
	if (!scene || scene->mFlags && AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}
	// ��ȡ�ļ�·����Ŀ¼·��
	directory = path.substr(0, path.find_last_of('/'));

	// �����������нڵ�
	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	// ����ڵ����������
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	// �����ӽڵ�Ҳ������ͬ����
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

	glm::vec3 vertexInfo; // ��ʱ����
	// ���㣨����mesh�е�ÿ�����㣩
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		// ������λ�ã����ߺ���������
		Vertex vertex;
		// λ��
		vertexInfo.x = mesh->mVertices[i].x;
		vertexInfo.y = mesh->mVertices[i].y;
		vertexInfo.z = mesh->mVertices[i].z;
		vertex.Position = vertexInfo;
		// ����
		vertexInfo.x = mesh->mNormals[i].x;
		vertexInfo.y = mesh->mNormals[i].y;
		vertexInfo.z = mesh->mNormals[i].z;
		vertex.Normal = vertexInfo;
		// ��������(Assimp����һ��������8���������꣬����ֻ��ע��һ��)
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
		vertices.push_back(vertex); // ����ȡ���Ķ�������ѹ��vertices��
	}
	// ����������mesh�е�Face��
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}
	// ���ʣ�һ������ֻ����һ��ָ����ʶ������������ȡ���������������Ҫ����������mMaterials���飬��������λ��mMaterialIndex�У�
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
		mat->GetTexture(type, i, &str); // ���ÿ��������ļ�λ��
		std::string path = str.C_Str();

		// �ж������Ƿ񱻼��ع�
		if (textures_loaded.find(path) != textures_loaded.end())
		{
			textures.push_back(textures_loaded[path]);
		}
		else // δ�����������
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
