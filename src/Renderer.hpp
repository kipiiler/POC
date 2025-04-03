#pragma once
#include <chrono>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "Shader.hpp"
#include "Square.hpp"

class Renderer {
public:
  Renderer(const int &w, const int &h) : width(w), height(h) {
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

    { // Create a triangle
      // Define vertices of a triangle
      float vertices[] = {
          0.0f,  0.5f,  0.0f, // Top vertex
          -0.5f, -0.5f, 0.0f, // Bottom-left vertex
          0.5f,  -0.5f, 0.0f  // Bottom-right vertex
      };

      // Generate and bind a Vertex Array Object (VAO)
      glGenVertexArrays(1, &tri_VAO);
      glBindVertexArray(tri_VAO);

      // Generate and bind a Vertex Buffer Object (VBO)
      glGenBuffers(1, &tri_VBO);
      glBindBuffer(GL_ARRAY_BUFFER, tri_VBO);
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

      // Define vertex attributes
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                            (void *)0);
      glEnableVertexAttribArray(0);

      // Unbind the VBO and VAO
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindVertexArray(0);
    }
  };

  ~Renderer() {
    // Cleanup code here
    cleanup();
  }

  void run() {
    Shader shader("./src/shaders/simple.vert.glsl",
                  "./src/shaders/simple.frag.glsl");

    glm::mat4 rot(1.0f);
    GLint modelMatLoc = glGetUniformLocation(shader.shaderProgram, "uModelMat");
    GLint colLoc = glGetUniformLocation(shader.shaderProgram, "uCol");
    Square square;
    square.Scale({0.25f, 0.25f, 1.0f});
    square.Translate({0.5f, 0.5f, 0.0f});

    std::vector<std::shared_ptr<Square>> squares;

    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        std::shared_ptr<Square> s = std::make_shared<Square>();
        s->Scale({0.1f, 0.1f, 1.0f});
        s->Translate({-1.0f + j * 0.4f + 0.2f, -1.0f + i * 0.4f + 0.2f, 0.0f});
        squares.push_back(s);
      }
    }

    double dt;
    std::chrono::steady_clock::time_point prev =
        std::chrono::steady_clock::now();

    // Main loop
    while (!glfwWindowShouldClose(window)) {
      std::chrono::steady_clock::time_point now =
          std::chrono::steady_clock::now();

      // Elapsed time since last frame in milisecond
      long long dt =
          std::chrono::duration_cast<std::chrono::milliseconds>(now - prev)
              .count();

      if (dt >= 160) { // 6 FPS
        shader.use();  // Use the shader program

        // Update model matrix for triangle
        rot = glm::rotate(rot, glm::pi<float>() / 60, {0.0, 0.0, 1.0});
        square.Rotate(glm::pi<float>() / 30);

        // Render here
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set clear color to black
        glClear(GL_COLOR_BUFFER_BIT |
                GL_DEPTH_BUFFER_BIT); // Clear the color buffer

        // Model matrix for triangle
        glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(rot));
        glUniform3f(colLoc, 0.7f, 0.1f, 0.3f);
        render();

        // Render the square
        square.Bind();
        glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE,
                           glm::value_ptr(square.GetModelMatrix()));
        glUniform3f(colLoc, 0.1f, 0.2f, 0.8f);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        square.Unbind();

        for (auto &s : squares) {
          s->Bind();
          glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE,
                             glm::value_ptr(s->GetModelMatrix()));
          glUniform3f(colLoc, 0.5f, 0.2f, 0.4f);
          glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
          s->Unbind();
        }

        glfwSwapBuffers(window); // Swap front and back buffers

        prev = now;
      }

      glfwPollEvents(); // Poll for and process events
    }
  }

  void render() {
    // Render the triangle
    renderTriangle();
  }

  void cleanup() {
    // Cleanup triangle
    glDeleteBuffers(1, &tri_VBO);
    glDeleteVertexArrays(1, &tri_VAO);

    // Cleanup code here
    glfwDestroyWindow(window);
    glfwTerminate();
  }

  void renderTriangle() {
    // Render the triangle
    glBindVertexArray(tri_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
  }

private:
  int width, height;
  GLFWwindow *window;
  GLuint tri_VAO, tri_VBO;
}; // Renderer
