#include "main.h"

int main()
{
	// ��ʼ��OpenGL
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
	// ���Դλ������
	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.0f,  0.4f,  1.0f),
		glm::vec3(0.8f, 0.6f, 0.0f),
		glm::vec3(-1.0f,  0.7f, 0.0f),
		glm::vec3(0.0f,  1.0f, -1.0f)
	};
	// �ݵ�λ��
	std::vector<glm::vec3> vegetation
	{
		glm::vec3(-1.5f, 0.0f, -0.48f),
		glm::vec3(1.5f, 0.0f, 0.51f),
		glm::vec3(0.0f, 0.0f, 0.7f),
		glm::vec3(-0.3f, 0.0f, -2.3f),
		glm::vec3(0.5f, 0.0f, -0.6f)
	};
	// ������λ��
	std::vector<glm::vec3> windows
	{
		glm::vec3(-1.5f, 0.0f, -0.48f),
		glm::vec3(1.5f, 0.0f, 0.51f),
		glm::vec3(0.0f, 0.0f, 0.7f),
		glm::vec3(-0.3f, 0.0f, -2.3f),
		glm::vec3(0.5f, 0.0f, -0.6f)
	};
	// ������ɫ
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
	// ��պ�
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
	// ���
	GLCall(glEnable(GL_BLEND)); // �������
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)); // ���û�ϵķ�ʽ
	// glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO); // ���Էֱ�����RGB��alphaͨ��ѡ��
	// ��Ȳ���
	GLCall(glEnable(GL_DEPTH_TEST)); // ������Ȳ���
	// GLCall(glDepthMask(GL_FALSE)); // ������Ȼ����д�룬��������Ȼ���
	GLCall(glDepthFunc(GL_LESS)); // ������Ȳ���ʹ�õıȽ������
	// ģ�����
	GLCall(glEnable(GL_STENCIL_TEST)); // ����ģ�����
	// GLCall(glStencilMask(0xff)); // λ������ģ��ֵ���������㣬��Ϊ1д��ģ�建��ʱ������ԭ����0д��ģ�建��ʱ������0
	GLCall(glStencilFunc(GL_NOTEQUAL, 1, 0xff)); // ģ����Ժ�����ģ����ԵĲο�ֵ��������ο�ֵ��ģ��ֵ����������
	GLCall(glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE)); // sfailģ�����ʧ��ʱ��dpfailģ�����ͨ������Ȳ���ʧ��ʱ��dppass��ͨ��ʱ��ȡ����Ϊ
	// ���޳�
	GLCall(glCullFace(GL_BACK)); //  ֻ�޳�����
	// �������㻺�����VBO
	VertexBuffer cubeVBO(nullptr, 36 * 5 * sizeof(float));
	VertexBuffer normVBO(vertices, 36 * 6 * sizeof(float));
	VertexBuffer skyboxVBO(skyboxVertices, 36 * 3 * sizeof(float));
	VertexBuffer quadVBO(quadVertices, 6 * 4 * sizeof(float));
	VertexBuffer planeVBO(planeVertices, 6 * 5 * sizeof(float));
	VertexBuffer grassVBO(transparentVertices, 6 * 5 * sizeof(float));
	// ���������������VAO
	VertexArray cubeVAO; // ������VAO
	VertexArray normVAO; // �����ߵ�������VAO
	VertexArray quadVAO; // �ı���VAO
	VertexArray planeVAO; // ƽ��VAO
	VertexArray grassVAO; // ��VAO
	VertexArray skyboxVAO; // ��պ�VAO
	// �������鲼��
	VertexBufferLayout layout;
	layout.Push<float>(3); // ��������

	// ��պ�
	VertexBuffer boxVBO(nullptr, 36 * 3 * sizeof(float));
	//skyboxVAO.AddBuffer(skyboxVBO, layout);
	skyboxVAO.BatchedAddBuffer(boxVBO, skyboxVertices, 36 * 3 * sizeof(float), 3, GL_FLOAT);

	layout.Push<float>(2); // ��������
	// ������
	cubeVAO.BatchedAddBuffer(cubeVBO, position, 36 * 3 * sizeof(float), 3, GL_FLOAT);
	cubeVAO.BatchedAddBuffer(cubeVBO, tex, 36 * 2 * sizeof(float), 2, GL_FLOAT);
	// �ذ�
	planeVAO.AddBuffer(planeVBO, layout);
	// ��
	grassVAO.AddBuffer(grassVBO, layout);
	// �ı���
	VertexBufferLayout quadlayout;
	quadlayout.Push<float>(2);
	quadlayout.Push<float>(2);
	quadVAO.AddBuffer(quadVBO, quadlayout);

	VertexBufferLayout normLayout;
	normLayout.Push<float>(3);
	normLayout.Push<float>(3);
	normVAO.AddBuffer(normVBO, normLayout);

	// ������ɫ��shader
	Shader shader("./shader/Advanced_Vert.glsl", "./shader/Advanced_Frag.glsl"); // ��ɫ��
	Shader singleColor("./shader/single_Vert.glsl", "./shader/single_Frag.glsl"); // ������ɫ��
	Shader screenShader("./shader/Screen_Vert.glsl", "./shader/Screen_Frag.glsl"); // ��Ļ��ɫ��
	Shader skyboxShader("./shader/Skybox_Vert.glsl", "./shader/Skybox_Frag.glsl"); // ��պ���ɫ��
	Shader reflectShader("./shader/Reflect_Vert.glsl", "./shader/Reflect_Frag.glsl"); // ������ɫ��
	Shader refractShader("./shader/Refract_Vert.glsl", "./shader/Refract_Frag.glsl"); // ������ɫ��
	Shader mappingShader("./shader/Mapping_Vert.glsl", "./shader/Mapping_Frag.glsl"); // ����ӳ����ɫ��
	Shader explodeShader("./shader/Explode_Vert.glsl", "./shader/Explode_Frag.glsl", "./shader/Explode_Geom.glsl"); // Explode��ɫ��
	Shader normalShader("./shader/Normal_Vert.glsl", "./shader/Normal_Frag.glsl", "./shader/Normal_Geom.glsl"); // ������ɫ��

	Texture floorTexture("./texture/metal.png");
	Texture grassTexture("./texture/grass.png");
	Texture windowTexture("./texture/blending_transparent_window.png");
	Texture skyboxTexture(faces);

	shader.Use();
	shader.setInt("texture1", 0);
	shader.SetUniformBindingPoint("Matrices", 0); // ����ͳһ�������İ󶨵�
	singleColor.Use();
	singleColor.SetUniformBindingPoint("Matrices", 0); // ����ͳһ�������İ󶨵�
	screenShader.Use();
	screenShader.setInt("screenTexture", 0);
	skyboxShader.Use();
	skyboxShader.setInt("skybox", 0);
	skyboxShader.SetUniformBindingPoint("Matrices", 0); // ����ͳһ�������İ󶨵�
	reflectShader.Use();
	reflectShader.setInt("skybox", 0);
	reflectShader.SetUniformBindingPoint("Matrices", 0); // ����ͳһ�������İ󶨵�
	mappingShader.Use();
	mappingShader.setInt("skybox", 3);
	mappingShader.SetUniformBindingPoint("Matrices", 0); // ����ͳһ�������İ󶨵�
	mappingShader.setVec3("sun.direction", 1.0f, -2.0f, 1.0f);
	mappingShader.setVec3("sun.ambient", 0.6f, 0.6f, 0.6f);
	mappingShader.setVec3("sun.diffuse", 0.8f, 0.8f, 0.8f);
	mappingShader.setVec3("sun.specular", 1.0f, 1.0f, 1.0f);
	explodeShader.Use();
	explodeShader.setInt("skybox", 3);
	explodeShader.SetUniformBindingPoint("Matrices", 0); // ����ͳһ�������İ󶨵�
	explodeShader.setVec3("sun.direction", 1.0f, -2.0f, 1.0f);
	explodeShader.setVec3("sun.ambient", 0.6f, 0.6f, 0.6f);
	explodeShader.setVec3("sun.diffuse", 0.8f, 0.8f, 0.8f);
	explodeShader.setVec3("sun.specular", 1.0f, 1.0f, 1.0f);
	normalShader.Use();
	normalShader.SetUniformBindingPoint("Matrices", 0); // ����ͳһ�������İ󶨵�

	Model nanosuit_reflection("./model/nanosuit_reflection/nanosuit.obj");

	RenderBuffer RBO; // ������Ⱦ�������
	FrameBuffer FBO; // ����֡�������
	Texture colorTexture; // ����������
	FBO.AddTexture(colorTexture); // ��һ�������ӵ�֡������Ϊ��ɫ����
	FBO.AddBuffer(RBO); // ���һ����Ⱥ�ģ�帽����֡����
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	}
	FBO.Unbind();

	UniformBuffer UBO(sizeof(glm::mat4) * 2); // ����һ��ͳһ�������
	UBO.SetBindingPoint(0); // �󶨵��󶨵�0

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

		// �����͸����͸���������Ⱦ˳��
		std::map<float, glm::vec3> sorted;
		for (unsigned int i = 0; i < windows.size(); i++)
		{
			float distance = glm::length(camera.Position - windows[i]);
			sorted[distance] = windows[i];
		}

		GLCall(glFrontFace(GL_CW)); // ��˳ʱ����涨��Ϊ������

		FBO.Bind();
		// ��Ⱦ
		// glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f); // ���������Ļ����Ҫ����ɫ
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // �����ɫ���桢��Ȼ��桢ģ�建��
		glEnable(GL_DEPTH_TEST);

		glm::mat4 model = glm::mat4(1.0f);
		camera.Front *= -1;
		glm::mat4 view = camera.GetViewMatrix();
		camera.Front *= -1;
		
		UBO.UpdateData(glm::value_ptr(view), sizeof(glm::mat4), sizeof(glm::mat4)); // ����ͳһ������������

		//// ͸��ƽ��ͷ��fov����߱ȣ���ƽ�棬Զƽ��
		glm::mat4 proj = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		UBO.UpdateData(glm::value_ptr(proj), sizeof(glm::mat4)); // ����ͳһ������������

		shader.Use();
		// ���Ƶذ�
		GLCall(glStencilMask(0x00)); // �����ذ�д��ģ�建��
		planeVAO.Bind();
		floorTexture.Bind();
		shader.setMat4("model", glm::mat4(1.0f));
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// ����������
		reflectShader.Use();
		reflectShader.setVec3("cameraPos", camera.Position);
		GLCall(glEnable(GL_CULL_FACE)); // �������޳�
		GLCall(glStencilFunc(GL_ALWAYS, 1, 0xff)); // ģ����Ժ�����ģ����ԵĲο�ֵ��������ο�ֵ��ģ��ֵ����������
		GLCall(glStencilMask(0xff));
		normVAO.Bind();
		skyboxTexture.CubeBind();
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
		reflectShader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		// ������2
		refractShader.Use();
		refractShader.setVec3("cameraPos", camera.Position);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		refractShader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		GLCall(glStencilMask(0x00));
		GLCall(glDisable(GL_CULL_FACE)); // �ر����޳�

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
		// ���Ʋ�
		grassVAO.Bind();
		grassTexture.Bind();
		for (unsigned int i = 0; i < vegetation.size(); i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, vegetation[i]);
			shader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}

		// ���ƴ���
		windowTexture.Bind();
		for (std::map<float, glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); it++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, it->second);
			shader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}

		// ������պ�
		GLCall(glDepthFunc(GL_LEQUAL));
		skyboxShader.Use();
		skyboxVAO.Bind();
		skyboxTexture.CubeBind();
		glDrawArrays(GL_TRIANGLES, 0, 36);
		GLCall(glDepthFunc(GL_LESS));

		// ��������������
		GLCall(glEnable(GL_CULL_FACE)); // �������޳�
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
		GLCall(glDisable(GL_CULL_FACE)); // �ر����޳�

		GLCall(glFrontFace(GL_CCW)); // ����ʱ����涨��Ϊ������

		FBO.Unbind();
		// ��Ⱦ
		// glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f); // ���������Ļ����Ҫ����ɫ
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // �����ɫ���桢��Ȼ��桢ģ�建��
		GLCall(glEnable(GL_DEPTH_TEST));
		model = glm::mat4(1.0f);
		view = camera.GetViewMatrix();
		UBO.UpdateData(glm::value_ptr(view), sizeof(glm::mat4), sizeof(glm::mat4)); // ����ͳһ������������
		// ͸��ƽ��ͷ��fov����߱ȣ���ƽ�棬Զƽ��
		//proj = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		singleColor.Use();

		shader.Use();
		// ���Ƶذ�
		GLCall(glStencilMask(0x00)); // �����ذ�д��ģ�建��
		planeVAO.Bind();
		floorTexture.Bind();
		shader.setMat4("model", glm::mat4(1.0f));
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// ����������
		reflectShader.Use();
		reflectShader.setVec3("cameraPos", camera.Position);
		GLCall(glEnable(GL_CULL_FACE)); // �������޳�
		GLCall(glStencilFunc(GL_ALWAYS, 1, 0xff)); // ģ����Ժ�����ģ����ԵĲο�ֵ��������ο�ֵ��ģ��ֵ����������
		GLCall(glStencilMask(0xff));
		normVAO.Bind();
		skyboxTexture.CubeBind();
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
		reflectShader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		// ������2
		refractShader.Use();
		refractShader.setVec3("cameraPos", camera.Position);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		refractShader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		GLCall(glStencilMask(0x00));
		GLCall(glDisable(GL_CULL_FACE)); // �ر����޳�

		// nanosuit_reflection
		mappingShader.Use(); // ����ӳ��
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

		explodeShader.Use(); // ��ըЧ��
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

		// ���Ʋ�
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

		// ���ƴ���
		windowTexture.Bind();
		for (std::map<float, glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); it++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, it->second);
			shader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}

		// ������պ�
		GLCall(glDepthFunc(GL_LEQUAL));
		skyboxShader.Use();
		skyboxVAO.Bind();
		skyboxTexture.CubeBind();
		GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
		GLCall(glDepthFunc(GL_LESS));

		// ��������������
		GLCall(glEnable(GL_CULL_FACE)); // �������޳�
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
		GLCall(glDisable(GL_CULL_FACE)); // �ر����޳�

		screenShader.Use();
		quadVAO.Bind();
		colorTexture.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);

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
	// ע����̵Ļص�����
	glfwSetKeyCallback(window, key_callback);
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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_F && action == GLFW_PRESS)
	{
		flashlight = !flashlight; // F �����ֵ�
	}
}