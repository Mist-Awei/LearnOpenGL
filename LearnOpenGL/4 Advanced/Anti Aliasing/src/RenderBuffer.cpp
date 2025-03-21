#include "RenderBuffer.h"
#include "CallError.h"

RenderBuffer::RenderBuffer()
{
	glGenRenderbuffers(1, &m_RendererID);
	//glBindRenderbuffer(GL_RENDERBUFFER, m_RendererID);
}

RenderBuffer::~RenderBuffer()
{
	GLCall(glDeleteRenderbuffers(1, &m_RendererID));
}

void RenderBuffer::Bind() const
{
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_RendererID));
}

void RenderBuffer::SetStorage(unsigned int width, unsigned int height) const
{
	Bind();
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
}

void RenderBuffer::SetMultiSampleStorage(unsigned int width, unsigned int height, unsigned int sample) const
{
	Bind();
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, sample, GL_DEPTH24_STENCIL8, width, height);
}

void RenderBuffer::Unbind() const
{
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
}

void RenderBuffer::Delete() const
{
	GLCall(glDeleteRenderbuffers(1, &m_RendererID));
}
