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
	void AddTexture(Texture& texture) const;
	void AddBuffer(RenderBuffer& RBO) const;
	void Delete() const;
};

