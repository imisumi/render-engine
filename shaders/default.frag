#version 460 core

in vec3 fragColor;
in vec2 fragTexCoord;

out vec4 screenColor;

uniform sampler2D material;

void main()
{
	// screenColor = vec4(fragColor, 1.0);
	vec3 baseColor = texture(material, fragTexCoord).rgb;
	

	screenColor = texture(material, fragTexCoord);
}