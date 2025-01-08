#version 330 core
layout (location = 0) in vec3 aPos; // λ�ñ���������λ��ֵΪ0
layout (location = 1) in vec3 aNormol; // ��������
layout (location = 2) in vec2 aTexcoords; // ��������

out vec3 FragPos; // ����ռ��µĶ�������
out vec3 Normal; // ����ռ��µķ�������
out vec2 TexCoords;

// MVP�任
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	FragPos = vec3(model * vec4(aPos, 1.0f));
	Normal = mat3(transpose(inverse(model))) * aNormol; // ���߾����Ƴ��Է��������������ŵ�Ӱ��
	TexCoords = aTexcoords;
}