#include "Window.h"

int key_pressed[GLFW_KEY_LAST] = { 0 };
int button_pressed[GLFW_MOUSE_BUTTON_LAST] = { 0 };

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	for (int i = 0; i < GLFW_KEY_LAST; i++)
	{
		if (key == i && action == GLFW_RELEASE) { key_pressed[i] = 0; };
		if (key == i && action == GLFW_PRESS) { key_pressed[i] = 1; };
		if (key == i && action == GLFW_REPEAT) { key_pressed[i] = 2; };
	}
}

void cursor_enter_callback(GLFWwindow* window, int entered)
{
	if (entered)
	{
		// The cursor entered the client area of the window
	}
	else
	{
		// The cursor left the client area of the window
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST; i++)
	{
		if (button == i && action == GLFW_RELEASE) { button_pressed[i] = 0; };
		if (button == i && action == GLFW_PRESS) { button_pressed[i] = 1; };
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
}

void framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH)
{
	glViewport(0, 0, fbW, fbH);
}

int framebufferWidth = 0;
int framebufferHeight = 0;

Window::Window(int x, int y, const char * name, const char * window_icon)
{
	m_closeRequest = false;

	if (!glfwInit())
		exit(-1);

	m_window = glfwCreateWindow(x, y, name, NULL, NULL);
	if (!m_window)
	{
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(m_window);

	glfwGetFramebufferSize(m_window, &framebufferWidth, &framebufferHeight);
	glfwSetFramebufferSizeCallback(m_window, framebuffer_resize_callback);

	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	GLFWimage icon[1];
	icon[0].pixels = SOIL_load_image(window_icon, &icon[0].width, &icon[0].height, 0, SOIL_LOAD_RGBA);
	glfwSetWindowIcon(m_window, 1, icon);
	SOIL_free_image_data(icon[0].pixels);

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LESS);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Switch to GL_LINE TO DRAW OUTLINE
	
	glViewport(0, 0, x, y);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	glewExperimental = GL_TRUE;

	Refresh();
}

Window::~Window()
{
}

bool Window::isClosed()
{
	return glfwWindowShouldClose(m_window);
}

void Window::close()
{
	glfwTerminate();
	exit(0);
}

void Window::Refresh()
{
	glfwSwapBuffers(m_window);

	glfwPollEvents();

	glFlush();

	glfwSetCursorPosCallback(m_window, cursor_position_callback);
	glfwSetKeyCallback(m_window, key_callback);
	glfwSetCursorEnterCallback(m_window, cursor_enter_callback);
	glfwSetMouseButtonCallback(m_window, mouse_button_callback);
	glfwSetScrollCallback(m_window, scroll_callback);
	glfwSetFramebufferSizeCallback(m_window, framebuffer_resize_callback);

	glfwGetWindowSize(m_window, &m_width, &m_height);
}

void Window::ChangeColor(float r, float b, float g, float a) 
{ 
	glClearColor(r, b, g, a); 
}

void Window::Resize(GLFWwindow* window, int width, int height) 
{ 
	glViewport(0, 0, width, height); 
}

int Window::getWidth() 
{ 
	return m_width; 
}

int Window::getHeight() 
{ 
	return m_height; 
}

glm::vec2 Window::getMousePos()
{
	double xpos, ypos;
	glfwGetCursorPos(m_window, &xpos, &ypos);
	glm::vec2 mousevec = { xpos, ypos };

	return mousevec;
}

void Window::setMousePos(glm::vec2 pos)
{
	glfwSetCursorPos(m_window, pos.x, pos.y);
}