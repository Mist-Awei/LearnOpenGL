#include "FrameBuffer.h"
#include "CallError.h"

FrameBuffer::FrameBuffer()
{
	// ����֡�������
	GLCall(glGenFramebuffers(1, &m_RendererID));
	//GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));
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

void FrameBuffer::AddAttachment(Texture& texture, RenderBuffer& RBO) const
{
	Bind();
	// ֡�����Ŀ�꣨���ƻ��ȡ�����������ͣ���ɫ����ȡ�ģ�壩���������ͣ��������༶��Զ����ļ���
	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.GetId(), 0));
	GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO.GetId()));
}

void FrameBuffer::AddMultiSampleAttachment(Texture& texture, RenderBuffer& RBO) const // Ϊ֡������Ӷ��ز�������������ͻ��壩
{
	Bind();
	// ֡�����Ŀ�꣨���ƻ��ȡ�����������ͣ���ɫ����ȡ�ģ�壩���������ͣ��������༶��Զ����ļ���
	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, texture.GetId(), 0));
	GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO.GetId()));
}

void FrameBuffer::Delete() const
{
	GLCall(glDeleteFramebuffers(1, &m_RendererID));
}
