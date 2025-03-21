#pragma once

#include <vector>

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
private:
	unsigned int m_RendererID;
	unsigned int m_AttributeCounts = 0;
	unsigned int m_AttributeOffset = 0;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& VBO, const VertexBufferLayout& layout);
	void BatchedAddBuffer(const VertexBuffer& VBO, const void* data, unsigned int size, unsigned int stride, unsigned int type);

	inline unsigned int GetId() const { return m_RendererID; }
	void Bind() const;
	void Unbind() const;
	void Delete() const;
};