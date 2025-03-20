#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal; // 法线向量
layout (location = 2) in vec2 aTexcoords; // 纹理坐标

out VS_OUT {
    vec2 texCoords;
    vec3 normal;
} vs_out;

layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};
uniform mat4 model;

void main()
{
	vs_out.texCoords = aTexcoords;
    vs_out.normal = aNormal;
	gl_Position = vec4(aPos, 1.0);
}