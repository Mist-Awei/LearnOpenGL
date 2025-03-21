#include "VertexBuffer.h"
#include "CallError.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	GLCall(glGenBuffers(1, &m_RendererID)); // ����һ�����л���ID�Ķ��㻺�����VBO
	// �Ѷ������鸴�Ƶ������й�OpenGLʹ��.���㻺�����Ļ���������GL_ARRAY_BUFFER
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); // �������Ķ��㻺�����VBO�󶨵�GL_ARRAY_BUFFERĿ����
	// ���û�����Ķ������ݸ��Ƶ���ǰ�󶨵Ļ���������
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); // �������Ķ��㻺�����VBO�󶨵�GL_ARRAY_BUFFERĿ����
}

void VertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::Delete() const
{
	 GLCall(glDeleteBuffers(1, &m_RendererID));
}
