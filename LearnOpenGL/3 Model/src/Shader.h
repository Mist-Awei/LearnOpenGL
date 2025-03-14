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
	unsigned int ID; // 着色器程序ID
	//构造器读取并构建着色器
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	// 使用或激活程序
	void Use() const;
	void Unuse() const;
	void Delete() const;

	// uniform工具函数
	// glGetUniformLocation查询uniform的位置值，返回-1代表未找到
	// 更新uniform前必须使用过程序，查询位置值不必之前使用过程序
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