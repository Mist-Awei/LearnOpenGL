#pragma once

#include <string>
#include <vector>

#include "CallError.h"

class Texture
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	std::string type;
	int m_Width, m_Height, m_BPP;
public:
	Texture(); // Ĭ�Ϲ��캯��
	Texture(const std::string& path, const bool flipUV = true);
	Texture(std::vector<std::string> faces, const bool flipUV = false); // ����CubeMap
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void CubeBind(unsigned int slot = 0) const;
	void Unbind() const;

	inline unsigned int GetId() const { return m_RendererID; }
};