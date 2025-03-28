#include "VertexArray.h"
#include "CallError.h"

VertexArray::VertexArray()
{
    // 创建VAO
    GLCall(glGenVertexArrays(1, &m_RendererID));
    GLCall(glBindVertexArray(m_RendererID));
}

VertexArray::~VertexArray()
{
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
        // 设置顶点属性指针,配置顶点属性（layout position位置值），数据类型，是否标准化，
        // 步长（连续的顶点属性组的间隔），位置缓冲在起始位置时的偏移量
        // 顶点位置属性
        GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
        GLCall(glEnableVertexAttribArray(i)); //顶点属性位置值为参数，启用顶点属性
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
}

void VertexArray::Bind() const
{
    // 绑定VAO
    GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
    // 解绑VAO
    GLCall(glBindVertexArray(0));
}

void VertexArray::Delete() const
{
    // 释放VAO
    GLCall(glDeleteVertexArrays(1, &m_RendererID));
}
