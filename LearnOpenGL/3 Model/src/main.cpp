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

void framebuffer_size_callback(GLFWwindow* window, int width, int height); //回调函数，窗口大小被调整时也对视口调整
void processInput(GLFWwindow* window); // 处理按键输入
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods); // 键盘回调函数
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn); // 鼠标位置回调函数
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset); // 鼠标滚轮回调函数,yoffset代表滚轮竖直滚动的大小

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
// timing
float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间
// carmera
Camera camera(glm::vec3(0.0f, 0.5f, 3.0f));
float last_X = SCR_WIDTH / 2.0f;
float last_Y = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
// flashlight
bool flashlight = false;

int main()
{
	glfwInit();// 初始化GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);// 设置GLFW主版本号为3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);// 设置GLFW次版本号为3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);// 使用核心模式

	//创建一个窗口对象
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);// 设置窗口宽、高、名称
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
	// 注册键盘的回调函数
	glfwSetKeyCallback(window, key_callback);
	// 隐藏光标并捕捉，焦点在程序上，光标应停留在窗口中
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
	// 点光源位置坐标
	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.0f,  0.4f,  1.0f),
		glm::vec3(0.8f, 0.6f, 0.0f),
		glm::vec3(-1.0f,  0.7f, 0.0f),
		glm::vec3(0.0f,  1.0f, -1.0f)
	};
	 // 点光源颜色
	glm::vec3 pointLightColors[] = {
		glm::vec3(1.0f, 0.6f, 0.0f),
		glm::vec3(1.0f, 1.0, 0.0),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(0.2f, 0.2f, 1.0f)
	};
	// 背景颜色
	glm::vec3 backgroundColor(0.6f, 0.6f, 0.6f);
	// 太阳光颜色
	glm::vec3 sunColor(1.0f, 1.0f, 1.0f);

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	// 创建顶点缓冲对象VBO
	VertexBuffer VBO(cubeVertices, 36 * 5 * sizeof(float));
	// 创建顶点数组对象VAO
	VertexArray lightVAO; // 灯光的VAO
	// 绑定VAO和VBO
	lightVAO.Bind();
	VBO.Bind();

	// 顶点数组布局
	VertexBufferLayout layout;
	layout.Push<float>(3); // 顶点坐标
	layout.Push<float>(2); // 纹理坐标

	// 将VBO的布局添加到VAO中
	lightVAO.AddBuffer(VBO, layout);
	VBO.Unbind(); // 调用glVertexAttribPointer将VBO注册为顶点属性的绑定顶点缓冲对象后可以解除绑定

	// 创建着色器shader
	Shader lightingShader("./shader/Phong_Vert.glsl", "./shader/Phong_Frag.glsl"); // 多光源着色器
	Shader lightCubeShader("./shader/lamp_Vert.glsl", "./shader/lamp_Frag.glsl"); // 灯光的着色器

	Model nanosuit("./model/nanosuit/nanosuit.obj"); // 加载模型

	// 设置光源属性
	lightingShader.Use();
	// 定向光
	lightingShader.setVec3("sun.direction", -0.2f, -1.0f, -0.3f); // 光照方向
	lightingShader.setVec3("sun.ambient", 0.05f * sunColor);
	lightingShader.setVec3("sun.diffuse", 0.4f * sunColor);
	lightingShader.setVec3("sun.specular", 0.5f * sunColor);
	// 点光源 1
	lightingShader.setVec3("pointLights[0].position", pointLightPositions[0]); // 光照位置
	lightingShader.setVec3("pointLights[0].ambient", 0.1f * pointLightColors[0]);
	lightingShader.setVec3("pointLights[0].diffuse", pointLightColors[0]);
	lightingShader.setVec3("pointLights[0].specular", pointLightColors[0]);
	lightingShader.setFloat("pointLights[0].constant", 1.0f);
	lightingShader.setFloat("pointLights[0].linear", 0.09f);
	lightingShader.setFloat("pointLights[0].quadratic", 0.032f);
	// 点光源 2
	lightingShader.setVec3("pointLights[1].position", pointLightPositions[1]);
	lightingShader.setVec3("pointLights[1].ambient", 0.1f * pointLightColors[1]);
	lightingShader.setVec3("pointLights[1].diffuse", pointLightColors[1]);
	lightingShader.setVec3("pointLights[1].specular", pointLightColors[1]);
	lightingShader.setFloat("pointLights[1].constant", 1.0f);
	lightingShader.setFloat("pointLights[1].linear", 0.09f);
	lightingShader.setFloat("pointLights[1].quadratic", 0.032f);
	// 点光源 3
	lightingShader.setVec3("pointLights[2].position", pointLightPositions[2]);
	lightingShader.setVec3("pointLights[2].ambient", 0.1f * pointLightColors[2]);
	lightingShader.setVec3("pointLights[2].diffuse", pointLightColors[2]);
	lightingShader.setVec3("pointLights[2].specular", pointLightColors[2]);
	lightingShader.setFloat("pointLights[2].constant", 1.0f);
	lightingShader.setFloat("pointLights[2].linear", 0.09f);
	lightingShader.setFloat("pointLights[2].quadratic", 0.032f);
	// 点光源 4
	lightingShader.setVec3("pointLights[3].position", pointLightPositions[3]);
	lightingShader.setVec3("pointLights[3].ambient", 0.1f * pointLightColors[3]);
	lightingShader.setVec3("pointLights[3].diffuse", pointLightColors[3]);
	lightingShader.setVec3("pointLights[3].specular", pointLightColors[3]);
	lightingShader.setFloat("pointLights[3].constant", 1.0f);
	lightingShader.setFloat("pointLights[3].linear", 0.09f);
	lightingShader.setFloat("pointLights[3].quadratic", 0.032f);
	// 聚光
	lightingShader.setVec3("flashLight.ambient", 0.0f, 0.0f, 0.0f);
	lightingShader.setVec3("flashLight.diffuse", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("flashLight.specular", 1.0f, 1.0f, 1.0f);
	lightingShader.setFloat("flashLight.constant", 1.0f); // 衰减常数项
	lightingShader.setFloat("flashLight.linear", 0.09f); // 衰减一次项
	lightingShader.setFloat("flashLight.quadratic", 0.032f); // 衰减二次项
	lightingShader.setFloat("flashLight.innerCutOff", glm::cos(glm::radians(25.0f))); // 内切光角
	lightingShader.setFloat("flashLight.outerCutOff", glm::cos(glm::radians(35.0f))); // 外切光角
	lightingShader.setVec3("flashLight.position", camera.Position);
	lightingShader.setVec3("flashLight.direction", camera.Front);
	// 材质属性
	lightingShader.setFloat("material.shininess", 32);

	glEnable(GL_DEPTH_TEST); // 开启深度测试
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // 只绘制线段
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

		// 渲染
		glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f); // 设置清空屏幕所需要的颜色
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 清除颜色缓存和深度缓存

		lightingShader.Use();
		// 设置并更新观察坐标
		lightingShader.setVec3("viewPos", camera.Position);
		// 设置并更新flashlight的位置和方向
		lightingShader.setVec3("flashLight.position", camera.Position);
		lightingShader.setVec3("flashLight.direction", camera.Front);
		// 设置手电开关
		lightingShader.setBool("flash", flashlight);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.04f));
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 proj = glm::mat4(1.0f);
		// 透视平截头体fov，宽高比，近平面，远平面
		proj = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		lightingShader.setMat4("view", view);
		lightingShader.setMat4("projection", proj);
		lightingShader.setMat4("model", model);
		nanosuit.Draw(lightingShader);

		lightCubeShader.Use();
		lightCubeShader.setMat4("view", view);
		lightCubeShader.setMat4("projection", proj);
		lightVAO.Bind();
		// 绘制4个点光源
		for (unsigned int i = 0; i < 4; i++)
		{
			lightCubeShader.setVec3("lightColor", pointLightColors[i]);
			model = glm::mat4(1.0f);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f));
			lightCubeShader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glfwSwapBuffers(window); //交换颜色缓冲，它存储着GLFW窗口每个像素颜色的大缓冲
		// 双缓冲，前缓冲保存并显示着最终输出的图像，所有的渲染指令则在后缓冲上绘制。
		glfwPollEvents(); // 函数检查有没有触发事件，鼠标键盘、更新窗口状态，并调用对应的回调函数
	}
	// 渲染结束删除和释放分配的资源
	VBO.Delete();
	lightVAO.Delete();
	lightCubeShader.Delete();
	lightingShader.Delete();
	nanosuit.Delete();
	// 渲染结束需要正确的删除和释放分配的所有资源，调用glfwTerminate函数
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// 设置视口的尺寸
	glViewport(0, 0, width, height); //前两个参数控制窗口左下角的位置，后两个参数控制渲染窗口的宽度和高度（像素）
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE))
	{
		glfwWindowShouldClose(window); // ESC 关闭窗口
	}
	if (glfwGetKey(window, GLFW_KEY_W))
	{
		camera.ProcessKeyboard(FORWARD, deltaTime); // W 前移
	}
	if (glfwGetKey(window, GLFW_KEY_A))
	{
		camera.ProcessKeyboard(LEFT, deltaTime); // A 左移
	}
	if (glfwGetKey(window, GLFW_KEY_S))
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime); // S 后移
	}
	if (glfwGetKey(window, GLFW_KEY_D))
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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_F && action == GLFW_PRESS)
	{
		flashlight = !flashlight; // F 开关手电
	}
}