#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <vector>

#include <glm/glm.hpp>

class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();
	void Bind() const;
	void Unbind() const;
	void Delete() const;
};

#endif // !VERTEXBUFFER_H
