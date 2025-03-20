#include "FrameBuffer.h"
#include "CallError.h"

FrameBuffer::FrameBuffer()
{
	// 创建帧缓冲对象
	GLCall(glGenFramebuffers(1, &m_RendererID));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));
}

FrameBuffer::~FrameBuffer()
{
	GLCall(glDeleteFramebuffers(1, &m_RendererID));
}

void FrameBuffer::Bind() const
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));
}

void FrameBuffer::Unbind() const
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void FrameBuffer::AddTexture(Texture& texture) const
{
	Bind();
	// 帧缓冲的目标（绘制或读取），附件类型（颜色、深度、模板），纹理类型，纹理本身，多级渐远纹理的级别
	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.GetId(), 0));
}

void FrameBuffer::AddBuffer(RenderBuffer& RBO) const
{
	Bind();
	GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO.GetId()));
}

void FrameBuffer::Delete() const
{
	GLCall(glDeleteFramebuffers(1, &m_RendererID));
}
