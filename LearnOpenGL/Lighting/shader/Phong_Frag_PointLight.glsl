#version 330 core
out vec4 FragColor;

in vec3 Normal; // ����ռ��µķ�������
in vec3	FragPos; // ����ռ��µĶ�������
in vec2 TexCoords;

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

struct Material {
	sampler2D diffuse; //��������ɫ�ڼ�����������¶�������������ɫ���������ǲ���Ҫ�����Ƿֿ�����
	sampler2D specular;
	float shininess;
};

uniform PointLight light;
uniform Material material;
uniform vec3 viewPos;

void main()
{	
	// �����⣨ambient��
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	
	// ������⣨diffuse��
	vec3 normal = normalize(Normal); // ���㷨������
	vec3 lightDir = normalize(light.position - FragPos); // ���շ���������Ƭ�ζ���ָ�����
	float diff = max(dot(normal, lightDir), 0.0f); // ������ǿ��
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords)); // ������
	
	// �߹⣨specular��
	vec3 viewDir = normalize(viewPos - FragPos); // ���߷�������
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
	
	// ����Ƭ�ε���ɫ
	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result, 1.0f);
}