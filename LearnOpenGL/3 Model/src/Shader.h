#ifndef SHADER_H
#define SHADER_H

#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

#include "CallError.h"

class Shader
{
private:
	
	std::unordered_map<std::string, int> UniformLocationCache;
	void checkCompileErrors(GLuint shader, std::string type);
public:
	unsigned int ID; // ��ɫ������ID
	//��������ȡ��������ɫ��
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	// ʹ�û򼤻����
	void Use() const;
	void Unuse() const;
	void Delete() const;

	// uniform���ߺ���
	// glGetUniformLocation��ѯuniform��λ��ֵ������-1����δ�ҵ�
	// ����uniformǰ����ʹ�ù����򣬲�ѯλ��ֵ����֮ǰʹ�ù�����
	void setBool(const std::string& name, bool value);
	void setInt(const std::string& name, int value);
	void setFloat(const std::string& name, float value);
	void setVec2(const std::string& name, const glm::vec2& value);
	void setVec2(const std::string& name, float x, float y);
	void setVec3(const std::string& name, const glm::vec3& value);
	void setVec3(const std::string& name, float x, float y, float z);
	void setVec4(const std::string& name, const glm::vec4& value);
	void setVec4(const std::string& name, float x, float y, float z, float w);
	void setMat2(const std::string& name, const glm::mat2& mat);
	void setMat3(const std::string& name, const glm::mat3& mat);
	void setMat4(const std::string& name, const glm::mat4& mat);
	int GetUniformLocation(const std::string& name);
};

#endif // !SHADER_H