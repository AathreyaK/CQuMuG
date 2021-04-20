#pragma once

#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <string>
#include <fstream>

#include "../../Utils/GLDebugger.h"

class Shader
{
private:
	GLuint m_id;

public:
	Shader(const char * vertPath, const char * fragPath);
	~Shader();

	int getAttribLoc(const char * name);

	void Bind();
	void Unbind();

	void set1F(GLfloat value, const GLchar * name);
	void set1I(GLint value, const GLchar * name);

	void setV2F(glm::fvec2 value, const GLchar * name);
	void setV3F(glm::fvec3 value, const GLchar * name);
	void setV4F(glm::fvec4 value, const GLchar * name);

	void setM2FV(glm::mat2 value, const GLchar * name, GLboolean transpose = GL_FALSE);
	void setM3FV(glm::mat3 value, const GLchar * name, GLboolean transpose = GL_FALSE);
	void setM4FV(glm::mat4 value, const GLchar * name, GLboolean transpose = GL_FALSE);
};