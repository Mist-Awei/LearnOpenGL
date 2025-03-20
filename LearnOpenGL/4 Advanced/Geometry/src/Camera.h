#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
// ��������ƶ�ѡ��
enum Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};
// ���Ĭ�ϲ���
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 1.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

// ��������࣬�������벢������Ӧ��ŷ���ǣ�ʸ���;�������OpenGL
class Camera
{
public:
	// �������
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WordUp;
	// ŷ����
	float Yaw;
	float Pitch;
	// ���ѡ��
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;
	// �������캯��
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH)
		: Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		Position = position;
		WordUp = up;
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}
	// �������캯��
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		Position = glm::vec3(posX, posY, posZ);
		WordUp = glm::vec3(upX, upY, upZ);
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}
	// ����LookAt�۲����
	glm::mat4 getLookatMatrix()
	{
		/*
		//R����������U����������D�Ƿ�������������������෴����P�������λ������
		glm::vec3 D = glm::normalize(position - target);
		glm::vec3 R = glm::normalize(glm::cross(glm::normalize(wordUp), D));
		glm::vec3 U = glm::normalize(glm::cross(D, R));
		*/
		glm::vec3 R = Right;
		glm::vec3 U = Up;
		glm::vec3 D = -Front;
		glm::mat4 rotation = glm::mat4(1.0f);
		glm::mat4 translation = glm::mat4(1.0f);
		// λ���������෴�ģ�����ƶ�������λ�ǰ�����ƽ�Ƶ����ƶ����෴����
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
	// ����view��ͼ����
	glm::mat4 GetViewMatrix()
	{
		return getLookatMatrix();
		// return glm::lookAt(Position, Position + Front, Up);
	}
	// �����������,������������ENUM��ʽ�������������windowing systems�г������
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
		// ȡ����ֱλ�ƣ�ʹ�û����ڵ���
		// Position.y = 0.6f;
	}
	// �����������
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
	{
		xoffset *= MouseSensitivity;
		yoffset *= MouseSensitivity;

		Yaw += xoffset;
		Pitch += yoffset;
		// ���Ƹ����ǳ��磬ȷ����Ļ���ᱻ��ת
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
		// �ø��º��ŷ���Ǹ������Front��Right��Up����
		updateCameraVectors();
	}
	// ����������,ֻ��Ҫ����ֱ����
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
	// �������ŷ���Ǽ��㲢����Front����
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
