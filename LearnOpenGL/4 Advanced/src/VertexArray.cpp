#include "VertexArray.h"
#include "CallError.h"

VertexArray::VertexArray()
{
    // ����VAO
    GLCall(glGenVertexArrays(1, &m_RendererID));
    GLCall(glBindVertexArray(m_RendererID));
}

VertexArray::~VertexArray()
{
	// �ͷ�VAO
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& VBO, const VertexBufferLayout& layout)
{
    Bind();
	VBO.Bind();

    const auto& elements = layout.GetElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        // ���ö�������ָ��,���ö������ԣ�layout positionλ��ֵ�����������ͣ��Ƿ��׼����
        // �����������Ķ���������ļ������λ�û�������ʼλ��ʱ��ƫ����
        // ����λ������
        GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
        GLCall(glEnableVertexAttribArray(i)); //��������λ��ֵΪ���������ö�������
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
}

void VertexArray::BatchedAddBuffer(const VertexBuffer& VBO, const void* data, unsigned int size, unsigned int stride, unsigned int type)
{
    VBO.Bind();
    Bind();
    // ��仺��
    GLCall(glBufferSubData(GL_ARRAY_BUFFER, m_AttributeOffset, size, data));
    // ���ö�������ָ��
    GLCall(glVertexAttribPointer(m_AttributeCounts, stride, type, GL_FALSE, stride * sizeof(type), (const void*)m_AttributeOffset));
    GLCall(glEnableVertexAttribArray(m_AttributeCounts)); //��������λ��ֵΪ���������ö�������
    m_AttributeCounts++;
    m_AttributeOffset += size;
}

void VertexArray::Bind() const
{
    // ��VAO
    GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
    // ���VAO
    GLCall(glBindVertexArray(0));
}

void VertexArray::Delete() const
{
    // �ͷ�VAO
    GLCall(glDeleteVertexArrays(1, &m_RendererID));
}
