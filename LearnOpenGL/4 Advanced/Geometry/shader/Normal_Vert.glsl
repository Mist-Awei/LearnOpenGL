#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out VS_OUT {
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
//    mat3 normalMatrix = mat3(transpose(inverse(view * model)));
//    gl_Position = projection * view * model * vec4(aPos, 1.0); 
    vs_out.normal = aNormal;
    gl_Position = vec4(aPos, 1.0); 
}