#version 330 core
layout (location = 0) in vec3 aPos; // 位置变量的属性位置值为0
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord; // 纹理坐标属性

out vec4 ourColor; // 为片段着色器指定一个输出
out vec2 TexCoord;

// uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	ourColor = gl_Position;
	TexCoord = aTexCoord;
}