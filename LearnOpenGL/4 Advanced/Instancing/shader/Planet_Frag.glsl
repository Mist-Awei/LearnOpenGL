#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;

// 定向光(Directional Light)
struct DirLight { 
	vec3 direction; // 光源无限远平行光，直接使用光照方向向量
	
	vec3 diffuse;
};

struct Materials
{
    sampler2D texture_diffuse1;
};

uniform DirLight dirlight;
uniform Materials material;

vec3 CalcDirLight(DirLight light, vec3 normal);

void main()
{
	vec3 normal = normalize(Normal);
	FragColor = vec4(CalcDirLight(dirlight, normal), 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal)
{
	// 漫反射光（diffuse）
	vec3 lightDir = normalize(-light.direction); // 光照方向向量，片段顶点指向光照
	float diff = max(dot(normal, lightDir), 0.2f); // 漫反射强度
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse1, TexCoords)); // 漫反射
	
	// 定向光返回颜色
	return diffuse;
}
