#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <chrono>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "Scene.hpp"
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

    m_scene.Init();
  };

  ~Renderer() {
    // Cleanup code here
    cleanup();
  }

  void run() {
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

      if (dt >= 160) {  // 6 FPS
        // Render here
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Set clear color to black
        glClear(GL_COLOR_BUFFER_BIT |
                GL_DEPTH_BUFFER_BIT);  // Clear the color buffer

        Render();

        glfwSwapBuffers(window);  // Swap front and back buffers

        prev = now;
      }

      glfwPollEvents();  // Poll for and process events
    }
  }

  void Render() {
    // Render the triangle
    // renderTriangle();

    m_scene.Render();
  }

  void cleanup() {
    // Cleanup code here
    glfwDestroyWindow(window);
    glfwTerminate();
  }

 private:
  int width, height;
  GLFWwindow *window;
  GLuint tri_VAO, tri_VBO;

  // Shader *shader;
  std::vector<std::shared_ptr<Square>> squares;

  Scene m_scene;
};  // Renderer
