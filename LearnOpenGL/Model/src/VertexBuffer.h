#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <vector>

#include <glm/glm.hpp>

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

class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer(const void* data, unsigned int size);
	VertexBuffer();
	~VertexBuffer();
	void AddBuffer(const std::vector<Vertex>& vertices);
	void Bind() const;
	void Unbind() const;
	void Delete() const;
};

#endif // !VERTEXBUFFER_H
