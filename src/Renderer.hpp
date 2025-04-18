#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <chrono>
#include <format>
#include <functional>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "Scene.hpp"
#include "Square.hpp"

class Renderer {
 public:
  Renderer(const int &w, const int &h);

  // Cleanup code here
  ~Renderer() { CleanUp(); }

  void Run();

  void Render() { m_scene.Render(); }

  void CleanUp() {
    // Cleanup code here
    glfwDestroyWindow(m_window);
    glfwTerminate();
  }

 private: // Callback handler functions
  static void GLAPIENTRY DebugOutputCallback(GLenum source, GLenum type,
                                             unsigned int id, GLenum severity,
                                             GLsizei length,
                                             const char *message,
                                             const void *userParam);

  void HandleDebugMessage(GLenum source, GLenum type, unsigned int id,
                          GLenum severity, GLsizei length, const char *message);

  static void FrameBufferSizeCallback(GLFWwindow *window, int width,
                                      int height);

  void HandleFrameBufferSize(int width, int height);

  static void HandleGLFWError(int error, const char* description);

 private:
  int m_width, m_height;
  GLFWwindow *m_window;

  // Shader *shader;
  std::vector<std::shared_ptr<Square>> squares;

  Scene m_scene;

 private:
  bool m_debug = true;
};  // Renderer
