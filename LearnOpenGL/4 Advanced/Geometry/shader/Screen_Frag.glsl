#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

vec4 GetInversion(vec4 color); // 反相
vec4 GetGray(vec4 color); // 灰度化
vec4 KernelProcess(uint kernel); // 核效果（卷积矩阵）

const float offset = 1.0f / 300.0f;
const uint sharpen = 0, blur = 1, edge = 2;

void main()
{
    FragColor = texture(screenTexture, TexCoords);
    // FragColor = KernelProcess(uint(3));
}

vec4 GetInversion(vec4 color)
{
    vec4 Color = vec4(vec3(1.0 - color), 1.0f); // 反相
    return Color;
}

vec4 GetGray(vec4 color)
{
    float average = 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;
    vec4 Color = vec4(average, average, average, 1.0f);
    return Color;
}

vec4 KernelProcess(uint kernel)
{
    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // 左上
        vec2( 0.0f,    offset), // 正上
        vec2( offset,  offset), // 右上
        vec2(-offset,  0.0f),   // 左
        vec2( 0.0f,    0.0f),   // 中
        vec2( offset,  0.0f),   // 右
        vec2(-offset, -offset), // 左下
        vec2( 0.0f,   -offset), // 正下
        vec2( offset, -offset)  // 右下
    );
    float Kernel[9] = float[](
            0, 0, 0,
            0, 1, 0,
            0, 0, 0
         );
    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(screenTexture, TexCoords.st + offsets[i]));
    }
    vec3 Color = vec3(0.0f);
    switch(kernel)
    {
    case sharpen:
        Kernel = float[](
        -1, -1, -1,
        -1, 9, -1,
        -1, -1, -1
        );
        break;
    case blur:
        Kernel = float[](
            1.0 / 16, 2.0 / 16, 1.0 / 16,
            2.0 / 16, 4.0 / 16, 2.0 / 16,
            1.0 / 16, 2.0 / 16, 1.0 / 16
         );
        break;
    case edge:
        Kernel = float[](
        1, 2, 1,
        0, 0, 0,
        -1, -2, -1
        );
        break;
    }
    for(int i =0; i < 9; i++)
    {
        Color += sampleTex[i] * Kernel[i];
    }
    return vec4(Color, 1.0f);
}