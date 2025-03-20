#pragma once
class RenderBuffer
{
private:
	unsigned int m_RendererID;
public:
	RenderBuffer();
	~RenderBuffer();
	void Bind() const;
	void Unbind() const;
	void Delete() const;

	inline unsigned int GetId() const { return m_RendererID; }
};

