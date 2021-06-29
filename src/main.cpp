#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "shader.h"

int main()
{
	// GLFW initialization and specifiying OpenGL window context version 
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Creates the actual window, throws an error in case of failure
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Error! Could not create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))		// This function requires a valid OpenGL context 
	{
		std::cout << "Error! Could not load glad" << std::endl;
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 800, 600);		// Defines the size of the OpenGL rendering viewport, this is independent of window size

	// OpenGL version info and GPU currently in use
	std::cout << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OPENGL VERSION: " << glGetString(GL_VERSION) << std::endl;

	//-------------------------------------------------
	// Shader compile functions
	//-------------------------------------------------

    Shader ShaderLoader("vertex.glsl", "fragment.glsl");

	//-------------------------------------------------
	// Vertex data
	//-------------------------------------------------

    float vertices[] = {
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
	};

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

	//-------------------------------------------------
	// OpenGL buffers
	//-------------------------------------------------

    unsigned int VBO;
    unsigned int VAO;
    unsigned int IBO;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO); 	// OpenGL core profile requires a VAO to be bound

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);		// Copies the data from system RAM to GPU RAM

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Defines the data layout of the VBO and stores it in the VAO
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);	// we can unbind the VBO because it has be registered to the VAO using glVertexAttribPointer

	//-------------------------------------------------
	// Main render loop
	//-------------------------------------------------

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.5f, 0.8f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

        ShaderLoader.use();
		glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Resource de-allocation for a cleaner exit. This is optionnal as the OS should handle this automatically
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();

	return 0;
}
