#include "RenderBuffer.h"
#include "CallError.h"

RenderBuffer::RenderBuffer()
{
	glGenRenderbuffers(1, &m_RendererID);
	glBindRenderbuffer(GL_RENDERBUFFER, m_RendererID);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
}

RenderBuffer::~RenderBuffer()
{
	GLCall(glDeleteRenderbuffers(1, &m_RendererID));
}

void RenderBuffer::Bind() const
{
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_RendererID));
}

void RenderBuffer::Unbind() const
{
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
}

void RenderBuffer::Delete() const
{
	GLCall(glDeleteRenderbuffers(1, &m_RendererID));
}
