#version 460 core

// layout (location=0) in vec3 pos;
// // layout (location=1) in vec3 vertexColor;
// layout (location=1) in int colorIndex;

// out vec3 fragColor;
// out vec2 fragTexCoord;

// const vec3 colors[4] = vec3[](
// 	vec3(1.0, 0.0, 0.0),
// 	vec3(0.0, 1.0, 0.0),
// 	vec3(0.0, 0.0, 1.0),
// 	vec3(0.7647, 1.0, 0.0)
// );

// uniform mat4 model;
// uniform mat4 view;
// uniform mat4 projection;


// void main()
// {
// 	gl_Position = vec4(pos, 1.0);
// 	// fragColor = vertexColor;
// 	fragColor = colors[colorIndex];
// 	// fragColor = colors[gl_VertexID];

// 	// fragTexCoord = pos.xy;
// 	gl_Position = projection * view * model * vec4(pos, 1.0);

// 	fragTexCoord = vec2(0.5, -0.5) * (pos.xy + vec2(1));

// }




// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec3 aColor;
// Texture Coordinates
layout (location = 2) in vec2 aTex;


// Outputs the color for the Fragment Shader
out vec3 color;
// Outputs the texture coordinates to the fragment shader
out vec2 texCoord;

// Controls the scale of the vertices
uniform float scale;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	// Outputs the positions/coordinates of all vertices
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	// Assigns the colors from the Vertex Data to "color"
	color = aColor;
	// Assigns the texture coordinates from the Vertex Data to "texCoord"
	texCoord = aTex;
}