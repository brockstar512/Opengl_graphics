#version 400

in vec3 vertexIn;
in vec3 colorIn;
in vec2 textureIn;

out vec3 colorOut;
out vec2 textureOut;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;



void main()
{
	textureOut = textureIn; 
	colorOut = colorIn;
	gl_Position = projection * view * model * vec4(vertexIn,1.0);
}