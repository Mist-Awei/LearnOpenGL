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
	// 网格数据
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	VertexArray VAO;
	// 函数
	Mesh(const std::vector<Vertex> vertices, const std::vector<unsigned int> indices, const std::vector<Texture> textures);
	void Draw(Shader shader);
	void Delete();
private:
	// 渲染数据
	VertexBuffer VBO;
	ElementBuffer EBO;
	// 函数
	void setupMesh();	
};

