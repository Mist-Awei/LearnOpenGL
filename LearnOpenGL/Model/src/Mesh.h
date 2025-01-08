#pragma once

#include <vector>

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ElementBuffer.h"
#include "Texture.h"
#include "Shader.h"

class Mesh
{
public:
	// ��������
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	VertexArray VAO;
	// ����
	Mesh(const std::vector<Vertex> vertices, const std::vector<unsigned int> indices, const std::vector<Texture> textures);
	void Draw(Shader shader);
	void Delete();
private:
	// ��Ⱦ����
	VertexBuffer VBO;
	ElementBuffer EBO;
	// ����
	void setupMesh();	
};

