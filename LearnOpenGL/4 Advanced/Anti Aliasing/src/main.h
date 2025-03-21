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

int opengl_init(); // 初始化OpenGL
void framebuffer_size_callback(GLFWwindow* window, int width, int height); //回调函数，窗口大小被调整时也对视口调整
void processInput(GLFWwindow* window); // 处理按键输入
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn); // 鼠标位置回调函数
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset); // 鼠标滚轮回调函数,yoffset代表滚轮竖直滚动的大小

GLFWwindow* window = nullptr;
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
// timing
float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间
// carmera
Camera camera(glm::vec3(0.0f, 0.0f, 80.0f));
float last_X = SCR_WIDTH / 2.0f;
float last_Y = SCR_HEIGHT / 2.0f;
bool firstMouse = true;