#include <stb_image/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "CallError.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ElementBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"

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

    {
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
        // 世界坐标位置
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
        /*
        float vertices[] = {
         -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        };
        */
        // 索引数组
        unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3
        };

        // GLCall(glEnable(GL_BLEND));
        // GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        // 创建顶点缓冲对象VBO
        VertexBuffer VBO(vertices, 36 * 5 * sizeof(float));
        // 创建顶点数组对象VAO
        VertexArray VAO;
        // 绑定VAO和VBO
        VAO.Bind();
        VBO.Bind();

        // 顶点数组布局
        VertexBufferLayout layout;
        layout.Push<float>(3); // 顶点坐标
        layout.Push<float>(2); // 纹理坐标
        VAO.AddBuffer(VBO, layout);

        
        //创建元素缓冲对象EBO
        ElementBuffer EBO(indices, 6);
        
        // 创建着色器shader
        Shader ourShader("./shader/vertex.glsl", "./shader/fragment.glsl");
        ourShader.Use();
        ourShader.setInt("texture1", 0);
        ourShader.setInt("texture2", 1);
        
        Texture texture1("./texture/container.jpg", GL_RGB);
        Texture texture2("./texture/awesomeface.png", GL_RGBA);

        // VAO.Unbind(); 
        VBO.Unbind(); // 调用glVertexAttribPointer将VBO注册为顶点属性的绑定顶点缓冲对象后可以解除绑定
        // EBO.Unbind();

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
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // 设置清空屏幕所需要的颜色
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 清除颜色缓存和深度缓存

            texture1.Bind();
            texture2.Bind(1);

            glm::mat4 view = camera.GetViewMatrix();
            glm::mat4 proj = glm::mat4(1.0f);
            // glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f); // 正射投影平截头体左，右，底部，顶部，近平面，远平面
            proj = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f); // 透视平截头体fov，宽高比，近平面，远平面
            ourShader.setFloat("MixValue", mixValue);
            ourShader.setMat4("view", view);
            ourShader.setMat4("projection", proj);
            VAO.Bind();
            for (unsigned int i = 0; i < 10; i++)
            {
                // calculate the model matrix for each object and pass it to shader before drawing
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                float angle = 20.0f * i;
                if (i % 3 == 0)
                {
                    angle = timeValue * 25.0f;
                }
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                ourShader.setMat4("model", model);

                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
            
            // 绘制的图元类型，顶点数组的起始索引，绘制顶点数
            // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            glfwSwapBuffers(window); //交换颜色缓冲，它存储着GLFW窗口每个像素颜色的大缓冲
            // 双缓冲，前缓冲保存并显示着最终输出的图像，所有的渲染指令则在后缓冲上绘制。
            glfwPollEvents(); // 函数检查有没有触发事件，鼠标键盘、更新窗口状态，并调用对应的回调函数
        }
    }
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
    if (glfwGetKey(window, GLFW_KEY_UP))
    {
        mixValue += 0.001;
        if (mixValue > 1.0f)
        {
            mixValue = 1.0f;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN))
    {
        mixValue -= 0.001;
        if (mixValue < 0.0f)
        {
            mixValue = 0.0f;
        }
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
