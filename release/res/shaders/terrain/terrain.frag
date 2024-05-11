#version 330 core

out vec4 colorOut;

in vec3 interpNormal;
in vec2 interpUV;

uniform sampler2D tex;

void main()
{
	vec4 texS = texture(tex, interpUV);

	if(texS.r < 0.1 && texS.g < 0.1 && texS.b < 0.1f)
	{
		discard;
	}

	vec3 lightDir = vec3(0.0f, -1.0f, 0.0f);
	float diff = (dot(normalize(interpNormal), lightDir) + 1)*0.5f;

	vec3 ambient = 0.1f * texS.rgb;
	vec3 diffuse =  diff * texS.rgb;

	colorOut = vec4(ambient+diffuse, 1.0);
}