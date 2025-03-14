#include "Texture.h"

#include "stb_image/stb_image.h"

Texture::Texture(const std::string& path, const unsigned int type)
	: m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);
    // float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor); // ʹ��clamp_to_border��Ҫʹ��fv��׺����ָ����Ե��ɫ
    // Ϊ��ǰ�󶨵�����������û��ƺ͹��˷�ʽ
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // ���ز���������
    stbi_set_flip_vertically_on_load(true);
    // m_BPP = nrChannels;
    m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 0); // ������ͼ��Ŀ�ߺ���ɫͨ����������Ӧ����
    if (m_LocalBuffer)
    {
        // ��һ������ָ������Ŀ�꣬�ڶ�������Ϊ�����ƶ��༶��Զ����ļ��𣬵���������Ϊ����洢�ĸ�ʽ�����ĵ��������������Ŀ��
        // ������������Ϊ0����ʷ�������⣩�����ߵڰ˸�����������Դͼ�ĸ�ʽ���������ͣ����һ��������ͼ������
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, type, GL_UNSIGNED_BYTE, m_LocalBuffer));
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(m_LocalBuffer); // �ͷ�ͼ���ڴ�
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
