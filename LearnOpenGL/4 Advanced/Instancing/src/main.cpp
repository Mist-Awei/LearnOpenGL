#include "main.h"

int main()
{
	// 初始化OpenGL
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
	srand(glfwGetTime()); // 初始化随机种子
	float radius = 90.0f;
	float offset = 15.0f;
	for (unsigned int i = 0; i < amount; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		// 1. 位移：分布在半径为 'radius' 的圆形上，偏移的范围是 [-offset, offset]
		float angle = (float)i / (float)amount * 360.0f;
		float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float x = sin(angle) * radius + displacement;
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float y = 0.15 * x + displacement * 0.3f; // 让行星带的高度比x和z的宽度要小
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float z = cos(angle) * radius + displacement;
		model = glm::translate(model, glm::vec3(x, y, z));

		// 2. 缩放：在0.1和0.45之间缩放
		float scale = (rand() % 35) / 100.0f + 0.1;
		model = glm::scale(model, glm::vec3(scale));

		// 3. 旋转：绕着一个（半）随机选择的旋转轴向量进行随机的旋转
		float rotAngle = (rand() % 360);
		model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));
		
		// 4. 添加到矩阵数组中
		modelMatrices[i] = model;
	}

	// 背景颜色
	glm::vec3 backgroundColor(0.1f, 0.1f, 0.1f);

	// 混合
	GLCall(glEnable(GL_BLEND)); // 开启混合
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)); // 设置混合的方式
	// glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO); // 可以分别设置RGB和alpha通道选项
	
	// 面剔除
	GLCall(glCullFace(GL_BACK)); //  只剔除背面

	// 创建着色器shader
	Shader planetShader("./shader/Planet_Vert.glsl", "./shader/Planet_Frag.glsl"); // 星球着色器
	Shader asteroidShader("./shader/Instance_Vert.glsl", "./shader/Instance_Frag.glsl"); // 碎石着色器
	Shader skyboxShader("./shader/Skybox_Vert.glsl", "./shader/Skybox_Frag.glsl"); // 碎石着色器

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

	// 渲染循环
	while (!glfwWindowShouldClose(window)) // 检查GLFW是否要求被退出
	{
		// 计算帧时间
		float timeValue = glfwGetTime(); // 获取运行的秒数
		float currentFrame = timeValue;
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// 检测并处理按键输入
		processInput(window);

		GLCall(glFrontFace(GL_CW)); // 将顺时针的面定义为正向面

		// 渲染
		glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f); // 设置清空屏幕所需要的颜色
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 清除颜色缓存、深度缓存、模板缓存
		glEnable(GL_DEPTH_TEST);
		
		// 透视平截头体fov，宽高比，近平面，远平面
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

		glfwSwapBuffers(window); //交换颜色缓冲，它存储着GLFW窗口每个像素颜色的大缓冲
		// 双缓冲，前缓冲保存并显示着最终输出的图像，所有的渲染指令则在后缓冲上绘制。
		glfwPollEvents(); // 函数检查有没有触发事件，鼠标键盘、更新窗口状态，并调用对应的回调函数
	}
	// 渲染结束删除和释放分配的资源
	}
	// 渲染结束需要正确的删除和释放分配的所有资源，调用glfwTerminate函数
	glfwTerminate();
	return 0;
}

int opengl_init()
{
	glfwInit();// 初始化GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);// 设置GLFW主版本号为3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);// 设置GLFW次版本号为3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);// 使用核心模式

	//创建一个窗口对象
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);// 设置窗口宽、高、名称
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// 将创建的窗口上下文设置为当前线程的主上下文
	glfwMakeContextCurrent(window);
	// GLAD是用来管理OpenGL的函数指针的，调用任何OpenGL函数都需要初始化GLAD
	// 给GLAD传入用来加载系统相关的OpenGL函数指针地址的函数，GLFW给我们的是glfwGetProcAddress
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// 注册函数，告诉GLFW每当窗口调整大小调用此函数
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// 注册鼠标移动的回调函数
	glfwSetCursorPosCallback(window, mouse_callback);
	// 注册鼠标滚轮的回调函数
	glfwSetScrollCallback(window, scroll_callback);

	// 隐藏光标并捕捉，焦点在程序上，光标应停留在窗口中
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// 设置视口的尺寸
	glViewport(0, 0, width, height); //前两个参数控制窗口左下角的位置，后两个参数控制渲染窗口的宽度和高度（像素）
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true); // ESC 关闭窗口
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(FORWARD, deltaTime); // W 前移
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(LEFT, deltaTime); // A 左移
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime); // S 后移
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(RIGHT, deltaTime); // D 右移
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
	float yoffset = last_Y - ypos; // y坐标是从屏幕下到上
	last_X = xpos;
	last_Y = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll((float)yoffset);
}