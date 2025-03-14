#version 330 core
out vec4 FragColor;

in vec3 Normal; // ����ռ��µķ�������
in vec3	FragPos; // ����ռ��µĶ�������
in vec2 TexCoords;

// �����(Directional Light)
struct DirectionalLight { 
	vec3 direction; // ��Դ����Զƽ�й⣬ֱ��ʹ�ù��շ�������
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct Material {
	sampler2D diffuse; //��������ɫ�ڼ�����������¶�������������ɫ���������ǲ���Ҫ�����Ƿֿ�����
	sampler2D specular;
	float shininess;
};

uniform DirectionalLight light;
uniform Material material;
uniform vec3 viewPos;

void main()
{	
	// �����⣨ambient��
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	
	// ������⣨diffuse��
	vec3 normal = normalize(Normal); // ���㷨������
	vec3 lightDir = normalize(-light.direction); // ���շ���������Ƭ�ζ���ָ�����
	float diff = max(dot(normal, lightDir), 0.0f); // ������ǿ��
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords)); // ������
	
	// �߹⣨specular��
	vec3 viewDir = normalize(viewPos - FragPos); // ���߷�������
	vec3 reflectDir = reflect(-lightDir, normal); // ��������
	// ���߷���ͷ��䷽��Խ�ӽ����߹�Խǿ
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords)); // �߹�

	// ����Ƭ�ε���ɫ
	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result, 1.0f);
}