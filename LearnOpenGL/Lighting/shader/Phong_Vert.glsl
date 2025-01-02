#version 330 core
layout (location = 0) in vec3 aPos; // 位置变量的属性位置值为0
layout (location = 1) in vec3 aNormol; // 法线向量
layout (location = 2) in vec2 aTexcoords; // 纹理坐标

out vec3 FragPos; // 世界空间下的顶点坐标
out vec3 Normal; // 世界空间下的法线向量
out vec2 TexCoords;

// MVP变换
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	FragPos = vec3(model * vec4(aPos, 1.0f));
	Normal = mat3(transpose(inverse(model))) * aNormol; // 法线矩阵移除对法线向量错误缩放的影响
	TexCoords = aTexcoords;
}