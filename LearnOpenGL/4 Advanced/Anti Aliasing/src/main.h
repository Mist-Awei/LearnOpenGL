#pragma once
#include <stb_image/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Windows.h>
#include <map>

#include "CallError.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ElementBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "FrameBuffer.h"
#include "RenderBuffer.h"
#include "UniformBuffer.h"

int opengl_init(); // ��ʼ��OpenGL
void framebuffer_size_callback(GLFWwindow* window, int width, int height); //�ص����������ڴ�С������ʱҲ���ӿڵ���
void processInput(GLFWwindow* window); // ����������
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn); // ���λ�ûص�����
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset); // �����ֻص�����,yoffset���������ֱ�����Ĵ�С

GLFWwindow* window = nullptr;
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
// timing
float deltaTime = 0.0f; // ��ǰ֡����һ֡��ʱ���
float lastFrame = 0.0f; // ��һ֡��ʱ��
// carmera
Camera camera(glm::vec3(0.0f, 0.0f, 80.0f));
float last_X = SCR_WIDTH / 2.0f;
float last_Y = SCR_HEIGHT / 2.0f;
bool firstMouse = true;