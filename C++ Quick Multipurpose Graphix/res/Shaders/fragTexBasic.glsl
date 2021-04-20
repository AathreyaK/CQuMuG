#version 330 core

in vec4 f_color;
in vec2 f_texCoords;

out vec4 outColor;

uniform sampler2D f_texture;

void main()
{
    outColor = texture(f_texture, f_texCoords) * f_color;
}