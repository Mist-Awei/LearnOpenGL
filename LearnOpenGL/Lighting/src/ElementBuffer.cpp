#include "ElementBuffer.h"
#include "CallError.h"

ElementBuffer::ElementBuffer(const unsigned int* data, unsigned int count) : m_Count(count)
{
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));

	GLCall(glGenBuffers(1, &m_RendererID));
	// �����������鵽һ�����������У���OpenGLʹ��.Ԫ�ػ������Ļ���������GL_ELEMENT_ARRAY_BUFFER
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

ElementBuffer::~ElementBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void ElementBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); // �������Ķ��㻺�����VBO�󶨵�GL_ARRAY_BUFFERĿ����
}

void ElementBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
