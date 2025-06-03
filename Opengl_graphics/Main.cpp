#include <iostream>
#include "Screen.h"
#include "Input.h"
#include "glad.h"
#include "Shader.h"
#include "Quad.h"
#include <glm.hpp>
#include "Camera.h"
#include "Light.h"
bool isAppRunning = true;



int main(int argc, char* argv[])
{
	Screen::Instance()->Initialize();

	if (!Shader::Instance()->CreateProgram())
	{
		return 0;
	}

	if(!Shader::Instance()->CreateShaders())
	{
		return 0;
	}
	
	Shader::Instance()->CompileShaders("Shaders/Main.vert", Shader::ShaderType::VERTEX_SHADER);

	Shader::Instance()->CompileShaders("Shaders/Main.frag", Shader::ShaderType::FRAGMENT_SHADER);


	Shader::Instance()->AttachShaders();

	Shader::Instance()->LinkProgram();

	Quad quad;
	Camera camera;
	Light light;
	camera.Set3DView();

	while (isAppRunning)
	{
		Screen::Instance()->Clear();
		Input::Instance()->Update();

		char keyPressed = Input::Instance()->GetKeyDown();
	
		camera.Update();


		light.Update();
		light.Render();
		light.SendToShader();

		//update/render
		quad.Update();
		quad.Render();

		Screen::Instance()->Render();

		isAppRunning = !Input::Instance()->IsXClicked();
	}





	Shader::Instance()->DetachShaders();
	Shader::Instance()->DestroyShaders();
	Shader::Instance()->DestroyProgram();

	Screen::Instance()->Destroy();

	return 0;
}

/*
*

glGenBuffers: generate buffer
What it does:
Generates one or more buffer object names (IDs).
Analogy:
Like getting a unique ID number for a container — the container doesn't exist yet, but now you have a name (creating a container)

glBindBuffer: select current buffer working with
What it does:
Binds a buffer to a specific target (like GL_ARRAY_BUFFER) so OpenGL knows what you're working with. (Selecting the container to use)
Analogy:
Think of it as selecting the container you're going to fill or modify.


glBufferData: send data to buffer
What it does:
Allocates memory for the currently bound buffer and optionally uploads data. (generates the size of the container and allows you to pass in your data)
Analogy:
You’ve picked your container with glBindBuffer; now you're filling it with stuff (glBufferData).


-------
*** important concepts of opengl VBO, VAO, IBO****


GLM: math helper library


VBO (Vertex Buffer Object): container of data
What it does:
Holds the actual vertex data — positions, normals, colors, texture coords, etc.
Role:
The source of raw geometry.


EBO (Element Buffer Object) or IBO (Index Buffer Object): index which data in the VAO is bound to the vertex in the VBO. basically allows us to determine which vertexs are shared.
What it does:
Holds indices that reference data in the VBO.
Role:
Tells OpenGL which vertices to draw and in what order.
What it stores:
A list of indices that reference vertices in a VBO.
Purpose:
Allows reuse of vertex data to draw shapes more efficiently (using glDrawElements).
Bound to:
GL_ELEMENT_ARRAY_BUFFER while a VAO is bound.
Key concept:
It holds which vertices to draw and in what order.




VAO (Vertex Array Object): container of data for the vertices/attributes of the VBOs
What it does:
Keeps track of:
Which VBO is bound
Which EBO is used
How to interpret the vertex data (attributes like glVertexAttribPointer)
Role:
A snapshot of vertex input state. You only need to bind it before drawing.
What it stores:
References and configurations for VBOs, EBOs, and vertex attribute settings.
Purpose:
Stores the entire "vertex input state" so you can bind one object and draw.
Bound to:
glBindVertexArray(...)
Key concept:
It's like a container of settings that includes a VBO and optionally an EBO.


basically
// 1. VBO — raw vertex data (only the points, no attributes like position, or color) [this is a point, this is a point,this is a point... etc]
// 2. EBO or Index buffers — index order for triangles [this triangle shares a vertex with this triangle, etc]
// 3. VAO — links it all together [[this is the color for this vertex, this is the position for this vertex],[this is the color for this vertex, this is the position for this vertex], etc...]

*/