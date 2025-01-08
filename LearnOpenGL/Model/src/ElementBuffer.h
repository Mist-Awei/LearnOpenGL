#ifndef ELEMENTBUFFER_H
#define ELEMENTBUFFER_H

#include <vector>

class ElementBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
public:
	ElementBuffer(const unsigned int* data, unsigned int count);
	ElementBuffer();
	~ElementBuffer();

	inline unsigned int GetCount() const
	{
		return m_Count;
	}

	void Bind() const;
	void AddBuffer(const std::vector<unsigned int>& indices);
	void Unbind() const;
	void Delete();
};

#endif // !ELEMENTBUFFER_H
