#pragma once

#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

#define GL_DEBUG	GLDebugger::getError(__LINE__, __FILE__);

struct GLDebugger
{
	static inline void getError(int line, std::string file)
	{
		if (glGetError() == 0)
			return;

		glfwTerminate();

		GLenum error = glGetError();
		std::cout << "----------------------------------------\n";
		std::cout << "[ERROR] :: GLDebugger :: Error occured on line " + std::to_string(line) + std::string(" of file ") + file + "\n";
		std::cout << "----------------------------------------\n";
		switch (error)
		{
		case GL_INVALID_ENUM:
			std::cout << "TYPE: GL_INVALID_ENUM\n";
			std::cout << "An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag.";
			break;
		case GL_INVALID_VALUE:
			std::cout << "TYPE: GL_INVALID_VALUE\n";
			std::cout << "A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag.";
			break;
		case GL_INVALID_OPERATION:
			std::cout << "TYPE: GL_INVALID_OPERATION\n";
			std::cout << "specified operation is not allowed in the current state.The offending command is ignored and has no other side effect than to set the error flag.";
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			std::cout << "TYPE: GL_INVALID_FRAMEBUFFER_OPERATION\n";
			std::cout << "The framebuffer object is not complete.The offending command is ignored and has no other side effect than to set the error flag.";
			break;
		case GL_OUT_OF_MEMORY:
			std::cout << "TYPE: GL_OUT_OF_MEMORY\n";
			std::cout << "There is not enough memory left to execute the command.The state of the GL is undefined, except for the state of the error flags, after this error is recorded.";
			break;
		case GL_STACK_UNDERFLOW:
			std::cout << "TYPE: GL_STACK_UNDERFLOW\n";
			std::cout << "An attempt has been made to perform an operation that would cause an internal stack to underflow.";
			break;
		case GL_STACK_OVERFLOW:
			std::cout << "TYPE: GL_STACK_OVERFLOW\n";
			std::cout << "An attempt has been made to perform an operation that would cause an internal stack to overflow.";
			break;
		default:
			std::cout << "TYPE: UNKOWN\n";
			std::cout << "Doomsday has begun. This error is very deep and we don't know what is going on here.";
			break;
		}
		std::cout << "\n----------------------------------------\n";
		std::cin.get();
	}
};