#include "UniformBuffer.h"
#include "CallError.h"
#include <time.h>

UniformBuffer::UniformBuffer(const unsigned int size)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_UNIFORM_BUFFER, m_RendererID);
	glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_STATIC_DRAW); // 分配size字节的内存
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	m_Size = size;
}

UniformBuffer::~UniformBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void UniformBuffer::Bind() const
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_RendererID);
}

void UniformBuffer::UpdateData(const void * data, const unsigned int size, const unsigned int offset) const
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_RendererID);
	glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBuffer::SetBindingPoint(const unsigned int bindingPoint, const unsigned int lowRange, const unsigned int upRange) const
{
	if (upRange == 0)
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, m_RendererID);
	}
	else
	{
		glBindBufferRange(GL_UNIFORM_BUFFER, bindingPoint, m_RendererID, lowRange, upRange);
	}
}

void UniformBuffer::Unbind() const
{
}

void UniformBuffer::Delete() const
{
	glDeleteBuffers(1, &m_RendererID);
}
