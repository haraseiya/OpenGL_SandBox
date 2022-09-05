#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void ProcessInput(GLFWwindow* window);
void FrameBufferSizeCallBack(GLFWwindow* window, int width, int height);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main(int argc,char** argv)
{
	// GLFWを初期化
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// ウィンドウオブジェクトを作成
	// 全てのウィンドウデータを保持し、GLFW以外の他のほとんどの機能で必要とされる
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "GraphicsTest", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "GLFWウィンドウの作成に失敗しました" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallBack);

	// GLADの初期化
	// GLADはOpenGLの関数ポインタを管理する
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "GLADの初期化に失敗しました" << std::endl;
		return -1;
	}

	// レンダリングループ
	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// GLFWに割り当てられたすべてのリソースを適切に削除
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
	// レンダリング開始前にウィンドウサイズを伝える
	// 最初2つのパラメータで左下隅の位置を設定
	glViewport(0, 0, width, height);
}