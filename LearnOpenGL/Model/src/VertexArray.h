#pragma once

#include <vector>

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
private:
	unsigned int m_RendererID;

public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& VBO, const VertexBufferLayout& layout);
	void AddBuffer(const VertexBuffer& VBO);

	void Bind() const;
	void Unbind() const;
	void Delete() const;
};