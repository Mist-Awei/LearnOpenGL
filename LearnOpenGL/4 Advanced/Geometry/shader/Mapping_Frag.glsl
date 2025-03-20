#version 330 core
out vec4 FragColor;

in vec3 Position;
in vec3 Normal;
in vec2 TexCoords;

// 材质
struct Material {
	sampler2D texture_diffuse1;
	sampler2D texture_specular1;
	sampler2D texture_reflection1;
};

// 定向光(Directional Light)
struct DirLight { 
	vec3 direction; // 光源无限远平行光，直接使用光照方向向量
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform vec3 cameraPos;
uniform samplerCube skybox;
uniform Material material;
uniform DirLight sun;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec4 EnvironmentReflection(vec3 normal, vec3 viewDir); // 计算环境映射反射
vec3 EnvironmentRefraction(vec3 normal, vec3 viewDir); // 计算环境映射折射

void main()
{
	vec3 I = normalize(Position - cameraPos);
	vec3 normal = normalize(Normal); // 顶点法线向量
	vec4 color =  vec4(CalcDirLight(sun, normal, I), 1.0f) + EnvironmentReflection(normal, I);
	FragColor = color;
}

vec4 EnvironmentReflection(vec3 normal, vec3 viewDir)
{
	vec3 R = reflect(viewDir, normal);
	vec4 reflect_intensity = texture(material.texture_reflection1, TexCoords);
	vec4 color = reflect_intensity * texture(skybox, R);
	return color;
}

vec3 EnvironmentRefraction(vec3 normal, vec3 viewDir)
{
	float ratio = 1.00 / 1.52;
    vec3 R = refract(viewDir, normal, ratio);
    vec3 color = texture(skybox, R).rgb;
	return color;
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	// 环境光（ambient）
	vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, TexCoords));
	
	// 漫反射光（diffuse）
	vec3 lightDir = normalize(-light.direction); // 光照方向向量，片段顶点指向光照
	float diff = max(dot(normal, lightDir), 0.0f); // 漫反射强度
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse1, TexCoords)); // 漫反射
	
	// 镜面光（specular）
	vec3 reflectDir = reflect(-lightDir, normal); // 反射向量
	// 视线方向和反射方向越接近，高光越强
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
	vec3 specular = light.specular * spec * vec3(texture(material.texture_specular1, TexCoords)); // 高光

	// 定向光返回颜色
	return (ambient + diffuse + specular);
}