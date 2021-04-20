#pragma once

#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <glm.hpp>
#include <fstream>

class Window
{
private:
	GLFWwindow * m_window;
	bool m_closeRequest;
	int m_width;
	int m_height;

public:
	Window(int x, int y, const char * name, const char * window_icon);
	~Window();

	bool isClosed();
	void close();

	void Refresh();

	void ChangeColor(float r, float b, float g, float a);

	void Resize(GLFWwindow* window, int width, int height);
	int getWidth();
	int getHeight();

	glm::vec2 getMousePos();
	void setMousePos(glm::vec2 pos);
};