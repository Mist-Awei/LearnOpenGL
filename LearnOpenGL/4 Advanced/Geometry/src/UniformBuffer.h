#pragma once
class UniformBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_Size = 0;
public:
	UniformBuffer(const unsigned int size);
	~UniformBuffer();
	void Bind() const;
	void UpdateData(const void* data, const unsigned int size, const unsigned int offset = 0) const;
	void SetBindingPoint(const unsigned int bindingPoint, const unsigned int lowRange = 0, const unsigned int upRange = 0) const;
	void Unbind() const;
	void Delete() const;
};