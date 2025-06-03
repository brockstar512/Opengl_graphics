#version 400

in vec3 vertexIn;
in vec3 colorIn;
in vec2 textureIn;

out vec3 colorOut;
out vec2 textureOut;
out vec3 vertexOut;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;



void main()
{
	textureOut = textureIn; 
	colorOut = colorIn;
	vertexOut = (model * vec4(vertexIn,1.0)).xyz;
	gl_Position = projection * view * model * vec4(vertexIn,1.0);
}