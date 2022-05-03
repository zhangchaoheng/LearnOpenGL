#include<glad/glad.h>
#include<GLFW/glfw3.h>	
#include<iostream>


//回调函数，针对窗口
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"                  //in，表示输入
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"   //gl_Position是预定义的，表示输出
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

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

	//顶点着色器
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);//创建顶点着色器
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//将顶点着色器源码附加给这个vertexShader
	glCompileShader(vertexShader);//编译shader

	//检测顶点着色器是否编译成功
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//片段着色器
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//检测片段着色器是否编译成功
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//将顶点着色器和片段着色器都附加在程序上，并且链接起来
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);


	//检验链接是否成功
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader); //将之前的顶点着色器和片段着色器可以删除
	glDeleteShader(fragmentShader);


	float firstTriangle[] = {
		-0.9f, -0.5f, 0.0f,  // left 
		-0.0f, -0.5f, 0.0f,  // right
		-0.45f, 0.5f, 0.0f,  // top 
	};
	float secondTriangle[] = {
		0.0f, -0.5f, 0.0f,  // left
		0.9f, -0.5f, 0.0f,  // right
		0.45f, 0.5f, 0.0f   // top 
	};

	unsigned int VBOs[2], VAOs[2];
	glGenVertexArrays(2, VAOs);//创造VAO和VBO数组对象
	glGenBuffers(2, VBOs);

	//第一个三角形
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//告诉OpenGL该如何解析顶点数据
	glEnableVertexAttribArray(0);//启用顶点属性

	//第二个三角形
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//告诉OpenGL该如何解析顶点数据
	glEnableVertexAttribArray(0);//启用顶点属性

	//解绑VBO和VAO
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);

	//检测是否需要关闭窗口
	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //设置清空屏幕所用的颜色
		glClear(GL_COLOR_BUFFER_BIT); //接受一个缓冲位(Buffer Bit)来指定要清空的缓冲

		//画三角形
		glUseProgram(shaderProgram);
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);//交换渲染好和已经展示的窗口缓冲，双缓冲
		glfwPollEvents(); //检测有无事件触发
	}

	//删除生命周期结束的对象
	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
	glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;

}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) //检测是否按下返回键
		glfwSetWindowShouldClose(window, true); //按下则关闭窗口
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height); //设置窗口的维度
}
