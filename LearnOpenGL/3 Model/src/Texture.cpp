#include "Texture.h"

#include <string>
#include <windows.h>

#include "stb_image/stb_image.h"

Texture::Texture(const std::string& path, const std::string& directory)
    : m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
    std::string filename = path.c_str();
    if (!directory.empty())
    {
        filename = directory + '/' + filename;
    }
    /*
    // ��ȡ����Ŀ��ַ�����
    int len = MultiByteToWideChar(CP_ACP, 0, filename.c_str(), -1, NULL, 0);
    // �����㹻���ڴ沢ת���ַ���
    std::wstring wstr(len, L'\0');  // ʹ��std::wstring������ָ��
    // ת���ַ���
    MultiByteToWideChar(CP_ACP, 0, filename.c_str(), -1, &wstr[0], len);
    FILE* f = nullptr;
    errno_t err = _wfopen_s(&f, wstr.c_str(), L"rb");  // ʹ��wstr.c_str()ֱ�Ӵ��ݸ� _wfopen_s
    if (err != 0)
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    else
    {
        // ���ز���������
        stbi_set_flip_vertically_on_load(true);
        // m_BPP = nrChannels;
        m_LocalBuffer = stbi_load_from_file(f, &m_Width, &m_Height, &m_BPP, 0); // ������ͼ��Ŀ�ߺ���ɫͨ����������Ӧ����
        fclose(f);
    }
    */
    // ���ز���������
    stbi_set_flip_vertically_on_load(true);
    // m_BPP = nrChannels;
    m_LocalBuffer = stbi_load(filename.c_str(), &m_Width, &m_Height, &m_BPP, 0); // ������ͼ��Ŀ�ߺ���ɫͨ����������Ӧ����
    if (m_LocalBuffer)
    {
        GLenum format = GL_RGBA; // ͨ���ж���ɫͨ������ȷ��ͼƬ����
        GLenum innterFormat = GL_RGBA;
        if (m_BPP == 1)
        {
            format = GL_RED;
            innterFormat = GL_RED;
        }
        else if (m_BPP == 2)
        {
            format = GL_RG;
            innterFormat = GL_RGBA8;
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
        // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor); // ʹ��clamp_to_border��Ҫʹ��fv��׺����ָ����Ե��ɫ
        // Ϊ��ǰ�󶨵�����������û��ƺ͹��˷�ʽ
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // ��һ������ָ������Ŀ�꣬�ڶ�������Ϊ�����ƶ��༶��Զ����ļ��𣬵���������Ϊ����洢�ĸ�ʽ�����ĵ��������������Ŀ��
        // ������������Ϊ0����ʷ�������⣩�����ߵڰ˸�����������Դͼ�ĸ�ʽ���������ͣ����һ��������ͼ������
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, innterFormat, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, m_LocalBuffer));
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

void Texture::Delete() const
{
     GLCall(glDeleteTextures(1, &m_RendererID));
}
