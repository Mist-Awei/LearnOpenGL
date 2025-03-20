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
    if(texColor.a < 0.1) // ���alphaֵ�Ƿ����ĳ����ֵ��͸������
        discard;
    FragColor = texColor;
    // float depth = LinearizeDepth(gl_FragCoord.z) / far;
    // FragColor = vec4(vec3(depth), 1.0f);
}

float LinearizeDepth(float depth)
{
    float z = depth * 2.0f - 1.0f; // ת����NDC
    return (2.0f * near * far) / (far + near - z * (far - near));
}