#include <stb_image/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "CallError.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ElementBuffer.h"
#include "Shader.h"
#include "Camera.h"
#include "Renderer.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height); //�ص����������ڴ�С������ʱҲ���ӿڵ���
void processInput(GLFWwindow* window); // ����������
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn); // ���λ�ûص�����
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset); // �����ֻص�����,yoffset���������ֱ�����Ĵ�С

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float mixValue = 0.5;
// timing
float deltaTime = 0.0f; // ��ǰ֡����һ֡��ʱ���
float lastFrame = 0.0f; // ��һ֡��ʱ��
// carmera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float last_X = SCR_WIDTH / 2.0f;
float last_Y = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

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
    // ���ع�겢��׽�������ڳ����ϣ����Ӧͣ���ڴ�����
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    {
        //�����������飨��׼���豸���꣩
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

        // ��������
        unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3
        };

        // �������㻺�����VBO
        VertexBuffer VBO(vertices, sizeof(vertices));
        // ���������������VAO
        VertexArray VAO;
        VAO.Bind();
        VBO.Bind();

        // �������鲼��
        VertexBufferLayout layout;
        layout.Push<float>(3); // ��������
        layout.Push<float>(2); // ��������
        VAO.AddBuffer(VBO, layout);

        
        //����Ԫ�ػ������EBO
        ElementBuffer EBO(indices, 6);
        
        // ������ɫ��shader
        Shader ourShader("./shader/vertex.glsl", "./shader/fragment.glsl");
        ourShader.Use();
        ourShader.setInt("texture1", 0);
        ourShader.setInt("texture2", 1);
        
        unsigned int textures[2];
        glGenTextures(2, textures);
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        // float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor); // ʹ��clamp_to_border��Ҫʹ��fv��׺����ָ����Ե��ɫ
        // Ϊ��ǰ�󶨵�����������û��ƺ͹��˷�ʽ
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // ���ز���������
        int width, height, nrChannels;
        unsigned char* data = stbi_load("./texture/container.jpg", &width, &height, &nrChannels, 0); // ������ͼ��Ŀ�ߺ���ɫͨ����������Ӧ����
        if (data)
        {
            // ��һ������ָ������Ŀ�꣬�ڶ�������Ϊ�����ƶ��༶��Զ����ļ��𣬵���������Ϊ����洢�ĸ�ʽ�����ĵ��������������Ŀ��
            // ������������Ϊ0����ʷ�������⣩�����ߵڰ˸�����������Դͼ�ĸ�ʽ���������ͣ����һ��������ͼ������
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
        data = stbi_load("./texture/awesomeface.png", &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }

        // VAO.Unbind(); 
        // VBO.Unbind(); // ����glVertexAttribPointer��VBOע��Ϊ�������Եİ󶨶��㻺��������Խ����
        // EBO.Unbind();
        stbi_image_free(data); // �ͷ�ͼ���ڴ�

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
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // ���������Ļ����Ҫ����ɫ
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // �����ɫ�������Ȼ���

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, textures[0]);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, textures[1]);

            glm::mat4 view = camera.GetViewMatrix();
            glm::mat4 proj = glm::mat4(1.0f);
            // model = glm::rotate(model, timeValue * glm::radians(-55.0f), glm::vec3(0.5f, 1.0f, 0.0f));
            // glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f); // ����ͶӰƽ��ͷ�����ң��ײ�����������ƽ�棬Զƽ��
            // ͸��ƽ��ͷ��fov����߱ȣ���ƽ�棬Զƽ��
            proj = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
            ourShader.setFloat("MixValue", mixValue);
            ourShader.setMat4("view", view);
            ourShader.setMat4("projection", proj);
            VAO.Bind();
            for (unsigned int i = 0; i < 10; i++)
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                if (i % 3 == 0)
                {
                    model = glm::rotate(model, timeValue * glm::radians(55.0f), glm::vec3(0.5f, 1.0f, 0.0f));
                }
                ourShader.setMat4("model", model);

                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
            // ���Ƶ�ͼԪ���ͣ������������ʼ���������ƶ�����
            // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            glfwSwapBuffers(window); //������ɫ���壬���洢��GLFW����ÿ��������ɫ�Ĵ󻺳�
            // ˫���壬ǰ���屣�沢��ʾ�����������ͼ�����е���Ⱦָ�����ں󻺳��ϻ��ơ�
            glfwPollEvents(); // ���������û�д����¼��������̡����´���״̬�������ö�Ӧ�Ļص�����
        }
    }
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
    float yoffset = last_Y - ypos; // y�����Ǵ���Ļ�µ���
    last_X = xpos;
    last_Y = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll((float)yoffset);
}