#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void ProcessInput(GLFWwindow* window);
void FrameBufferSizeCallBack(GLFWwindow* window, int width, int height);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main(int argc,char** argv)
{
	// GLFW��������
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// �E�B���h�E�I�u�W�F�N�g���쐬
	// �S�ẴE�B���h�E�f�[�^��ێ����AGLFW�ȊO�̑��̂قƂ�ǂ̋@�\�ŕK�v�Ƃ����
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "GraphicsTest", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "GLFW�E�B���h�E�̍쐬�Ɏ��s���܂���" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallBack);

	// GLAD�̏�����
	// GLAD��OpenGL�̊֐��|�C���^���Ǘ�����
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "GLAD�̏������Ɏ��s���܂���" << std::endl;
		return -1;
	}

	// �����_�����O���[�v
	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// GLFW�Ɋ��蓖�Ă�ꂽ���ׂẴ��\�[�X��K�؂ɍ폜
	glfwTerminate();

	return 0;
}

void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void FrameBufferSizeCallBack(GLFWwindow* window, int width, int height)
{
	// �����_�����O�J�n�O�ɃE�B���h�E�T�C�Y��`����
	// �ŏ�2�̃p�����[�^�ō������̈ʒu��ݒ�
	glViewport(0, 0, width, height);
}