#version 330 core
layout (location = 0) in vec3 aPos; // λ�ñ���������λ��ֵΪ0
layout (location = 1) in vec3 aNormol;

out vec3 LightColor;

uniform vec3 lightPos;
// MVP�任
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightColor;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	vec3 ShaderPos = vec3(view * model * vec4(aPos, 1.0f));
	vec3 Normal = mat3(transpose(inverse(view * model))) * aNormol; // ���߾����Ƴ��Է��������������ŵ�Ӱ��
	vec3 LightPos = vec3(view * model * vec4(lightPos, 1.0f));

	float ambientStrength = 0.1f; // ������ǿ��
	float specularStrength = 1.0f; // �߹�ǿ��
	
	// �����⣨ambient��
	vec3 ambient = ambientStrength * lightColor;

	// ������⣨diffuse��
	vec3 normal = normalize(Normal); // ���㷨������
	vec3 lightDir = normalize(LightPos - ShaderPos); // ���շ�������
	float diff = max(dot(normal, lightDir), 0.0f); // ������ǿ��
	vec3 diffuse = diff * lightColor; // ������
	
	// �߹⣨specular��
	vec3 viewDir = normalize(-ShaderPos); // ���߷����������۲�ռ��¹۲��ߵ�����Ϊ0��0��0��
	vec3 reflectDir = reflect(-lightDir, normal); // ��������
	// ���߷���ͷ��䷽��Խ�ӽ����߹�Խǿ
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
	vec3 specular = spec * lightColor; // �߹�

	// ���ն������ɫ
	LightColor = ambient + diffuse + specular;
}