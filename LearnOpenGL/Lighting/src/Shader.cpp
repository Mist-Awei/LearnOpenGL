#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	// 1.从文件路径中获取顶点/片段着色器
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// 保证ifstream对象可以抛出异常
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// 打开文件
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// 读取文件的缓冲内容到数据流中
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// 关闭文件处理器
		vShaderFile.close();
		fShaderFile.close();
		// 转换数据流到string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FAIL_NOT_SUCCESFULLY_READ\n" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	// 2. 编译着色器
	unsigned int vertex, fragment;
	int success;
	char infolog[512];
	// 顶点着色器
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");
	// 片段着色器
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");

	// 着色器程序
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");

	// 删除着色器
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::~Shader()
{
	// 删除着色器程序
	GLCall(glDeleteProgram(ID));
}

void Shader::Use() const
{
	GLCall(glUseProgram(ID));
}

void Shader::Unuse() const
{
	GLCall(glUseProgram(0));
}
// 打印编译错误
void Shader::checkCompileErrors(GLuint shader, std::string type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}

void Shader::setBool(const std::string& name, bool value)
{
	GLCall(glUniform1i(GetUniformLocation(name), (int)value));
}

void Shader::setInt(const std::string& name, int value)
{
	GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::setFloat(const std::string& name, float value)
{
	GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::setVec2(const std::string& name, const glm::vec2& value)
{
	GLCall(glUniform2fv(GetUniformLocation(name), 1, &value[0]));
}
void Shader::setVec2(const std::string& name, float x, float y)
{
	GLCall(glUniform2f(GetUniformLocation(name), x, y));
}
// ------------------------------------------------------------------------
void Shader::setVec3(const std::string& name, const glm::vec3& value)
{
	GLCall(glUniform3fv(GetUniformLocation(name), 1, &value[0]));
}
void Shader::setVec3(const std::string& name, float x, float y, float z)
{
	GLCall(glUniform3f(GetUniformLocation(name), x, y, z));
}
// ------------------------------------------------------------------------
void Shader::setVec4(const std::string& name, const glm::vec4& value)
{
	GLCall(glUniform4fv(GetUniformLocation(name), 1, &value[0]));
}
void Shader::setVec4(const std::string& name, float x, float y, float z, float w)
{
	GLCall(glUniform4f(GetUniformLocation(name), x, y, z, w));
}
// ------------------------------------------------------------------------
void Shader::setMat2(const std::string& name, const glm::mat2& mat)
{
	GLCall(glUniformMatrix2fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]));
}
// ------------------------------------------------------------------------
void Shader::setMat3(const std::string& name, const glm::mat3& mat)
{
	GLCall(glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]));
}
// ------------------------------------------------------------------------
void Shader::setMat4(const std::string& name, const glm::mat4& mat)
{
	// uniform变量的位置值，传递的个数，是否转置（OpenGL和glm均为列主序），矩阵数据（用value_ptr转换为OpenGL接受的格式）
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]));
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (UniformLocationCache.find(name) != UniformLocationCache.end())
	{
		return UniformLocationCache[name];
	}
	GLCall(int location = glGetUniformLocation(ID, name.c_str()));
	if (location == -1)
	{
		std::cout << "ERROR::UNIFORM::" << name << "_DOESNT_EXIST" << std::endl;
	}
	else
	{
		UniformLocationCache[name] = location;
	}
	return location;
}