#include<glad/glad.h>
#include<GLFW/glfw3.h>	
#include<iostream>
#include"shader.h"

//�ص���������Դ���
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
	glfwInit(); //��ʼ��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	//��������
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window); //�������������Ϊ��ǰcontext
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //ÿ�����ڵ�����С��ʱ������������
	//��GLAD��������������ϵͳ��ص�OpenGL����ָ���ַ
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "GLAD��ʼ��ʧ��" << std::endl;
		return -1;
	}

	Shader ourShader("3.3.shader.vs", "3.3.shader.fs");


	float vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
	};

	unsigned int VBO,VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);//����VBO����
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//��VBO�󶨵���Ӧ�Ļ�����,����ֻ��Ҫ�������������ǲ������VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//���������ݴ浽�������


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);//����OpenGL����ν�����������
	glEnableVertexAttribArray(0);//���ö�������

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//���VBO��VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//����Ƿ���Ҫ�رմ���
	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //���������Ļ���õ���ɫ
		glClear(GL_COLOR_BUFFER_BIT); //����һ������λ(Buffer Bit)��ָ��Ҫ��յĻ���


		//��������
		ourShader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);//������Ⱦ�ú��Ѿ�չʾ�Ĵ��ڻ��壬˫����
		glfwPollEvents(); //��������¼�����
	}

	//ɾ���������ڽ����Ķ���
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;

}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) //����Ƿ��·��ؼ�
		glfwSetWindowShouldClose(window, true); //������رմ���
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height); //���ô��ڵ�ά��
}