#include <stb_image/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Windows.h>

#include "CallError.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ElementBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height); //�ص����������ڴ�С������ʱҲ���ӿڵ���
void processInput(GLFWwindow* window); // ����������
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods); // ���̻ص�����
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn); // ���λ�ûص�����
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset); // �����ֻص�����,yoffset���������ֱ�����Ĵ�С

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
// timing
float deltaTime = 0.0f; // ��ǰ֡����һ֡��ʱ���
float lastFrame = 0.0f; // ��һ֡��ʱ��
// carmera
Camera camera(glm::vec3(0.0f, 0.5f, 3.0f));
float last_X = SCR_WIDTH / 2.0f;
float last_Y = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
// flashlight
bool flashlight = false;

int main()
{
	glfwInit();// ��ʼ��GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);// ����GLFW���汾��Ϊ3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);// ����GLFW�ΰ汾��Ϊ3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);// ʹ�ú���ģʽ

	//����һ�����ڶ���
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);// ���ô��ڿ��ߡ�����
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// �������Ĵ�������������Ϊ��ǰ�̵߳���������
	glfwMakeContextCurrent(window);
	// GLAD����������OpenGL�ĺ���ָ��ģ������κ�OpenGL��������Ҫ��ʼ��GLAD
	// ��GLAD������������ϵͳ��ص�OpenGL����ָ���ַ�ĺ�����GLFW�����ǵ���glfwGetProcAddress
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// ע�ắ��������GLFWÿ�����ڵ�����С���ô˺���
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// ע������ƶ��Ļص�����
	glfwSetCursorPosCallback(window, mouse_callback);
	// ע�������ֵĻص�����
	glfwSetScrollCallback(window, scroll_callback);
	// ע����̵Ļص�����
	glfwSetKeyCallback(window, key_callback);
	// ���ع�겢��׽�������ڳ����ϣ����Ӧͣ���ڴ�����
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	float cubeVertices[] = {
		// positions          // texture Coords
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	// ���Դλ������
	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.0f,  0.4f,  1.0f),
		glm::vec3(0.8f, 0.6f, 0.0f),
		glm::vec3(-1.0f,  0.7f, 0.0f),
		glm::vec3(0.0f,  1.0f, -1.0f)
	};
	 // ���Դ��ɫ
	glm::vec3 pointLightColors[] = {
		glm::vec3(1.0f, 0.6f, 0.0f),
		glm::vec3(1.0f, 1.0, 0.0),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(0.2f, 0.2f, 1.0f)
	};
	// ������ɫ
	glm::vec3 backgroundColor(0.6f, 0.6f, 0.6f);
	// ̫������ɫ
	glm::vec3 sunColor(1.0f, 1.0f, 1.0f);

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	// �������㻺�����VBO
	VertexBuffer VBO(cubeVertices, 36 * 5 * sizeof(float));
	// ���������������VAO
	VertexArray lightVAO; // �ƹ��VAO
	// ��VAO��VBO
	lightVAO.Bind();
	VBO.Bind();

	// �������鲼��
	VertexBufferLayout layout;
	layout.Push<float>(3); // ��������
	layout.Push<float>(2); // ��������

	// ��VBO�Ĳ�����ӵ�VAO��
	lightVAO.AddBuffer(VBO, layout);
	VBO.Unbind(); // ����glVertexAttribPointer��VBOע��Ϊ�������Եİ󶨶��㻺��������Խ����

	// ������ɫ��shader
	Shader lightingShader("./shader/Phong_Vert.glsl", "./shader/Phong_Frag.glsl"); // ���Դ��ɫ��
	Shader lightCubeShader("./shader/lamp_Vert.glsl", "./shader/lamp_Frag.glsl"); // �ƹ����ɫ��

	Model nanosuit("./model/nanosuit/nanosuit.obj"); // ����ģ��

	// ���ù�Դ����
	lightingShader.Use();
	// �����
	lightingShader.setVec3("sun.direction", -0.2f, -1.0f, -0.3f); // ���շ���
	lightingShader.setVec3("sun.ambient", 0.05f * sunColor);
	lightingShader.setVec3("sun.diffuse", 0.4f * sunColor);
	lightingShader.setVec3("sun.specular", 0.5f * sunColor);
	// ���Դ 1
	lightingShader.setVec3("pointLights[0].position", pointLightPositions[0]); // ����λ��
	lightingShader.setVec3("pointLights[0].ambient", 0.1f * pointLightColors[0]);
	lightingShader.setVec3("pointLights[0].diffuse", pointLightColors[0]);
	lightingShader.setVec3("pointLights[0].specular", pointLightColors[0]);
	lightingShader.setFloat("pointLights[0].constant", 1.0f);
	lightingShader.setFloat("pointLights[0].linear", 0.09f);
	lightingShader.setFloat("pointLights[0].quadratic", 0.032f);
	// ���Դ 2
	lightingShader.setVec3("pointLights[1].position", pointLightPositions[1]);
	lightingShader.setVec3("pointLights[1].ambient", 0.1f * pointLightColors[1]);
	lightingShader.setVec3("pointLights[1].diffuse", pointLightColors[1]);
	lightingShader.setVec3("pointLights[1].specular", pointLightColors[1]);
	lightingShader.setFloat("pointLights[1].constant", 1.0f);
	lightingShader.setFloat("pointLights[1].linear", 0.09f);
	lightingShader.setFloat("pointLights[1].quadratic", 0.032f);
	// ���Դ 3
	lightingShader.setVec3("pointLights[2].position", pointLightPositions[2]);
	lightingShader.setVec3("pointLights[2].ambient", 0.1f * pointLightColors[2]);
	lightingShader.setVec3("pointLights[2].diffuse", pointLightColors[2]);
	lightingShader.setVec3("pointLights[2].specular", pointLightColors[2]);
	lightingShader.setFloat("pointLights[2].constant", 1.0f);
	lightingShader.setFloat("pointLights[2].linear", 0.09f);
	lightingShader.setFloat("pointLights[2].quadratic", 0.032f);
	// ���Դ 4
	lightingShader.setVec3("pointLights[3].position", pointLightPositions[3]);
	lightingShader.setVec3("pointLights[3].ambient", 0.1f * pointLightColors[3]);
	lightingShader.setVec3("pointLights[3].diffuse", pointLightColors[3]);
	lightingShader.setVec3("pointLights[3].specular", pointLightColors[3]);
	lightingShader.setFloat("pointLights[3].constant", 1.0f);
	lightingShader.setFloat("pointLights[3].linear", 0.09f);
	lightingShader.setFloat("pointLights[3].quadratic", 0.032f);
	// �۹�
	lightingShader.setVec3("flashLight.ambient", 0.0f, 0.0f, 0.0f);
	lightingShader.setVec3("flashLight.diffuse", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("flashLight.specular", 1.0f, 1.0f, 1.0f);
	lightingShader.setFloat("flashLight.constant", 1.0f); // ˥��������
	lightingShader.setFloat("flashLight.linear", 0.09f); // ˥��һ����
	lightingShader.setFloat("flashLight.quadratic", 0.032f); // ˥��������
	lightingShader.setFloat("flashLight.innerCutOff", glm::cos(glm::radians(25.0f))); // ���й��
	lightingShader.setFloat("flashLight.outerCutOff", glm::cos(glm::radians(35.0f))); // ���й��
	lightingShader.setVec3("flashLight.position", camera.Position);
	lightingShader.setVec3("flashLight.direction", camera.Front);
	// ��������
	lightingShader.setFloat("material.shininess", 32);

	glEnable(GL_DEPTH_TEST); // ������Ȳ���
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // ֻ�����߶�
	// ��Ⱦѭ��
	while (!glfwWindowShouldClose(window)) // ���GLFW�Ƿ�Ҫ���˳�
	{
		// ����֡ʱ��
		float timeValue = glfwGetTime(); // ��ȡ���е�����
		float currentFrame = timeValue;
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// ��Ⲣ����������
		processInput(window);

		// ��Ⱦ
		glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f); // ���������Ļ����Ҫ����ɫ
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // �����ɫ�������Ȼ���

		lightingShader.Use();
		// ���ò����¹۲�����
		lightingShader.setVec3("viewPos", camera.Position);
		// ���ò�����flashlight��λ�úͷ���
		lightingShader.setVec3("flashLight.position", camera.Position);
		lightingShader.setVec3("flashLight.direction", camera.Front);
		// �����ֵ翪��
		lightingShader.setBool("flash", flashlight);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.04f));
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 proj = glm::mat4(1.0f);
		// ͸��ƽ��ͷ��fov����߱ȣ���ƽ�棬Զƽ��
		proj = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		lightingShader.setMat4("view", view);
		lightingShader.setMat4("projection", proj);
		lightingShader.setMat4("model", model);
		nanosuit.Draw(lightingShader);

		lightCubeShader.Use();
		lightCubeShader.setMat4("view", view);
		lightCubeShader.setMat4("projection", proj);
		lightVAO.Bind();
		// ����4�����Դ
		for (unsigned int i = 0; i < 4; i++)
		{
			lightCubeShader.setVec3("lightColor", pointLightColors[i]);
			model = glm::mat4(1.0f);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f));
			lightCubeShader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glfwSwapBuffers(window); //������ɫ���壬���洢��GLFW����ÿ��������ɫ�Ĵ󻺳�
		// ˫���壬ǰ���屣�沢��ʾ�����������ͼ�����е���Ⱦָ�����ں󻺳��ϻ��ơ�
		glfwPollEvents(); // ���������û�д����¼��������̡����´���״̬�������ö�Ӧ�Ļص�����
	}
	// ��Ⱦ����ɾ�����ͷŷ������Դ
	VBO.Delete();
	lightVAO.Delete();
	lightCubeShader.Delete();
	lightingShader.Delete();
	nanosuit.Delete();
	// ��Ⱦ������Ҫ��ȷ��ɾ�����ͷŷ����������Դ������glfwTerminate����
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// �����ӿڵĳߴ�
	glViewport(0, 0, width, height); //ǰ�����������ƴ������½ǵ�λ�ã�����������������Ⱦ���ڵĿ�Ⱥ͸߶ȣ����أ�
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE))
	{
		glfwWindowShouldClose(window); // ESC �رմ���
	}
	if (glfwGetKey(window, GLFW_KEY_W))
	{
		camera.ProcessKeyboard(FORWARD, deltaTime); // W ǰ��
	}
	if (glfwGetKey(window, GLFW_KEY_A))
	{
		camera.ProcessKeyboard(LEFT, deltaTime); // A ����
	}
	if (glfwGetKey(window, GLFW_KEY_S))
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime); // S ����
	}
	if (glfwGetKey(window, GLFW_KEY_D))
	{
		camera.ProcessKeyboard(RIGHT, deltaTime); // D ����
	}
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = (float)xposIn;
	float ypos = (float)yposIn;
	if (firstMouse)
	{
		last_X = xpos;
		last_Y = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - last_X;
	float yoffset = last_Y - ypos; // y�����Ǵ���Ļ�µ���
	last_X = xpos;
	last_Y = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll((float)yoffset);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_F && action == GLFW_PRESS)
	{
		flashlight = !flashlight; // F �����ֵ�
	}
}