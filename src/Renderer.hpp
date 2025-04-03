#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <iostream>

#include "Shader.hpp"


class Renderer {
private:
    int width, height;
    GLFWwindow* window;

    public:
    
    Renderer(const int& w, const int& h) : width(w), height(h) {
        // Initialize OpenGL context and other setup here
        // Initialize GLFW
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            throw std::runtime_error("GLFW initialization failed");
        }

        // Create a windowed mode window and its OpenGL context
        window = glfwCreateWindow(width, height, "OpenGL Window", NULL, NULL);
        if (!window) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            throw std::runtime_error("GLFW window creation failed");
        }

        // Make the window's context current
        glfwMakeContextCurrent(window);

        // Initialize GLAD
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            throw std::runtime_error("GLAD initialization failed");
        }
    };


    ~Renderer() {
        // Cleanup code here
        cleanup();
    }


    void run() {

        Shader shader("C:/Users/nguye/Desktop/Random/POC/src/shaders/simple.vs", "C:/Users/nguye/Desktop/Random/POC/src/shaders/simple.fs");

        
        // Main loop
        while (!glfwWindowShouldClose(window)) {
            // Render here
            
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set clear color to black
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color buffer
            
            shader.use(); // Use the shader program
            render();

            glfwSwapBuffers(window); // Swap front and back buffers
            glfwPollEvents(); // Poll for and process events
        }
    }

    void render() {
        // Render the triangle
        renderTriangle();
    }


    void cleanup() {
        // Cleanup code here
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void renderTriangle() {
        // Define vertices of a triangle
        float vertices[] = {
            0.0f,  0.5f, 0.0f,  // Top vertex
           -0.5f, -0.5f, 0.0f,  // Bottom-left vertex
            0.5f, -0.5f, 0.0f   // Bottom-right vertex
        };

        // Generate and bind a Vertex Array Object (VAO)
        GLuint VAO;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        // Generate and bind a Vertex Buffer Object (VBO)
        GLuint VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Define vertex attributes
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Unbind the VBO and VAO
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        // Render the triangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Cleanup
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);
    }

}; // Renderer