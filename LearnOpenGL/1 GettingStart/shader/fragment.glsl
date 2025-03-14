#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float MixValue;

void main()
{
	// texture函数来采样纹理颜色（纹理采样器，纹理坐标）
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), MixValue);
}
