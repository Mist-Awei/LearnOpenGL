#version 330 core
layout (location = 0) in vec3 aPos; // 位置变量的属性位置值为0
layout (location = 1) in vec3 aNormol;

out vec3 LightColor;

uniform vec3 lightPos;
// MVP变换
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightColor;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	vec3 ShaderPos = vec3(view * model * vec4(aPos, 1.0f));
	vec3 Normal = mat3(transpose(inverse(view * model))) * aNormol; // 法线矩阵移除对法线向量错误缩放的影响
	vec3 LightPos = vec3(view * model * vec4(lightPos, 1.0f));

	float ambientStrength = 0.1f; // 环境光强度
	float specularStrength = 1.0f; // 高光强度
	
	// 环境光（ambient）
	vec3 ambient = ambientStrength * lightColor;

	// 漫反射光（diffuse）
	vec3 normal = normalize(Normal); // 顶点法线向量
	vec3 lightDir = normalize(LightPos - ShaderPos); // 光照方向向量
	float diff = max(dot(normal, lightDir), 0.0f); // 漫反射强度
	vec3 diffuse = diff * lightColor; // 漫反射
	
	// 高光（specular）
	vec3 viewDir = normalize(-ShaderPos); // 视线方向向量（观察空间下观察者的坐标为0，0，0）
	vec3 reflectDir = reflect(-lightDir, normal); // 反射向量
	// 视线方向和反射方向越接近，高光越强
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
	vec3 specular = spec * lightColor; // 高光

	// 最终顶点的颜色
	LightColor = ambient + diffuse + specular;
}