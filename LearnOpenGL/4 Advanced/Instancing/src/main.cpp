#include "main.h"

int main()
{
	// ��ʼ��OpenGL
	if (opengl_init())
		return -1;
	{
	
		float skyboxVertices[] = {
			// positions          
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			-1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f
		};

	std::vector<std::string> faces
	{
		"./texture/space/right.jpg",
		"./texture/space/left.jpg",
		"./texture/space/top.jpg",
		"./texture/space/bottom.jpg",
		"./texture/space/front.jpg",
		"./texture/space/back.jpg"
	};

	unsigned int amount = 3000;
	glm::mat4* modelMatrices;
	modelMatrices = new glm::mat4[amount];
	srand(glfwGetTime()); // ��ʼ���������
	float radius = 90.0f;
	float offset = 15.0f;
	for (unsigned int i = 0; i < amount; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		// 1. λ�ƣ��ֲ��ڰ뾶Ϊ 'radius' ��Բ���ϣ�ƫ�Ƶķ�Χ�� [-offset, offset]
		float angle = (float)i / (float)amount * 360.0f;
		float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float x = sin(angle) * radius + displacement;
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float y = 0.15 * x + displacement * 0.3f; // �����Ǵ��ĸ߶ȱ�x��z�Ŀ��ҪС
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float z = cos(angle) * radius + displacement;
		model = glm::translate(model, glm::vec3(x, y, z));

		// 2. ���ţ���0.1��0.45֮������
		float scale = (rand() % 35) / 100.0f + 0.1;
		model = glm::scale(model, glm::vec3(scale));

		// 3. ��ת������һ�����룩���ѡ�����ת�����������������ת
		float rotAngle = (rand() % 360);
		model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));
		
		// 4. ��ӵ�����������
		modelMatrices[i] = model;
	}

	// ������ɫ
	glm::vec3 backgroundColor(0.1f, 0.1f, 0.1f);

	// ���
	GLCall(glEnable(GL_BLEND)); // �������
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)); // ���û�ϵķ�ʽ
	// glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO); // ���Էֱ�����RGB��alphaͨ��ѡ��
	
	// ���޳�
	GLCall(glCullFace(GL_BACK)); //  ֻ�޳�����

	// ������ɫ��shader
	Shader planetShader("./shader/Planet_Vert.glsl", "./shader/Planet_Frag.glsl"); // ������ɫ��
	Shader asteroidShader("./shader/Instance_Vert.glsl", "./shader/Instance_Frag.glsl"); // ��ʯ��ɫ��
	Shader skyboxShader("./shader/Skybox_Vert.glsl", "./shader/Skybox_Frag.glsl"); // ��ʯ��ɫ��

	planetShader.Use();
	planetShader.setInt("material.texture_diffuse1", 0);
	planetShader.setVec3("dirlight.direction", 0.3, -0.5, 1.0);
	planetShader.setVec3("dirlight.diffuse", 1.0, 0.8, 0.7);
	asteroidShader.Use();
	asteroidShader.setInt("material.texture_diffuse1", 0);
	asteroidShader.setVec3("dirlight.direction", 0.3, -0.5, 1.0);
	asteroidShader.setVec3("dirlight.diffuse", 1.0, 0.8, 0.7);
	skyboxShader.Use();
	skyboxShader.setInt("skybox", 0);
	
	Model planet("./model/planet/planet.obj");
	Model rock("./model/rock/rock.obj");

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);

	for (unsigned int i = 0; i < rock.meshes.size(); i++)
	{
		unsigned int VAO = rock.meshes[i].mVAO;
		glBindVertexArray(VAO);
		// set attribute pointers for matrix (4 times vec4)
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);

		glBindVertexArray(0);
	}

	VertexArray skyboxVAO;
	VertexBuffer skyboxVBO(nullptr, 3 * 36 * sizeof(float));
	skyboxVAO.BatchedAddBuffer(skyboxVBO, skyboxVertices, sizeof(skyboxVertices), 3, GL_FLOAT);

	Texture spaceMap(faces);

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

		GLCall(glFrontFace(GL_CW)); // ��˳ʱ����涨��Ϊ������

		// ��Ⱦ
		glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f); // ���������Ļ����Ҫ����ɫ
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // �����ɫ���桢��Ȼ��桢ģ�建��
		glEnable(GL_DEPTH_TEST);
		
		// ͸��ƽ��ͷ��fov����߱ȣ���ƽ�棬Զƽ��
		glm::mat4 proj = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 500.0f);
		glm::mat4 view = camera.GetViewMatrix();

		planetShader.Use();
		planetShader.setMat4("view", view);
		planetShader.setMat4("projection", proj);
		
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));		
		planetShader.setMat4("model", model);
		planet.Draw(planetShader);

		asteroidShader.Use();
		asteroidShader.setMat4("view", view);
		asteroidShader.setMat4("projection", proj);
		for (unsigned int i = 0; i < rock.meshes.size(); i++)
		{
			glBindVertexArray(rock.meshes[i].mVAO);
			glDrawElementsInstanced(GL_TRIANGLES, rock.meshes[i].indices.size(), GL_UNSIGNED_INT, 0, amount);
			glBindVertexArray(0);
		}

		glDepthFunc(GL_LEQUAL);
		skyboxShader.Use();
		skyboxShader.setMat4("view", view);
		skyboxShader.setMat4("projection", proj);
		skyboxVAO.Bind();
		spaceMap.CubeBind();
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glDepthFunc(GL_LESS);

		glfwSwapBuffers(window); //������ɫ���壬���洢��GLFW����ÿ��������ɫ�Ĵ󻺳�
		// ˫���壬ǰ���屣�沢��ʾ�����������ͼ�����е���Ⱦָ�����ں󻺳��ϻ��ơ�
		glfwPollEvents(); // ���������û�д����¼��������̡����´���״̬�������ö�Ӧ�Ļص�����
	}
	// ��Ⱦ����ɾ�����ͷŷ������Դ
	}
	// ��Ⱦ������Ҫ��ȷ��ɾ�����ͷŷ����������Դ������glfwTerminate����
	glfwTerminate();
	return 0;
}

int opengl_init()
{
	glfwInit();// ��ʼ��GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);// ����GLFW���汾��Ϊ3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);// ����GLFW�ΰ汾��Ϊ3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);// ʹ�ú���ģʽ

	//����һ�����ڶ���
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);// ���ô��ڿ��ߡ�����
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

	// ���ع�겢��׽�������ڳ����ϣ����Ӧͣ���ڴ�����
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// �����ӿڵĳߴ�
	glViewport(0, 0, width, height); //ǰ�����������ƴ������½ǵ�λ�ã�����������������Ⱦ���ڵĿ�Ⱥ͸߶ȣ����أ�
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true); // ESC �رմ���
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(FORWARD, deltaTime); // W ǰ��
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(LEFT, deltaTime); // A ����
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime); // S ����
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
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