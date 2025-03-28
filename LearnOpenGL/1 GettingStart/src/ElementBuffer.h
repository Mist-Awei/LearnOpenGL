#ifndef ELEMENTBUFFER_H
#define ELEMENTBUFFER_H

class ElementBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
public:
	ElementBuffer(const unsigned int* data, unsigned int count);
	~ElementBuffer();

	inline unsigned int GetCount() const
	{
		return m_Count;
	}

	void Bind() const;
	void Unbind() const;
};

#endif // !ELEMENTBUFFER_H
