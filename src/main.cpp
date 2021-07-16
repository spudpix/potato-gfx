#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "shader.h"
#include "stb_image.h"

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
        std::cerr << "Error! Could not create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))		// This function requires a valid OpenGL context 
    {
        std::cerr << "Error! Could not load glad" << std::endl;
        glfwTerminate();
        return -1;
    }


    // Misc GL functions
    glViewport(0, 0, 800, 600);		// Defines the size of the OpenGL rendering viewport, this is independent of window size
    glEnable(GL_DEPTH_TEST);

    // OpenGL version info and GPU currently in use
    std::cout << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OPENGL VERSION: " << glGetString(GL_VERSION) << std::endl;

    //-------------------------------------------------
    // Shader compile functions
    //-------------------------------------------------

    Shader ShaderLoader("vertex.glsl", "fragment.glsl");

    //-------------------------------------------------
    // Data
    //-------------------------------------------------

    float vertices[] = {
          -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
           0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
           0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
           0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
          -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
          -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

          -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
           0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
           0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
           0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
          -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
          -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

          -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
          -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
          -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
          -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
          -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
          -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

           0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
           0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
           0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
           0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
           0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
           0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

          -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
           0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
           0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
           0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
          -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
          -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

          -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
           0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
           0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
           0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
          -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
          -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
      };

/*
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };
*/

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    //-------------------------------------------------
    // OpenGL buffers
    //-------------------------------------------------

    unsigned int VBO;
    unsigned int VAO;
    //unsigned int IBO;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO); 	// OpenGL core profile requires a VAO to be bound

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);		// Copies the data from system RAM to GPU RAM

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

/*
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);	// Defines the data layout of the VBO and stores it in the VAO
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
*/
    glBindBuffer(GL_ARRAY_BUFFER, 0);	// we can unbind the VBO because it has be registered to the VAO using glVertexAttribPointer

    //-------------------------------------------------
    // Texture loading
    //-------------------------------------------------

    int width;
    int height;
    int nrChannels;

    unsigned int texture1;
    unsigned int texture2;

    unsigned char* image;

    stbi_set_flip_vertically_on_load(true);
 
    //-------------
    // Texture 1
    //-------------

    image = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
         
    // The usual glGen and glBind
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // Texture wrapping methods
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Texture filtering method
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Output the data to be processed by shaders and error checking
    if(image)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "Texture loading failed" << std::endl;
    }
    // Cleanup
    stbi_image_free(image);

    //-------------
    // Texture 2
    //-------------

    image = stbi_load("PixelPotato512.png", &width, &height, &nrChannels, 0);

    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (image)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "Texture loading failed" << std::endl;
    }
    
    stbi_image_free(image);

    //-------------------------------------------------
    // Uniforms
    //-------------------------------------------------

    ShaderLoader.use();


    // Passing the texture sampler location to OpenGL
    glUniform1i(glGetUniformLocation(ShaderLoader.ID, "texture1"), 0);
    glUniform1i(glGetUniformLocation(ShaderLoader.ID, "texture2"), 1);


    //-------------------------------------------------
    // Main render loop
    //-------------------------------------------------

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.5f, 0.8f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        ShaderLoader.use();

        // Transforms
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        projection = glm::perspective(glm::radians(45.0f), (float)800/(float)600, 0.1f, 100.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        // Sending matrix data to shaders
        ShaderLoader.setMat4("projection", projection);
        ShaderLoader.setMat4("view", view);

        glBindVertexArray(VAO);

        for(unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.f * i;
            if(i % 4 == 0)
                angle = glfwGetTime() * 25.0f;

            if(i % 3 == 0)
                angle = glfwGetTime() * -25.0f;

            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            ShaderLoader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Resource de-allocation for a cleaner exit. This is optionnal as the OS should handle this automatically
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    //glDeleteBuffers(1, &IBO);

    glfwTerminate();

    return 0;
}
