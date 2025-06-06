#include "Renderer.hpp"

#include <GLFW/glfw3.h>

#include <memory>

Renderer::Renderer(const int &w, const int &h) : m_width(w), m_height(h) {
  // Initialize OpenGL context and other setup here
  // Initialize GLFW
  if (!glfwInit()) {
    std::cout << "[Error]: Failed to initialize GLFW" << std::endl;
    throw std::runtime_error("GLFW initialization failed");
  }

  if (m_debug) {
    std::cout << "[Info]: Running in debug mode" << std::endl;
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
  }

  // Create a windowed mode window and its OpenGL context
  m_window = glfwCreateWindow(m_width, m_height, "OpenGL Window", NULL, NULL);
  if (!m_window) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    throw std::runtime_error("GLFW window creation failed");
  }

  // Print out device info with GLFW
  if (m_debug) {
    GLFWmonitor *monitor = glfwGetWindowMonitor(m_window);

    if (monitor) {
      const GLFWvidmode *mode = glfwGetVideoMode(monitor);

      std::cout << "[Info]: "
                << std::format("Monitor (%d, %d) %dHz (%d, %d, %d)RBG",
                               mode->width, mode->height, mode->refreshRate,
                               mode->redBits, mode->greenBits, mode->blueBits)
                << std::endl;
    }
  }

  // Make the window's context current
  glfwMakeContextCurrent(m_window);

  // Match glfw refresh rate with monitor refresh rate
  glfwSwapInterval(1);

  // To get back this in GLFW callbacks
  glfwSetWindowUserPointer(m_window, this);

  // Window size callback
  glfwSetFramebufferSizeCallback(m_window, &Renderer::FrameBufferSizeCallback);

  m_prevKeyCallback = glfwSetKeyCallback(m_window, &Renderer::KeyCallback);

  // Initialize GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "[Error]: Failed to initialize GLAD" << std::endl;
    throw std::runtime_error("GLAD initialization failed");
  }

  if (m_debug) {
    // Print the OpenGL version
    int major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);
    std::cout << "[Info]: OpenGL version " << major << "." << minor
              << std::endl;

    int flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (!(flags & GL_CONTEXT_FLAG_DEBUG_BIT)) {
      std::cout << "[Warning]: Failed to initialize OpenGL debug context"
                << std::endl;
    } else {
      std::cout << "[Info]: Enabling OpenGL Debug output" << std::endl;
      glEnable(GL_DEBUG_OUTPUT);
      glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
      glDebugMessageCallback(Renderer::DebugOutputCallback, this);
      glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0,
                            nullptr, GL_TRUE);
    }
  }

  m_scene.Init();

  using namespace std::placeholders;
  AddHandler(std::bind(&Scene::HandleKey, &m_scene, _1, _2, _3));
  AddHandler([&](int key, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE and action == GLFW_PRESS) {
      glfwSetWindowShouldClose(m_window, true);
    }
  });
}

void Renderer::Run() {
  std::chrono::steady_clock::time_point prev = std::chrono::steady_clock::now();

  // Main loop
  while (!glfwWindowShouldClose(m_window)) {
    std::chrono::steady_clock::time_point now =
        std::chrono::steady_clock::now();

    // Elapsed time since last frame in milisecond
    long long dt =
        std::chrono::duration_cast<std::chrono::milliseconds>(now - prev)
            .count();

    if (dt >= 160) {  // 6 FPS
      // Render here
      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Set clear color to black
      glClear(GL_COLOR_BUFFER_BIT);          // Clear the color buffer

      Render();

      glfwSwapBuffers(m_window);  // Swap front and back buffers

      prev = now;
    }

    glfwPollEvents();  // Poll for and process events
  }
}

void Renderer::HandleDebugMessage(GLenum source, GLenum type, unsigned int id,
                                  GLenum severity, GLsizei length,
                                  const char *message) {
  // ignore non-significant error/warning codes
  if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

  std::cout << "";

  switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH:
      std::cout << "[Error]";
      break;
    case GL_DEBUG_SEVERITY_MEDIUM:
      std::cout << "[Error]";
      break;
    case GL_DEBUG_SEVERITY_LOW:
      std::cout << "[Warning]";
      break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
      std::cout << "[Info]";
      break;
  }

  std::cout << ": OpenGL (" << id << "): " << message << std::endl;

  switch (source) {
    case GL_DEBUG_SOURCE_API:
      std::cout << "\tSource: API";
      break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
      std::cout << "\tSource: Window System";
      break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
      std::cout << "\tSource: Shader Compiler";
      break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:
      std::cout << "\tSource: Third Party";
      break;
    case GL_DEBUG_SOURCE_APPLICATION:
      std::cout << "\tSource: Application";
      break;
    case GL_DEBUG_SOURCE_OTHER:
      std::cout << "\tSource: Other";
      break;
  }
  std::cout << std::endl;

  switch (type) {
    case GL_DEBUG_TYPE_ERROR:
      std::cout << "\tType: Error";
      break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
      std::cout << "\tType: Deprecated Behaviour";
      break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
      std::cout << "\tType: Undefined Behaviour";
      break;
    case GL_DEBUG_TYPE_PORTABILITY:
      std::cout << "\tType: Portability";
      break;
    case GL_DEBUG_TYPE_PERFORMANCE:
      std::cout << "\tType: Performance";
      break;
    case GL_DEBUG_TYPE_MARKER:
      std::cout << "\tType: Marker";
      break;
    case GL_DEBUG_TYPE_PUSH_GROUP:
      std::cout << "\tType: Push Group";
      break;
    case GL_DEBUG_TYPE_POP_GROUP:
      std::cout << "\tType: Pop Group";
      break;
    case GL_DEBUG_TYPE_OTHER:
      std::cout << "\tType: Other";
      break;
  }

  std::cout << std::endl;
}

void Renderer::DebugOutputCallback(GLenum source, GLenum type, unsigned int id,
                                   GLenum severity, GLsizei length,
                                   const char *message, const void *userParam) {
  Renderer *_this = reinterpret_cast<Renderer *>(const_cast<void *>(userParam));
  if (_this) {
    _this->HandleDebugMessage(source, type, id, severity, length, message);
  } else {
    std::cout << "[Warning]: Unknown userParam passed in debug callback"
              << std::endl;
  }
}

void Renderer::FrameBufferSizeCallback(GLFWwindow *window, int width,
                                       int height) {
  Renderer *_this = static_cast<Renderer *>(glfwGetWindowUserPointer(window));

  if (_this) {
    _this->HandleFrameBufferSize(width, height);
  }
}

void Renderer::HandleFrameBufferSize(int width, int height) {
  m_width = width;
  m_height = height;

  std::cout << "[Info]: Window size: (" << width << ", " << height << ")"
            << std::endl;

  m_scene.HandleFrameBufferSize(width, height);

  // Reset the opengl viewport with the new dimension
  glViewport(0, 0, width, height);
}

void Renderer::HandleGLFWError(int error, const char *description) {
  std::cout << "[Error]: GLFW (" << error << "): " << description << std::endl;
}

void Renderer::KeyCallback(GLFWwindow *window, int key, int scancode, int action,
                        int mods) {
  Renderer *_this = static_cast<Renderer *>(glfwGetWindowUserPointer(window));
  if (_this) {
    _this->HandleKey(key, scancode, action, mods);
  }
}

void Renderer::HandleKey(int key, int scancode, int action, int mods) {
  if (m_prevKeyCallback != nullptr)
    m_prevKeyCallback(m_window, key, scancode, action, mods);

  for (auto &handler : m_handlers) {
    handler(key, action, mods);
  }
}
