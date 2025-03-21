#include "Texture.h"

#include <string>
#include <windows.h>

#include "stb_image/stb_image.h"

Texture::Texture(const GLenum type)
    : m_RendererID(0), m_LocalBuffer(nullptr), m_Type(type), m_Width(0), m_Height(0), m_BPP(0)
{
    // 生成纹理
    glBindTexture(type, 0);
    glGenTextures(1, &m_RendererID);
    glBindTexture(m_Type, m_RendererID);
    if (m_Type == GL_TEXTURE_2D)
    {
        glTexImage2D(m_Type, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(m_Type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(m_Type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else if (m_Type == GL_TEXTURE_2D_MULTISAMPLE)
    {
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGB, 800, 600, GL_TRUE);
    }
    glBindTexture(m_Type, 0);
}

Texture::Texture(const std::string& path, const bool flipUV)
    : m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
    std::string filename = path.c_str();
    
    // 加载并生成纹理
    stbi_set_flip_vertically_on_load(flipUV);
    // m_BPP = nrChannels;
    m_LocalBuffer = stbi_load(filename.c_str(), &m_Width, &m_Height, &m_BPP, 0); // 将会用图像的宽高和颜色通道个数填充对应变量
    if (m_LocalBuffer)
    {
        GLenum format = GL_RGBA; // 通过判断颜色通道个数确定图片类型
        GLenum innterFormat = GL_RGBA;
        GLenum wrapMode = GL_REPEAT;
        if (m_BPP == 1)
        {
            format = GL_RED;
            innterFormat = GL_RED;
        }
        else if (m_BPP == 3)
        {
            format = GL_RGB;
            innterFormat = GL_RGB;
        }
        else if (m_BPP == 4)
        {
            format = GL_RGBA;
            innterFormat = GL_RGBA;
        }
        GLCall(glGenTextures(1, &m_RendererID));
        GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
        // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor); // 使用clamp_to_border需要使用fv后缀函数指定边缘颜色
        // 为当前绑定的纹理对象设置环绕和过滤方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // 第一个参数指定纹理目标，第二个参数为纹理制定多级渐远纹理的级别，第三个参数为纹理存储的格式，第四第五参数设置纹理的宽高
        // 第六参数总设为0（历史遗留问题），第七第八个参数定义了源图的格式和数据类型，最后一个参数是图像数据
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, innterFormat, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, m_LocalBuffer));
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(m_LocalBuffer); // 释放图像内存
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

Texture::Texture(std::vector<std::string> faces, const bool flipUV)
    :m_RendererID(0), m_FilePath(faces[0].c_str()), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);
    
    stbi_set_flip_vertically_on_load(flipUV);
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char* data = stbi_load(faces[i].c_str(), &m_Width, &m_Height, &m_BPP, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
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

void Texture::CubeBind(unsigned int slot) const
{
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID));
}

void Texture::Unbind() const
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}