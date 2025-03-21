#pragma once
#include "Texture.h"
#include "RenderBuffer.h"

class FrameBuffer
{
private:
	unsigned int m_RendererID;
public:
	FrameBuffer();
	~FrameBuffer();
	void Bind() const;
	void Unbind() const;
	void AddAttachment(Texture& texture, RenderBuffer& RBO) const;
	void AddMultiSampleAttachment(Texture& texture, RenderBuffer& RBO) const;
	void Delete() const;
	unsigned int GetId() const { return m_RendererID; }
};

