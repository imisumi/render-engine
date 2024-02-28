#version 460 core

// in vec3 fragColor;
// in vec2 fragTexCoord;

// out vec4 screenColor;

// uniform sampler2D material;

// void main()
// {
// 	// screenColor = vec4(fragColor, 1.0);
// 	vec3 baseColor = texture(material, fragTexCoord).rgb;
	

// 	screenColor = texture(material, fragTexCoord);
// }




// Outputs colors in RGBA
out vec4 FragColor;


// Inputs the color from the Vertex Shader
in vec3 color;
// Inputs the texture coordinates from the Vertex Shader
in vec2 texCoord;

// Gets the Texture Unit from the main function
uniform sampler2D tex0;


void main()
{
	FragColor = texture(tex0, texCoord);
}