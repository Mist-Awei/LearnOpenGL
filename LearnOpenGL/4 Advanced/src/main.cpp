#include "main.h"

int main()
{
	// 初始化OpenGL
	if (opengl_init())
		return -1;
	{
	float cubeVertices[] = {
		// Back position	  texcoord
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // Bottom-left
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, // top-right
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // bottom-right         
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, // top-right
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bottom-left
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, // top-left
		// Front
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // bottom-left
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, // bottom-right
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, // top-right
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, // top-right
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, // top-left
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // bottom-left
		// Left
		-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, // top-right
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, // top-left
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-left
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-left
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // bottom-right
		-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, // top-right
		// Right
		 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, // top-left
		 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-right
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, // top-right         
		 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-right
		 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, // top-left
		 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // bottom-left     
		 // Bottom
		 -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // top-right
		  0.5f, -0.5f, -0.5f, 1.0f, 1.0f, // top-left
		  0.5f, -0.5f,  0.5f, 1.0f, 0.0f, // bottom-left
		  0.5f, -0.5f,  0.5f, 1.0f, 0.0f, // bottom-left
		 -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // bottom-right
		 -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // top-right
		 // Top
		 -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, // top-left
		  0.5f,  0.5f,  0.5f, 1.0f, 0.0f, // bottom-right
		  0.5f,  0.5f, -0.5f, 1.0f, 1.0f, // top-right     
		  0.5f,  0.5f,  0.5f, 1.0f, 0.0f, // bottom-right
		 -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, // top-left
		 -0.5f,  0.5f,  0.5f, 0.0f, 0.0f  // bottom-left        
	};

	float position[] = {
		// Back position	
		-0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		// Front
		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		// Left
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		// Right
		 0.5f,  0.5f,  0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 // Bottom
		 -0.5f, -0.5f, -0.5f,
		  0.5f, -0.5f, -0.5f,
		  0.5f, -0.5f,  0.5f,
		  0.5f, -0.5f,  0.5f,
		 -0.5f, -0.5f,  0.5f,
		 -0.5f, -0.5f, -0.5f,
		 // Top
		 -0.5f,  0.5f, -0.5f,
		  0.5f,  0.5f,  0.5f,
		  0.5f,  0.5f, -0.5f,
		  0.5f,  0.5f,  0.5f,
		 -0.5f,  0.5f, -0.5f,
		 -0.5f,  0.5f,  0.5f
	};
	float tex[] = {
		//texcoord
		0.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 0.0f,
		0.0f, 1.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,

		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		1.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,

		 0.0f, 1.0f,
		 1.0f, 1.0f,
		 1.0f, 0.0f,
		 1.0f, 0.0f,
		 0.0f, 0.0f,
		 0.0f, 1.0f,

		 0.0f, 1.0f,
		 1.0f, 0.0f,
		 1.0f, 1.0f,
		 1.0f, 0.0f,
		 0.0f, 1.0f,
		 0.0f, 0.0f
	};
	float vertices[] = {
		//position		  //normal
	 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	  0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	  0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	  0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 // Front
	 -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	  0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	  0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	  0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 // Left
	 -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	 -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	 -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	 -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	 -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	 -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	 // Right
	  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	  0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	  0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	  0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	  0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	  // Bottom
	  -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	   0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	   0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	  -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	  -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	  // Top
	  -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	   0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	   0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	  -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	  -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	};
	float planeVertices[] = {
		// positions          // texture Coords
		 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

		 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
		 5.0f, -0.5f, -5.0f,  2.0f, 2.0f
	};
	float transparentVertices[] = {
		// positions         // texture Coords
		0.0f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.0f, -0.5f,  0.0f,  0.0f,  0.0f,
		1.0f, -0.5f,  0.0f,  1.0f,  0.0f,

		0.0f,  0.5f,  0.0f,  0.0f,  1.0f,
		1.0f, -0.5f,  0.0f,  1.0f,  0.0f,
		1.0f,  0.5f,  0.0f,  1.0f,  1.0f
	};
	// 点光源位置坐标
	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.0f,  0.4f,  1.0f),
		glm::vec3(0.8f, 0.6f, 0.0f),
		glm::vec3(-1.0f,  0.7f, 0.0f),
		glm::vec3(0.0f,  1.0f, -1.0f)
	};
	// 草的位置
	std::vector<glm::vec3> vegetation
	{
		glm::vec3(-1.5f, 0.0f, -0.48f),
		glm::vec3(1.5f, 0.0f, 0.51f),
		glm::vec3(0.0f, 0.0f, 0.7f),
		glm::vec3(-0.3f, 0.0f, -2.3f),
		glm::vec3(0.5f, 0.0f, -0.6f)
	};
	// 窗户的位置
	std::vector<glm::vec3> windows
	{
		glm::vec3(-1.5f, 0.0f, -0.48f),
		glm::vec3(1.5f, 0.0f, 0.51f),
		glm::vec3(0.0f, 0.0f, 0.7f),
		glm::vec3(-0.3f, 0.0f, -2.3f),
		glm::vec3(0.5f, 0.0f, -0.6f)
	};
	// 背景颜色
	glm::vec3 backgroundColor(0.6f, 0.6f, 0.6f);
	float quadVertices[] = {
		// positions   // texCoords
		-0.25f, 1.0f, 0.0f, 1.0f,
		-0.25f, 0.5f, 0.0f, 0.0f,
		 0.25f, 0.5f, 1.0f, 0.0f,

		-0.25f, 1.0f, 0.0f, 1.0f,
		 0.25f, 0.5f, 1.0f, 0.0f,
		 0.25f, 1.0f, 1.0f, 1.0f
	};
	// 天空盒
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
		"./texture/skybox/right.jpg",
		"./texture/skybox/left.jpg",
		"./texture/skybox/top.jpg",
		"./texture/skybox/bottom.jpg",
		"./texture/skybox/front.jpg",
		"./texture/skybox/back.jpg"
	};
	// 混合
	GLCall(glEnable(GL_BLEND)); // 开启混合
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)); // 设置混合的方式
	// glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO); // 可以分别设置RGB和alpha通道选项
	// 深度测试
	GLCall(glEnable(GL_DEPTH_TEST)); // 开启深度测试
	// GLCall(glDepthMask(GL_FALSE)); // 禁用深度缓冲的写入，不更新深度缓冲
	GLCall(glDepthFunc(GL_LESS)); // 设置深度测试使用的比较运算符
	// 模板测试
	GLCall(glEnable(GL_STENCIL_TEST)); // 开启模板测试
	// GLCall(glStencilMask(0xff)); // 位掩码与模板值进行与运算，设为1写入模板缓冲时都保持原样，0写入模板缓冲时都会变成0
	GLCall(glStencilFunc(GL_NOTEQUAL, 1, 0xff)); // 模板测试函数，模板测试的参考值，掩码与参考值和模板值进行与运算
	GLCall(glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE)); // sfail模板测试失败时，dpfail模板测试通过，深度测试失败时，dppass都通过时采取的行为
	// 面剔除
	GLCall(glCullFace(GL_BACK)); //  只剔除背面
	// 创建顶点缓冲对象VBO
	VertexBuffer cubeVBO(nullptr, 36 * 5 * sizeof(float));
	VertexBuffer normVBO(vertices, 36 * 6 * sizeof(float));
	VertexBuffer skyboxVBO(skyboxVertices, 36 * 3 * sizeof(float));
	VertexBuffer quadVBO(quadVertices, 6 * 4 * sizeof(float));
	VertexBuffer planeVBO(planeVertices, 6 * 5 * sizeof(float));
	VertexBuffer grassVBO(transparentVertices, 6 * 5 * sizeof(float));
	// 创建顶点数组对象VAO
	VertexArray cubeVAO; // 立方体VAO
	VertexArray normVAO; // 带法线的立方体VAO
	VertexArray quadVAO; // 四边形VAO
	VertexArray planeVAO; // 平面VAO
	VertexArray grassVAO; // 草VAO
	VertexArray skyboxVAO; // 天空盒VAO
	// 顶点数组布局
	VertexBufferLayout layout;
	layout.Push<float>(3); // 顶点坐标

	// 天空盒
	VertexBuffer boxVBO(nullptr, 36 * 3 * sizeof(float));
	//skyboxVAO.AddBuffer(skyboxVBO, layout);
	skyboxVAO.BatchedAddBuffer(boxVBO, skyboxVertices, 36 * 3 * sizeof(float), 3, GL_FLOAT);

	layout.Push<float>(2); // 纹理坐标
	// 立方体
	cubeVAO.BatchedAddBuffer(cubeVBO, position, 36 * 3 * sizeof(float), 3, GL_FLOAT);
	cubeVAO.BatchedAddBuffer(cubeVBO, tex, 36 * 2 * sizeof(float), 2, GL_FLOAT);
	// 地板
	planeVAO.AddBuffer(planeVBO, layout);
	// 草
	grassVAO.AddBuffer(grassVBO, layout);
	// 四边形
	VertexBufferLayout quadlayout;
	quadlayout.Push<float>(2);
	quadlayout.Push<float>(2);
	quadVAO.AddBuffer(quadVBO, quadlayout);

	VertexBufferLayout normLayout;
	normLayout.Push<float>(3);
	normLayout.Push<float>(3);
	normVAO.AddBuffer(normVBO, normLayout);

	// 创建着色器shader
	Shader shader("./shader/Advanced_Vert.glsl", "./shader/Advanced_Frag.glsl"); // 着色器
	Shader singleColor("./shader/single_Vert.glsl", "./shader/single_Frag.glsl"); // 轮廓着色器
	Shader screenShader("./shader/Screen_Vert.glsl", "./shader/Screen_Frag.glsl"); // 屏幕着色器
	Shader skyboxShader("./shader/Skybox_Vert.glsl", "./shader/Skybox_Frag.glsl"); // 天空盒着色器
	Shader reflectShader("./shader/Reflect_Vert.glsl", "./shader/Reflect_Frag.glsl"); // 反射着色器
	Shader refractShader("./shader/Refract_Vert.glsl", "./shader/Refract_Frag.glsl"); // 折射着色器
	Shader mappingShader("./shader/Mapping_Vert.glsl", "./shader/Mapping_Frag.glsl"); // 环境映射着色器
	Shader explodeShader("./shader/Explode_Vert.glsl", "./shader/Explode_Frag.glsl", "./shader/Explode_Geom.glsl"); // Explode着色器
	Shader normalShader("./shader/Normal_Vert.glsl", "./shader/Normal_Frag.glsl", "./shader/Normal_Geom.glsl"); // 法线着色器

	Texture floorTexture("./texture/metal.png");
	Texture grassTexture("./texture/grass.png");
	Texture windowTexture("./texture/blending_transparent_window.png");
	Texture skyboxTexture(faces);

	shader.Use();
	shader.setInt("texture1", 0);
	shader.SetUniformBindingPoint("Matrices", 0); // 设置统一缓冲对象的绑定点
	singleColor.Use();
	singleColor.SetUniformBindingPoint("Matrices", 0); // 设置统一缓冲对象的绑定点
	screenShader.Use();
	screenShader.setInt("screenTexture", 0);
	skyboxShader.Use();
	skyboxShader.setInt("skybox", 0);
	skyboxShader.SetUniformBindingPoint("Matrices", 0); // 设置统一缓冲对象的绑定点
	reflectShader.Use();
	reflectShader.setInt("skybox", 0);
	reflectShader.SetUniformBindingPoint("Matrices", 0); // 设置统一缓冲对象的绑定点
	mappingShader.Use();
	mappingShader.setInt("skybox", 3);
	mappingShader.SetUniformBindingPoint("Matrices", 0); // 设置统一缓冲对象的绑定点
	mappingShader.setVec3("sun.direction", 1.0f, -2.0f, 1.0f);
	mappingShader.setVec3("sun.ambient", 0.6f, 0.6f, 0.6f);
	mappingShader.setVec3("sun.diffuse", 0.8f, 0.8f, 0.8f);
	mappingShader.setVec3("sun.specular", 1.0f, 1.0f, 1.0f);
	explodeShader.Use();
	explodeShader.setInt("skybox", 3);
	explodeShader.SetUniformBindingPoint("Matrices", 0); // 设置统一缓冲对象的绑定点
	explodeShader.setVec3("sun.direction", 1.0f, -2.0f, 1.0f);
	explodeShader.setVec3("sun.ambient", 0.6f, 0.6f, 0.6f);
	explodeShader.setVec3("sun.diffuse", 0.8f, 0.8f, 0.8f);
	explodeShader.setVec3("sun.specular", 1.0f, 1.0f, 1.0f);
	normalShader.Use();
	normalShader.SetUniformBindingPoint("Matrices", 0); // 设置统一缓冲对象的绑定点

	Model nanosuit_reflection("./model/nanosuit_reflection/nanosuit.obj");

	RenderBuffer RBO; // 创建渲染缓冲对象
	FrameBuffer FBO; // 创建帧缓冲对象
	Texture colorTexture; // 创建纹理附件
	FBO.AddTexture(colorTexture); // 把一个纹理附加到帧缓冲作为颜色附件
	FBO.AddBuffer(RBO); // 添加一个深度和模板附件到帧缓冲
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	}
	FBO.Unbind();

	UniformBuffer UBO(sizeof(glm::mat4) * 2); // 创建一个统一缓冲对象
	UBO.SetBindingPoint(0); // 绑定到绑定点0

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

		// 计算半透明及透明物体的渲染顺序
		std::map<float, glm::vec3> sorted;
		for (unsigned int i = 0; i < windows.size(); i++)
		{
			float distance = glm::length(camera.Position - windows[i]);
			sorted[distance] = windows[i];
		}

		GLCall(glFrontFace(GL_CW)); // 将顺时针的面定义为正向面

		FBO.Bind();
		// 渲染
		// glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f); // 设置清空屏幕所需要的颜色
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // 清除颜色缓存、深度缓存、模板缓存
		glEnable(GL_DEPTH_TEST);

		glm::mat4 model = glm::mat4(1.0f);
		camera.Front *= -1;
		glm::mat4 view = camera.GetViewMatrix();
		camera.Front *= -1;
		
		UBO.UpdateData(glm::value_ptr(view), sizeof(glm::mat4), sizeof(glm::mat4)); // 更新统一缓冲对象的数据

		//// 透视平截头体fov，宽高比，近平面，远平面
		glm::mat4 proj = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		UBO.UpdateData(glm::value_ptr(proj), sizeof(glm::mat4)); // 更新统一缓冲对象的数据

		shader.Use();
		// 绘制地板
		GLCall(glStencilMask(0x00)); // 不将地板写入模板缓冲
		planeVAO.Bind();
		floorTexture.Bind();
		shader.setMat4("model", glm::mat4(1.0f));
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// 绘制立方体
		reflectShader.Use();
		reflectShader.setVec3("cameraPos", camera.Position);
		GLCall(glEnable(GL_CULL_FACE)); // 开启面剔除
		GLCall(glStencilFunc(GL_ALWAYS, 1, 0xff)); // 模板测试函数，模板测试的参考值，掩码与参考值和模板值进行与运算
		GLCall(glStencilMask(0xff));
		normVAO.Bind();
		skyboxTexture.CubeBind();
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
		reflectShader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		// 立方体2
		refractShader.Use();
		refractShader.setVec3("cameraPos", camera.Position);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		refractShader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		GLCall(glStencilMask(0x00));
		GLCall(glDisable(GL_CULL_FACE)); // 关闭面剔除

		// nanosuit_reflection
		explodeShader.Use();
		explodeShader.setVec3("cameraPos", camera.Position);
		explodeShader.setFloat("time", timeValue);
		normVAO.Bind();
		skyboxTexture.CubeBind(3);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.5f, -0.5f, 1.0f));
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
		explodeShader.setMat4("model", model);
		nanosuit_reflection.Draw(explodeShader);

		shader.Use();
		// 绘制草
		grassVAO.Bind();
		grassTexture.Bind();
		for (unsigned int i = 0; i < vegetation.size(); i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, vegetation[i]);
			shader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}

		// 绘制窗户
		windowTexture.Bind();
		for (std::map<float, glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); it++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, it->second);
			shader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}

		// 绘制天空盒
		GLCall(glDepthFunc(GL_LEQUAL));
		skyboxShader.Use();
		skyboxVAO.Bind();
		skyboxTexture.CubeBind();
		glDrawArrays(GL_TRIANGLES, 0, 36);
		GLCall(glDepthFunc(GL_LESS));

		// 绘制立方体轮廓
		GLCall(glEnable(GL_CULL_FACE)); // 开启面剔除
		GLCall(glStencilFunc(GL_NOTEQUAL, 1, 0xff));
		GLCall(glStencilMask(0x00));
		GLCall(glDisable(GL_DEPTH_TEST));
		singleColor.Use();
		cubeVAO.Bind();
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
		model = glm::scale(model, glm::vec3(1.05f, 1.05f, 1.05f));
		singleColor.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.05f, 1.05f, 1.05f));
		singleColor.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		GLCall(glStencilFunc(GL_ALWAYS, 0, 0xff));
		glStencilMask(0xff);
		GLCall(glDisable(GL_CULL_FACE)); // 关闭面剔除

		GLCall(glFrontFace(GL_CCW)); // 将逆时针的面定义为正向面

		FBO.Unbind();
		// 渲染
		// glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f); // 设置清空屏幕所需要的颜色
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // 清除颜色缓存、深度缓存、模板缓存
		GLCall(glEnable(GL_DEPTH_TEST));
		model = glm::mat4(1.0f);
		view = camera.GetViewMatrix();
		UBO.UpdateData(glm::value_ptr(view), sizeof(glm::mat4), sizeof(glm::mat4)); // 更新统一缓冲对象的数据
		// 透视平截头体fov，宽高比，近平面，远平面
		//proj = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		singleColor.Use();

		shader.Use();
		// 绘制地板
		GLCall(glStencilMask(0x00)); // 不将地板写入模板缓冲
		planeVAO.Bind();
		floorTexture.Bind();
		shader.setMat4("model", glm::mat4(1.0f));
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// 绘制立方体
		reflectShader.Use();
		reflectShader.setVec3("cameraPos", camera.Position);
		GLCall(glEnable(GL_CULL_FACE)); // 开启面剔除
		GLCall(glStencilFunc(GL_ALWAYS, 1, 0xff)); // 模板测试函数，模板测试的参考值，掩码与参考值和模板值进行与运算
		GLCall(glStencilMask(0xff));
		normVAO.Bind();
		skyboxTexture.CubeBind();
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
		reflectShader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		// 立方体2
		refractShader.Use();
		refractShader.setVec3("cameraPos", camera.Position);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		refractShader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		GLCall(glStencilMask(0x00));
		GLCall(glDisable(GL_CULL_FACE)); // 关闭面剔除

		// nanosuit_reflection
		mappingShader.Use(); // 环境映射
		skyboxTexture.CubeBind(3);
		mappingShader.setVec3("cameraPos", camera.Position);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, 1.0f));
		model = glm::scale(model, glm::vec3(0.06f, 0.06f, 0.06f));
		mappingShader.setMat4("model", model);
		nanosuit_reflection.Draw(mappingShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.0f, -0.5f, 1.0f));
		model = glm::scale(model, glm::vec3(0.06f, 0.06f, 0.06f));
		mappingShader.setMat4("model", model);
		nanosuit_reflection.Draw(mappingShader);

		explodeShader.Use(); // 爆炸效果
		explodeShader.setVec3("cameraPos", camera.Position);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.5f, -0.5f, 1.0f));
		model = glm::scale(model, glm::vec3(0.06f, 0.06f, 0.06f));
		explodeShader.setMat4("model", model);
		nanosuit_reflection.Draw(explodeShader);
		
		normalShader.Use();
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.0f, -0.5f, 1.0f));
		model = glm::scale(model, glm::vec3(0.06f, 0.06f, 0.06f));
		normalShader.setMat4("model", model);
		nanosuit_reflection.Draw(normalShader);

		// 绘制草
		shader.Use();
		grassVAO.Bind();
		grassTexture.Bind();
		for (unsigned int i = 0; i < vegetation.size(); i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, vegetation[i]);
			shader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}

		// 绘制窗户
		windowTexture.Bind();
		for (std::map<float, glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); it++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, it->second);
			shader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}

		// 绘制天空盒
		GLCall(glDepthFunc(GL_LEQUAL));
		skyboxShader.Use();
		skyboxVAO.Bind();
		skyboxTexture.CubeBind();
		GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
		GLCall(glDepthFunc(GL_LESS));

		// 绘制立方体轮廓
		GLCall(glEnable(GL_CULL_FACE)); // 开启面剔除
		GLCall(glStencilFunc(GL_NOTEQUAL, 1, 0xff));
		GLCall(glStencilMask(0x00));
		GLCall(glDisable(GL_DEPTH_TEST));
		singleColor.Use();
		cubeVAO.Bind();
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
		model = glm::scale(model, glm::vec3(1.05f, 1.05f, 1.05f));
		singleColor.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.05f, 1.05f, 1.05f));
		singleColor.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		GLCall(glStencilFunc(GL_ALWAYS, 0, 0xff));
		glStencilMask(0xff);
		GLCall(glDisable(GL_CULL_FACE)); // 关闭面剔除

		screenShader.Use();
		quadVAO.Bind();
		colorTexture.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);

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
	// 注册键盘的回调函数
	glfwSetKeyCallback(window, key_callback);
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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_F && action == GLFW_PRESS)
	{
		flashlight = !flashlight; // F 开关手电
	}
}