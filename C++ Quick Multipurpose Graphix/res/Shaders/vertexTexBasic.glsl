#version 330 core

in vec3 v_position;
in vec4 v_color;
in vec2 v_texCoords;

out vec4 f_color;
out vec2 f_texCoords;

uniform mat4 u_VPMat;

void main()
{
	f_color = v_color;
	f_texCoords = v_texCoords;
	gl_Position = u_VPMat * vec4(v_position, 1.0f);
}