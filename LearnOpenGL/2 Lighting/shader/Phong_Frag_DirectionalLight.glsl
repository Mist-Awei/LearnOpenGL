#version 330 core
out vec4 FragColor;

in vec3 Normal; // 世界空间下的法线向量
in vec3	FragPos; // 世界空间下的顶点坐标
in vec2 TexCoords;

// 定向光(Directional Light)
struct DirectionalLight { 
	vec3 direction; // 光源无限远平行光，直接使用光照方向向量
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct Material {
	sampler2D diffuse; //环境光颜色在几乎所有情况下都等于漫反射颜色，所以我们不需要将它们分开储存
	sampler2D specular;
	float shininess;
};

uniform DirectionalLight light;
uniform Material material;
uniform vec3 viewPos;

void main()
{	
	// 环境光（ambient）
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	
	// 漫反射光（diffuse）
	vec3 normal = normalize(Normal); // 顶点法线向量
	vec3 lightDir = normalize(-light.direction); // 光照方向向量，片段顶点指向光照
	float diff = max(dot(normal, lightDir), 0.0f); // 漫反射强度
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords)); // 漫反射
	
	// 高光（specular）
	vec3 viewDir = normalize(viewPos - FragPos); // 视线方向向量
	vec3 reflectDir = reflect(-lightDir, normal); // 反射向量
	// 视线方向和反射方向越接近，高光越强
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords)); // 高光

	// 最终片段的颜色
	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result, 1.0f);
}