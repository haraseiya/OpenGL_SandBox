#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void ProcessInput(GLFWwindow* window);
void FrameBufferSizeCallBack(GLFWwindow* window, int width, int height);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

float vertices[] =
{
	0.5f,0.5f,0.0f,
	0.5f,-0.5f,0.0f,
	-0.5f,-0.5f,0.0f,
	-0.5f,0.5f,0.0f
};

unsigned int indices[] =
{
	0,1,3,
	1,2,3
};

int main(int argc, char** argv)
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

	// ���_�V�F�[�_�[�쐬
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// �t���O�����g�V�F�[�_�[�쐬
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// �쐬�������_�V�F�[�_�[�ƃt���O�����g�V�F�[�_�[�������N������
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// �K�v�Ȃ��Ȃ�̂ŗ��V�F�[�_�[�j��
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// ���_�o�b�t�@�̍쐬�iCPU����GPU�ւ̓]���͎��Ԃ������邽�߁AVBO�ɂ܂Ƃ߂Ē��_�Ԃ�����ň�C�ɑ���ƌ����I�j
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// ���Œ�`���ꂽ���_�f�[�^���o�b�t�@�̃������ɃR�s�[
	// �ŏ��̈����̓f�[�^���R�s�[�������o�b�t�@�̃^�C�v�iGL_ARRAY_BUFFER�Ɍ��݃o�C���h����Ă���VBO���Ώہj
	// 2�Ԗڂ̈����̓o�b�t�@�ɓn���f�[�^�̃T�C�Y
	// 3�Ԗڂ͎��ۂɑ��M����f�[�^
	// 4�Ԗڂ̓O���t�B�b�N�X�J�[�h������̃f�[�^���ǂ̂悤�ɊǗ����邩

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// �����_�����O���[�v
	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

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