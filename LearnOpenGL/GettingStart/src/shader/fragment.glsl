#version 330 core
in vec4 ourColor;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixValue;

void main()
{
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(TexCoord.x, TexCoord.y)), mixValue); // texture函数来采样纹理颜色（纹理采样器，纹理坐标）
}