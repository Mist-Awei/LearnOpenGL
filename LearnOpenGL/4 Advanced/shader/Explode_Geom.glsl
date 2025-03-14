#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT {
    vec2 texCoords;
    vec3 normal;
} gs_in[];

out vec2 TexCoords; 
out vec3 Position;
out vec3 Normal;

uniform float time;
layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};
uniform mat4 model;

vec4 explode(vec4 position, vec3 normal);
vec3 GetNormal();

void main()
{
    mat4 vp = projection * view;
    vec3 normal = GetNormal();
    vec4 explodePosition;
    
    Normal = normal;
    
    explodePosition = model * explode(gl_in[0].gl_Position, normal);
    Position = explodePosition.xyz;
    TexCoords = gs_in[0].texCoords;
    gl_Position = vp * explodePosition;
    EmitVertex();

    explodePosition = model * explode(gl_in[1].gl_Position, normal);
    TexCoords = gs_in[1].texCoords;
    gl_Position = vp * explodePosition;
    EmitVertex();

    explodePosition = model * explode(gl_in[2].gl_Position, normal);
    TexCoords = gs_in[2].texCoords;
    gl_Position = vp * explodePosition;
    EmitVertex();
    EndPrimitive();
}

vec3 GetNormal()
{
    vec3 pos0 = gl_in[0].gl_Position.xyz;
    vec3 pos1 = gl_in[1].gl_Position.xyz;
    vec3 pos2 = gl_in[2].gl_Position.xyz;
    vec3 a = vec3(pos1 - pos0);
    vec3 b = vec3(pos2 - pos0);
    return normalize(cross(a, b));
}

vec4 explode(vec4 position, vec3 normal)
{
    float magnitude = 1.0;
    vec3 direction = normal * max(sin(time), 0.0) * magnitude;
    return position + vec4(direction, 0.0);
}