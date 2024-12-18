#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "camera.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height); //回调函数，窗口大小被调整时也对视口调整
void processInput(GLFWwindow* window); // 处理按键输入
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn); // 鼠标位置回调函数
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset); // 鼠标滚轮回调函数,yoffset代表滚轮竖直滚动的大小

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float mixValue = 0.5;
// timing
float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间
// carmera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float last_X = SCR_WIDTH / 2.0f;
float last_Y = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

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
    // 隐藏光标并捕捉，焦点在程序上，光标应停留在窗口中
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //创建顶点数组（标准化设备坐标）
    float vertices[] = {
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

    glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    // 索引数组
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    Shader ourShader("src/shader/vertex.glsl", "src/shader/fragment.glsl");

    // 创建VAO
    unsigned VAO;
    glGenVertexArrays(1, &VAO);
    //创建顶点缓冲对象
    unsigned int VBO;
    glGenBuffers(1, &VBO); // 生成一个带有缓冲ID的顶点缓冲对象VBO
    //创建元素缓冲对象
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    // 绑定VAO
    glBindVertexArray(VAO);
    // 把顶点数组复制到缓冲中供OpenGL使用.顶点缓冲对象的缓冲类型是GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // 将创建的顶点缓冲对象VBO绑定到GL_ARRAY_BUFFER目标上
    // 将用户定义的顶点数据复制到当前绑定的缓冲类型中
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 复制索引数组到一个索引缓冲中，供OpenGL使用.元素缓冲对象的缓冲类型是GL_ELEMENT_ARRAY_BUFFER
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // 设置顶点属性指针,配置顶点属性（layout position位置值），数据类型，是否标准化，
    // 步长（连续的顶点属性组的间隔），位置缓冲在起始位置时的偏移量
    // 顶点位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); //顶点属性位置值为参数，启用顶点属性
    // 顶点颜色属性
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    // glEnableVertexAttribArray(1);
    // 顶点纹理位置属性
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    // glBindBuffer(GL_ARRAY_BUFFER, 0); // 调用glVertexAttribPointer将VBO注册为顶点属性的绑定顶点缓冲对象后可以解除绑定
    // glBindVertexArray(0); 

    unsigned int textures[2];
    glGenTextures(2, textures);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    // float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor); // 使用clamp_to_border需要使用fv后缀函数指定边缘颜色
    // 为当前绑定的纹理对象设置环绕和过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 加载并生成纹理
    int width, height, nrChannels;
    unsigned char* data = stbi_load("./src/texture/container.jpg", &width, &height, &nrChannels, 0); // 将会用图像的宽高和颜色通道个数填充对应变量
    if (data)
    {
        // 第一个参数指定纹理目标，第二个参数为纹理制定多级渐远纹理的级别，第三个参数为纹理存储的格式，第四第五参数设置纹理的宽高
        // 第六参数总设为0（历史遗留问题），第七第八个参数定义了源图的格式和数据类型，最后一个参数是图像数据
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load("./src/texture/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data); // 释放图像内存

    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);
    
    glEnable(GL_DEPTH_TEST);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // 设置清空屏幕所需要的颜色
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 清除颜色缓存和深度缓存

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textures[1]);
        
        ourShader.setFloat("mixValue", mixValue);

        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        trans = glm::rotate(trans, timeValue, glm::vec3(0.0f, 0.0f, 1.0f));
        trans = glm::scale(trans, glm::vec3(1.0f, 1.0f, 1.0f));
        // int transLoc = glGetUniformLocation(ourShader.ID, "transform");
        // uniform变量的位置值，传递的个数，是否转置（OpenGL和glm均为列主序），矩阵数据（用value_ptr转换为OpenGL接受的格式）
        // glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(trans));
        
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 proj = glm::mat4(1.0f);
        // model = glm::rotate(model, timeValue * glm::radians(-55.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        // glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f); // 正射投影平截头体左，右，底部，顶部，近平面，远平面
        proj = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f); // 透视平截头体fov，宽高比，近平面，远平面
        
        int viewLoc = glGetUniformLocation(ourShader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        int projLoc = glGetUniformLocation(ourShader.ID, "projection");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            if (i % 3 == 0)
            {
                model = glm::rotate(model, timeValue * glm::radians(55.0f), glm::vec3(0.5f, 1.0f, 0.0f));
            }

            int modelLoc = glGetUniformLocation(ourShader.ID, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        // 绘制的图元类型，顶点数组的起始索引，绘制顶点数
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        glfwSwapBuffers(window); //交换颜色缓冲，它存储着GLFW窗口每个像素颜色的大缓冲
        // 双缓冲，前缓冲保存并显示着最终输出的图像，所有的渲染指令则在后缓冲上绘制。
        glfwPollEvents(); // 函数检查有没有触发事件，鼠标键盘、更新窗口状态，并调用对应的回调函数
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

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
        glfwWindowShouldClose(window);
    }
    if (glfwGetKey(window, GLFW_KEY_W))
    {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A))
    {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S))
    {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D))
    {
        camera.ProcessKeyboard(RIGHT, deltaTime);
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