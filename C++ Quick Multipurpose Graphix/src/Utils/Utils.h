#pragma once

#include <ctime>
#include <chrono>
#include <sstream>
#include <iostream>
#include <gl/glew.h>
#include <GLFW/glfw3.h>

typedef unsigned long int BIGINT;

static char * getDisplayTime()
{
	time_t now = time(0);
	char * dt = ctime(&now);
	return dt;
}

static BIGINT getTime()
{
	time_t now = time(0);
	return (BIGINT)now;
}

class HighResStopwatch
{
private:
	std::chrono::high_resolution_clock::time_point start;

public:
	HighResStopwatch() {}
	~HighResStopwatch() {}

	void reset()
	{
		start = std::chrono::high_resolution_clock::now();
	}

	double read()
	{
		std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - start);
		return time_span.count();
	}

	std::chrono::high_resolution_clock::time_point getStart()
	{
		return start;
	}

	void setStart(std::chrono::high_resolution_clock::time_point starting)
	{
		start = starting;
	}
};


enum DrawOps { Line, Fill };
enum Sides { FrontBack, Front, Back, Cullface };

static void setDrawOption(DrawOps option = Fill, Sides sides = FrontBack)
{
	if (option == Fill && sides == FrontBack)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	else if (option == Fill && sides == Front)
	{
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_LINE);
	}
	else if (option == Fill && sides == Back)
	{
		glPolygonMode(GL_BACK, GL_FILL);
		glPolygonMode(GL_FRONT, GL_LINE);
	}
	else if (option == Fill && sides == Cullface)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_CULL_FACE);
	}
	else if (option == Line && sides == FrontBack)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else if (option == Line && sides == Front)
	{
		glEnable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT, GL_LINE);
	}
	else if (option == Line && sides == Back)
	{
		glEnable(GL_CULL_FACE);
		glPolygonMode(GL_BACK, GL_LINE);
	}
	else if (option == Line && sides == Cullface)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glEnable(GL_CULL_FACE);
	}
}

template<typename T>
inline std::vector<T> subvec(std::vector<T> v, int s, int e)
{
	std::vector<T> vec(e - s + 1);
	std::copy(v.begin() + s, v.begin() + e + 1, vec.begin());
	return vec;
}


inline std::vector<std::string> tokenizeString(std::string str)
{
	std::vector<std::string> tokens;

	std::istringstream ss(str);
	do
	{
		std::string token;
		ss >> token;

		tokens.push_back(token);
	} while (ss);

	return tokens;
}

inline void DO_NOT_USE(std::string funcName)
{
	glfwTerminate();
	std::cout << "[WARNING-ERROR] A function in your program is not for use." << std::endl;
	std::cout << "FUNCTION_NAME: " + funcName << std::endl;
	std::cin.get();
	exit(1);
}