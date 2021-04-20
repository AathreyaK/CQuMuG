#version 330 core

in vec3 v_position;
in vec4 v_color;

out vec4 f_color;

uniform mat4 u_VPMat;

void main()
{
	f_color = v_color;
	gl_Position = u_VPMat * vec4(v_position, 1.0f);
}