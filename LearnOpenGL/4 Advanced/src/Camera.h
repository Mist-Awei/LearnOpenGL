#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
// 定义相机移动选项
enum Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};
// 相机默认参数
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 1.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

// 抽象相机类，处理输入并计算相应的欧拉角，矢量和矩阵，用于OpenGL
class Camera
{
public:
	// 相机属性
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WordUp;
	// 欧拉角
	float Yaw;
	float Pitch;
	// 相机选项
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;
	// 向量构造函数
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH)
		: Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		Position = position;
		WordUp = up;
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}
	// 标量构造函数
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		Position = glm::vec3(posX, posY, posZ);
		WordUp = glm::vec3(upX, upY, upZ);
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}
	// 计算LookAt观察矩阵
	glm::mat4 getLookatMatrix()
	{
		/*
		//R是右向量，U是上向量，D是方向向量（与相机朝向相反），P是摄像机位置向量
		glm::vec3 D = glm::normalize(position - target);
		glm::vec3 R = glm::normalize(glm::cross(glm::normalize(wordUp), D));
		glm::vec3 U = glm::normalize(glm::cross(D, R));
		*/
		glm::vec3 R = Right;
		glm::vec3 U = Up;
		glm::vec3 D = -Front;
		glm::mat4 rotation = glm::mat4(1.0f);
		glm::mat4 translation = glm::mat4(1.0f);
		// 位置向量是相反的，相机移动可以认位是把世界平移到与移动的相反方向
		translation[3][0] = -Position.x;
		translation[3][1] = -Position.y;
		translation[3][2] = -Position.z;
		rotation[0][0] = R.x;
		rotation[1][0] = R.y;
		rotation[2][0] = R.z;
		rotation[0][1] = U.x;
		rotation[1][1] = U.y;
		rotation[2][1] = U.z;
		rotation[0][2] = D.x;
		rotation[1][2] = D.y;
		rotation[2][2] = D.z;
		return rotation * translation;
	}
	// 返回view视图矩阵
	glm::mat4 GetViewMatrix()
	{
		return getLookatMatrix();
		// return glm::lookAt(Position, Position + Front, Up);
	}
	// 处理键盘输入,接受相机定义的ENUM形式的输入参数，从windowing systems中抽象出来
	void ProcessKeyboard(Camera_Movement direction, float deltaTime)
	{
		float velocity = MovementSpeed * deltaTime;
		if (direction == FORWARD)
		{
			Position += Front * velocity;
		}
		if (direction == BACKWARD)
		{
			Position -= Front * velocity;
		}
		if (direction == LEFT)
		{
			Position -= Right * velocity;
		}
		if (direction == RIGHT)
		{
			Position += Right * velocity;
		}
		// 取消垂直位移，使用户待在地面
		// Position.y = 0.6f;
	}
	// 处理鼠标输入
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
	{
		xoffset *= MouseSensitivity;
		yoffset *= MouseSensitivity;

		Yaw += xoffset;
		Pitch += yoffset;
		// 限制俯仰角出界，确保屏幕不会被反转
		if (constrainPitch)
		{
			if (Pitch > 89.0f)
			{
				Pitch = 89.0f;
			}
			if (Pitch < -89.0f)
			{
				Pitch = -89.0f;
			}
		}
		// 用更新后的欧拉角更新相机Front，Right，Up向量
		updateCameraVectors();
	}
	// 处理鼠标滚轮,只需要处理垂直滚轮
	void ProcessMouseScroll(float yoffset)
	{
		Zoom -= yoffset;
		if (Zoom < 1.0f)
		{
			Zoom = 1.0f;
		}
		if (Zoom > 45.0f)
		{
			Zoom = 45.0f;
		}
	}
private:
	// 从相机的欧拉角计算并更新Front向量
	void updateCameraVectors()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(front);
		Right = glm::normalize(glm::cross(Front, WordUp));
		Up = glm::normalize(glm::cross(Right, Front));
	}
};

#endif // CAMERA_H
