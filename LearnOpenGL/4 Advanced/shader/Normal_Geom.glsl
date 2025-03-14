#version 330 core
layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

in VS_OUT {
    vec3 normal;
} gs_in[];

const float MAGNITUDE = 0.01;

layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};
uniform mat4 model;

mat4 mv = view * model;
mat3 normalMatrix = mat3(transpose(inverse(view * model)));


void GenerateLine(int index)
{
    gl_Position = projection * mv * gl_in[index].gl_Position;
    EmitVertex();
    vec4 ptOnNormal = mv * gl_in[index].gl_Position + vec4(normalize(normalMatrix * gs_in[index].normal) * MAGNITUDE, 0.0f);
    gl_Position = projection * ptOnNormal;
    EmitVertex();
    EndPrimitive();
}

void main()
{
    GenerateLine(0); // 第一个顶点法线
    GenerateLine(1); // 第二个顶点法线
    GenerateLine(2); // 第三个顶点法线
}