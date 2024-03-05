#version 420 core

layout(location=0)in vec4 position;
layout(location=1)in vec3 color;
layout(location=2)in vec2 texCoord;

out vec3 v_Color;
out vec2 v_TexCoord;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
	gl_Position = u_Projection * u_View * u_Model * position;
	v_Color = color;
	v_TexCoord = texCoord;
}
