#include "VertexArray.h"
#include "CallError.h"

VertexArray::VertexArray()
{
    // ����VAO
    GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
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
    // ������ɫ����
    // GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))));
    // GLCall(glEnableVertexAttribArray(1));
    // ��������λ������
    // GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))));
    // GLCall(glEnableVertexAttribArray(2));
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
