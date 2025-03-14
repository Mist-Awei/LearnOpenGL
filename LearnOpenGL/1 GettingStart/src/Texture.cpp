#include "Texture.h"

#include "stb_image/stb_image.h"

Texture::Texture(const std::string& path, const unsigned int type)
	: m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);
    // float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor); // 使用clamp_to_border需要使用fv后缀函数指定边缘颜色
    // 为当前绑定的纹理对象设置环绕和过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 加载并生成纹理
    stbi_set_flip_vertically_on_load(true);
    // m_BPP = nrChannels;
    m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 0); // 将会用图像的宽高和颜色通道个数填充对应变量
    if (m_LocalBuffer)
    {
        // 第一个参数指定纹理目标，第二个参数为纹理制定多级渐远纹理的级别，第三个参数为纹理存储的格式，第四第五参数设置纹理的宽高
        // 第六参数总设为0（历史遗留问题），第七第八个参数定义了源图的格式和数据类型，最后一个参数是图像数据
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, type, GL_UNSIGNED_BYTE, m_LocalBuffer));
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(m_LocalBuffer); // 释放图像内存
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

Texture::~Texture()
{
    GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::Bind(unsigned int slot) const
{
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::Unbind() const
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
