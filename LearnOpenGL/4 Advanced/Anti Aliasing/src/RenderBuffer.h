#pragma once
class RenderBuffer
{
private:
	unsigned int m_RendererID;
public:
	RenderBuffer();
	~RenderBuffer();
	void Bind() const;
	void SetStorage(unsigned int width, unsigned int height) const;
	void SetMultiSampleStorage(unsigned int width, unsigned int height, unsigned int sample) const;
	void Unbind() const;
	void Delete() const;

	inline unsigned int GetId() const { return m_RendererID; }
};

