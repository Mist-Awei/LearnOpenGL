#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal; // 法线向量
layout (location = 2) in vec2 aTexcoords; // 纹理坐标

out vec2 TexCoords; 
out vec3 Position;
out vec3 Normal;

layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};
uniform mat4 model;

void main()
{
    mat3 normalMatrix = mat3(transpose(inverse(view * model)));
	TexCoords = aTexcoords;
    Normal = normalize(normalMatrix * aNormal);
    Position = vec3(model * vec4(aPos, 1.0));
	gl_Position = projection * view * model * vec4(aPos, 1.0);
}