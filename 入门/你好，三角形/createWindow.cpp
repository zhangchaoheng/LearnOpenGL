#include<glad/glad.h>
#include<GLFW/glfw3.h>	
#include<iostream>


//回调函数，针对窗口
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
	glfwInit(); //初始化
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	//创建窗口
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window); //将这个窗口设置为当前context
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //每当窗口调整大小的时候调用这个函数
	//给GLAD传入了用来加载系统相关的OpenGL函数指针地址
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "GLAD初始化失败" << std::endl;
		return -1;
	}

	//检测是否需要关闭窗口
	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f); //设置清空屏幕所用的颜色
		glClear(GL_COLOR_BUFFER_BIT); //接受一个缓冲位(Buffer Bit)来指定要清空的缓冲

		glfwSwapBuffers(window);//交换渲染好和已经展示的窗口缓冲，双缓冲
		glfwPollEvents(); //检测有无事件触发
	}
	glfwTerminate();
	return 0;

}

void processInput(GLFWwindow* window) {
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) //检测是否按下返回键
		glfwSetWindowShouldClose(window, true); //按下则关闭窗口
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height); //设置窗口的维度
}
