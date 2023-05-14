#version 330 core

out vec4 colorOut;

uniform vec3 color;

void main()
{
	colorOut = vec4(color, 1.0f);
}