#include "Shader.h"

std::string loadSource(std::string path)
{
	std::ifstream inFile;
	inFile.open(path, std::ifstream::in);
	
	std::string src = "", temp;

	while (std::getline(inFile, temp))
		src += temp + "\n";

	return src;
}

GLuint createShader(const char * src, GLenum type)
{
	GLuint shader = glCreateShader(type); GL_DEBUG;
	glShaderSource(shader, 1, &src, NULL); GL_DEBUG;

	glCompileShader(shader); GL_DEBUG;

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status); GL_DEBUG;
	if (status != GL_TRUE)
	{
		char buffer[512];
		glGetShaderInfoLog(shader, 512, NULL, buffer); GL_DEBUG;
		std::cerr << buffer << std::endl;
		glfwTerminate();
		std::cin.get();
		exit(-1);
	}

	return shader;
}

Shader::Shader(const char * vertPath, const char * fragPath)
{
	std::string vertSrc = loadSource(vertPath);
	std::string fragSrc = loadSource(fragPath);

	GLuint vertShader = createShader(vertSrc.c_str(), GL_VERTEX_SHADER); GL_DEBUG;
	GLuint fragShader = createShader(fragSrc.c_str(), GL_FRAGMENT_SHADER); GL_DEBUG;

	m_id = glCreateProgram(); GL_DEBUG;
	glAttachShader(m_id, vertShader); GL_DEBUG;
	glAttachShader(m_id, fragShader); GL_DEBUG;

	glBindFragDataLocation(m_id, 0, "outColor"); GL_DEBUG;

	glLinkProgram(m_id); GL_DEBUG;

	glDeleteShader(vertShader); GL_DEBUG;
	glDeleteShader(fragShader); GL_DEBUG;

	glUseProgram(m_id); GL_DEBUG;
}

Shader::~Shader()
{
	glDeleteProgram(m_id); GL_DEBUG;
}

int Shader::getAttribLoc(const char * name)
{
	int loc = glGetAttribLocation(m_id, name); GL_DEBUG;
	if (loc == -1)
		std::cerr << "[ERROR] :: Shader :: The attribute " + std::string(name) + " does not exist in this shader.\n";
	return loc;
}

void Shader::Bind()
{
	glUseProgram(m_id); GL_DEBUG;
}

void Shader::Unbind()
{
	glUseProgram(0); GL_DEBUG;
}

void Shader::set1F(GLfloat value, const GLchar * name)
{
	this->Bind();
	glUniform1f(glGetUniformLocation(this->m_id, name), value);
	Shader::Unbind();
}

void Shader::set1I(GLint value, const GLchar * name)
{
	this->Bind();
	glUniform1i(glGetUniformLocation(this->m_id, name), value);
	Shader::Unbind();
}

void Shader::setV2F(glm::fvec2 value, const GLchar * name)
{
	this->Bind();
	glUniform2fv(glGetUniformLocation(this->m_id, name), 1, glm::value_ptr(value));
	Shader::Unbind();
}

void Shader::setV3F(glm::fvec3 value, const GLchar * name)
{
	this->Bind();
	glUniform3fv(glGetUniformLocation(this->m_id, name), 1, glm::value_ptr(value));
	Shader::Unbind();
}

void Shader::setV4F(glm::fvec4 value, const GLchar * name)
{
	this->Bind();
	glUniform4fv(glGetUniformLocation(this->m_id, name), 1, glm::value_ptr(value));
	Shader::Unbind();
}

void Shader::setM2FV(glm::mat2 value, const GLchar * name, GLboolean transpose)
{
	this->Bind();
	glUniformMatrix2fv(glGetUniformLocation(this->m_id, name), 1, transpose, glm::value_ptr(value));
	Shader::Unbind();
}

void Shader::setM3FV(glm::mat3 value, const GLchar * name, GLboolean transpose)
{
	this->Bind();
	glUniformMatrix3fv(glGetUniformLocation(this->m_id, name), 1, transpose, glm::value_ptr(value));
	Shader::Unbind();
}

void Shader::setM4FV(glm::mat4 value, const GLchar * name, GLboolean transpose)
{
	this->Bind();
	glUniformMatrix4fv(glGetUniformLocation(this->m_id, name), 1, transpose, glm::value_ptr(value));
	Shader::Unbind();
}