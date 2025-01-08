#include "VertexBuffer.h"
#include "CallError.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	GLCall(glGenBuffers(1, &m_RendererID)); // 生成一个带有缓冲ID的顶点缓冲对象VBO
	// 把顶点数组复制到缓冲中供OpenGL使用.顶点缓冲对象的缓冲类型是GL_ARRAY_BUFFER
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); // 将创建的顶点缓冲对象VBO绑定到GL_ARRAY_BUFFER目标上
	// 将用户定义的顶点数据复制到当前绑定的缓冲类型中
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::VertexBuffer()
{
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

VertexBuffer::~VertexBuffer()
{
}

void VertexBuffer::AddBuffer(const std::vector<Vertex>& vertices)
{
	Bind();
	GLCall(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW));
}

void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); // 将创建的顶点缓冲对象VBO绑定到GL_ARRAY_BUFFER目标上
}

void VertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::Delete() const
{
	 GLCall(glDeleteBuffers(1, &m_RendererID));
}
