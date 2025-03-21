#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;

// �����(Directional Light)
struct DirLight { 
	vec3 direction; // ��Դ����Զƽ�й⣬ֱ��ʹ�ù��շ�������
	
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
	// ������⣨diffuse��
	vec3 lightDir = normalize(-light.direction); // ���շ���������Ƭ�ζ���ָ�����
	float diff = max(dot(normal, lightDir), 0.2f); // ������ǿ��
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse1, TexCoords)); // ������
	
	// ����ⷵ����ɫ
	return diffuse;
}
