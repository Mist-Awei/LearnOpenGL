#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;

float near = 0.1f;
float far = 100.0f;

float LinearizeDepth(float depth);

void main()
{
    vec4 texColor = texture(texture1, TexCoords);
    if(texColor.a < 0.1) // 检测alpha值是否低于某个阈值，透明则丢弃
        discard;
    FragColor = texColor;
    // float depth = LinearizeDepth(gl_FragCoord.z) / far;
    // FragColor = vec4(vec3(depth), 1.0f);
}

float LinearizeDepth(float depth)
{
    float z = depth * 2.0f - 1.0f; // 转换回NDC
    return (2.0f * near * far) / (far + near - z * (far - near));
}