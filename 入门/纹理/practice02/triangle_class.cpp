#include<glad/glad.h>
#include<GLFW/glfw3.h>	
#include<iostream>
#include"shader.h"
#include "stb_image.h"

//�ص���������Դ���
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
	glfwInit(); //��ʼ��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(  GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	//��������
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);

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
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f  // top left 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};


	unsigned int VBO,VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);//����VBO����
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//��VBO�󶨵���Ӧ�Ļ�����,����ֻ��Ҫ�������������ǲ������VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//���������ݴ浽�������

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);//����OpenGL����ν�����������
	glEnableVertexAttribArray(0);//���ö�������

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//���VBO��VAO
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);

	//����������ͼ
	unsigned int texture1, texture2;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	//Ϊ�󶨵��������û��ƺ͹��˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//��תy��
	stbi_set_flip_vertically_on_load(true);
	//�����������������
	int width, height, nrChannels;
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	if (data) {
		//ʹ��ǰ�������ͼƬ��������һ������
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "��������ʧ��" << std::endl;
	}
	stbi_image_free(data);

	//����2
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	//Ϊ�󶨵��������û��ƺ͹��˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
	if (data) {
		//ʹ��ǰ�������ͼƬ��������һ������,ע��������RGBA
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "��������ʧ��" << std::endl;
	}
	stbi_image_free(data);

	ourShader.use();
	ourShader.setInt("texture1", 0);
	ourShader.setInt("texture2", 1);
	//����Ƿ���Ҫ�رմ���
	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //���������Ļ���õ���ɫ
		glClear(GL_COLOR_BUFFER_BIT); //����һ������λ(Buffer Bit)��ָ��Ҫ��յĻ���

		//������
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		//��������
		ourShader.use();

		glBindVertexArray(VAO);
		//�Զ�������ֵ��Ƭ����ɫ���Ĳ�������sampler2D ourTexture,��Ƭ����ɫ����
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);//������Ⱦ�ú��Ѿ�չʾ�Ĵ��ڻ��壬˫����
		glfwPollEvents(); //��������¼�����
	}

	//ɾ���������ڽ����Ķ���
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

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



