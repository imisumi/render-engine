#version 460 core

layout (location=0) in vec3 pos;
// layout (location=1) in vec3 vertexColor;
layout (location=1) in int colorIndex;

out vec3 fragColor;
out vec2 fragTexCoord;

const vec3 colors[4] = vec3[](
	vec3(1.0, 0.0, 0.0),
	vec3(0.0, 1.0, 0.0),
	vec3(0.0, 0.0, 1.0),
	vec3(0.7647, 1.0, 0.0)
);

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
	gl_Position = vec4(pos, 1.0);
	// fragColor = vertexColor;
	fragColor = colors[colorIndex];
	// fragColor = colors[gl_VertexID];

	// fragTexCoord = pos.xy;
	gl_Position = projection * view * model * vec4(pos, 1.0);

	fragTexCoord = vec2(0.5, -0.5) * (pos.xy + vec2(1));

}