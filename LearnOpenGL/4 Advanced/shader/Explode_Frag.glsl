#version 330 core
out vec4 FragColor;

in vec3 Position;
in vec3 Normal;
in vec2 TexCoords;

// ����
struct Material {
	sampler2D texture_diffuse1;
	sampler2D texture_specular1;
	sampler2D texture_reflection1;
};

// �����(Directional Light)
struct DirLight { 
	vec3 direction; // ��Դ����Զƽ�й⣬ֱ��ʹ�ù��շ�������
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform vec3 cameraPos;
uniform samplerCube skybox;
uniform Material material;
uniform DirLight sun;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec4 EnvironmentReflection(vec3 normal, vec3 viewDir); // ���㻷��ӳ�䷴��
vec3 EnvironmentRefraction(vec3 normal, vec3 viewDir); // ���㻷��ӳ������

void main()
{
	vec3 I = normalize(Position - cameraPos);
	vec3 normal = normalize(Normal); // ���㷨������
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
	// �����⣨ambient��
	vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, TexCoords));
	
	// ������⣨diffuse��
	vec3 lightDir = normalize(-light.direction); // ���շ���������Ƭ�ζ���ָ�����
	float diff = max(dot(normal, lightDir), 0.0f); // ������ǿ��
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse1, TexCoords)); // ������
	
	// ����⣨specular��
	vec3 reflectDir = reflect(-lightDir, normal); // ��������
	// ���߷���ͷ��䷽��Խ�ӽ����߹�Խǿ
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
	vec3 specular = light.specular * spec * vec3(texture(material.texture_specular1, TexCoords)); // �߹�

	// ����ⷵ����ɫ
	return (ambient + diffuse + specular);
}