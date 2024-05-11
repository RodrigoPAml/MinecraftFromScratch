#version 330 core

out vec4 outColor;

in vec2 uv;
uniform sampler2D image;

void main()
{
	vec4 texFrag = texture(image, uv);

	if(texFrag.a < 0.5f)
	{
		discard;
	}

	outColor =  vec4(texFrag.xyz, 1.0f);
}