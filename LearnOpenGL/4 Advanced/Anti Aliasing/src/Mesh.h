#pragma once

#include <vector>

#include "CallError.h"
#include "Shader.h"
#define MAX_BONE_INFLUENCE 4

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
	//bone indexes which will influence this vertex
	int m_BoneIDs[MAX_BONE_INFLUENCE];
	//weights from each bone
	float m_Weights[MAX_BONE_INFLUENCE];
};

struct Material {
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh
{
public:
	// ��������
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Material> materials;
	unsigned int mVAO;
	// ����
	Mesh(const std::vector<Vertex> vertices, const std::vector<unsigned int> indices, std::vector<Material> materials);
	~Mesh();
	void Draw(Shader &shader);
	void Delete();
private:
	// ��Ⱦ����
	unsigned int mVBO, mEBO;
	// ����
	void setupMesh();	
};