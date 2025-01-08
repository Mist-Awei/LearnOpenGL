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
	std::string directory;
	std::string type;
	int m_Width, m_Height, m_BPP;
public:
	Texture() {}; // 默认构造函数
	Texture(const std::string& path, const std::string& directory = "");
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;
	void Delete() const;

	void SetType(const std::string& typeName) { type = typeName; }
	inline std::string GetType() const { return type; }
	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
};