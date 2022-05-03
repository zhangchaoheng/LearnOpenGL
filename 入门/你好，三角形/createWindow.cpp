#include<glad/glad.h>
#include<GLFW/glfw3.h>	
#include<iostream>


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

	//����Ƿ���Ҫ�رմ���
	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f); //���������Ļ���õ���ɫ
		glClear(GL_COLOR_BUFFER_BIT); //����һ������λ(Buffer Bit)��ָ��Ҫ��յĻ���

		glfwSwapBuffers(window);//������Ⱦ�ú��Ѿ�չʾ�Ĵ��ڻ��壬˫����
		glfwPollEvents(); //��������¼�����
	}
	glfwTerminate();
	return 0;

}

void processInput(GLFWwindow* window) {
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) //����Ƿ��·��ؼ�
		glfwSetWindowShouldClose(window, true); //������رմ���
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height); //���ô��ڵ�ά��
}
