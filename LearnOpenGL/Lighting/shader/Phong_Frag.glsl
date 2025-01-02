#version 330 core
out vec4 FragColor;

in vec3 Normal; // ����ռ��µķ�������
in vec3	FragPos; // ����ռ��µĶ�������
in vec2 TexCoords;

// �����(Directional Light)
struct DirLight { 
	vec3 direction; // ��Դ����Զƽ�й⣬ֱ��ʹ�ù��շ�������
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

// ���Դ��PointLight��
struct PointLight {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant; // ˥��������Kc��ͨ������Ϊ1.0����ֹ��ĸС��1��ĳЩ����ǿ�ȷ�������
	float linear; // ˥��һ����Kl�����Եݼ�����ǿ��
	float quadratic; // ˥��������Kq�����Σ�ƽ�����ݼ�ǿ�ȣ���ʱ�ݼ�����Զʱ�ݼ���
};

// �۹⣨Spotlight��
struct SpotLight { 
	vec3 position; // �۹��λ������
	vec3 direction; // �۹���ָ����ķ�������
	float innerCutOff; // ���й��
	float outerCutOff; // ���й��

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

// ����
struct Material {
	sampler2D diffuse; //��������ɫ�ڼ�����������¶�������������ɫ���������ǲ���Ҫ�����Ƿֿ�����
	sampler2D specular;
	float shininess;
};

#define NR_POINT_LIGHTS 4
uniform DirLight sun;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight flashLight;
uniform Material material;
uniform vec3 viewPos;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{	
	vec3 normal = normalize(Normal); // ���㷨������
	vec3 viewDir = normalize(viewPos - FragPos); // ���߷�������

	// �����Դ
	vec3 result = CalcDirLight(sun, normal, viewDir);
	// ���Դ
	for(int i = 0;i < NR_POINT_LIGHTS;i++)
	{
		result += CalcPointLight(pointLights[i], normal, FragPos, viewDir);
	}
	// �۹�Դ
	result += CalcSpotLight(flashLight, normal, FragPos, viewDir);

	FragColor = vec4(result, 1.0f);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	// �����⣨ambient��
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	
	// ������⣨diffuse��
	vec3 lightDir = normalize(-light.direction); // ���շ���������Ƭ�ζ���ָ�����
	float diff = max(dot(normal, lightDir), 0.0f); // ������ǿ��
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords)); // ������
	
	// ����⣨specular��
	vec3 reflectDir = reflect(-lightDir, normal); // ��������
	// ���߷���ͷ��䷽��Խ�ӽ����߹�Խǿ
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords)); // �߹�

	// ����ⷵ����ɫ
	return (ambient + diffuse + specular);
}
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	// �����⣨ambient��
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	
	// ������⣨diffuse��
	vec3 lightDir = normalize(light.position - FragPos); // ���շ���������Ƭ�ζ���ָ�����
	float diff = max(dot(normal, lightDir), 0.0f); // ������ǿ��
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords)); // ������
	
	// ����⣨specular��
	vec3 reflectDir = reflect(-lightDir, normal); // ��������
	// ���߷���ͷ��䷽��Խ�ӽ����߹�Խǿ
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords)); // �߹�
	
	// ���հ�����˥��
	float distance = length(light.position - FragPos);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	ambient *= attenuation; 
	diffuse *= attenuation;
	specular *= attenuation;

	// ���Դ������ɫ
	return (ambient + diffuse + specular);
}
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	// �����⣨ambient��
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	
	// ������⣨diffuse��
	vec3 lightDir = normalize(light.position - FragPos); // ���շ���������Ƭ�ζ���ָ�����
	float diff = max(dot(normal, lightDir), 0.0f); // ������ǿ��
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords)); // ������
	
	// ����⣨specular��
	vec3 reflectDir = reflect(-lightDir, normal); // ��������
	// ���߷���ͷ��䷽��Խ�ӽ����߹�Խǿ
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords)); // �߹�
	// ƽ������
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.innerCutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);

	// ���հ�����˥��
	float distance = length(light.position - FragPos);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	ambient *= attenuation; // ������һ�㻷����
	diffuse *= attenuation * intensity;
	specular *= attenuation * intensity;
	// �۹ⷵ�ص���ɫ
	return (ambient + diffuse + specular);
}