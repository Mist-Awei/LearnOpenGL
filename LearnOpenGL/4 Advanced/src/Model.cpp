#include "Model.h"

#include <stb_image/stb_image.h>

Model::Model(std::string const& path, bool gamma)
	: gammaCorrection(gamma)
{
	loadModel(path);
}

Model::~Model()
{
	for (auto& material : materials_loaded)
	{
		GLCall(glDeleteTextures(1, (unsigned int*)&material.second.id));
	}
	for (unsigned int i = 0; i < meshes.size(); ++i)
	{
		meshes[i].Delete();
	}
}

void Model::Draw(Shader &shader)
{
	for (unsigned int i = 0; i < meshes.size(); ++i)
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
	std::vector<Material> materials;

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
		std::vector<Material> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		materials.insert(materials.end(), diffuseMaps.begin(), diffuseMaps.end());
		// specular maps
		std::vector<Material> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		materials.insert(materials.end(), specularMaps.begin(), specularMaps.end());
		// normal maps
		std::vector<Material> normalMaps = loadMaterialTextures(material, aiTextureType_NORMALS, "texture_normal");
		materials.insert(materials.end(), normalMaps.begin(), normalMaps.end());
		// reflection maps
		std::vector<Material> reflectionMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_reflection");
		materials.insert(materials.end(), reflectionMaps.begin(), reflectionMaps.end());
	}
	return Mesh(vertices, indices, materials);
}

std::vector<Material> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<Material> materials;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str); // ���ÿ��������ļ�λ��
		std::string path = str.C_Str();

		// �ж������Ƿ񱻼��ع�
		if (materials_loaded.find(path) != materials_loaded.end())
		{
			materials.push_back(materials_loaded[path]);
		}
		else // δ�����������
		{
			Material material;
			material.id = MaterialFromFile(str.C_Str(), this->directory, this->gammaCorrection);
			material.type = typeName;
			material.path = str.C_Str();
			materials.push_back(material);
			materials_loaded[path] = material;
		}
	}
	return materials;
}

unsigned int Model::MaterialFromFile(const char* path, const std::string& directory, bool gamma)
{
	std::string filename = std::string(path);
	filename = directory + '/' + filename;
	/*
	// ��ȡ����Ŀ��ַ�����
	int len = MultiByteToWideChar(CP_ACP, 0, filename.c_str(), -1, NULL, 0);
	// �����㹻���ڴ沢ת���ַ���
	std::wstring wstr(len, L'\0');  // ʹ��std::wstring������ָ��
	// ת���ַ���
	MultiByteToWideChar(CP_ACP, 0, filename.c_str(), -1, &wstr[0], len);
	FILE* f = nullptr;
	errno_t err = _wfopen_s(&f, wstr.c_str(), L"rb");  // ʹ��wstr.c_str()ֱ�Ӵ��ݸ� _wfopen_s
	if (err != 0)
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	else
	{
		// ���ز���������
		stbi_set_flip_vertically_on_load(true);
		// m_BPP = nrChannels;
		m_LocalBuffer = stbi_load_from_file(f, &m_Width, &m_Height, &m_BPP, 0); // ������ͼ��Ŀ�ߺ���ɫͨ����������Ӧ����
		fclose(f);
	}
	*/
	unsigned int materialID;
	glGenTextures(1, &materialID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, materialID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return materialID;
}