#pragma once

// #include "Square.hpp"
#include <vector>

#include "Camera.hpp"
#include "TextureSquare.hpp"
#include "Utils.hpp"

class Scene {

 public:
  Scene() {}
  ~Scene() {}

  /**
   * Initialize the scene
   *
   * Called after initializing GLFW and OpenGL contexts
   */
  void Init() {
    // Set up the camera
    m_camera = std::make_shared<Camera>();

    m_viewMat = m_camera->GetViewMatrix();
    m_projectionMat = m_camera->GetProjectionMatrix();

    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        std::string texture_path = "./src/textures/wall.jpg";

        if (0 < i and i < 4 and 0 < j and j < 4) {
          texture_path = "./src/textures/red.jpg";
        }
        std::shared_ptr<TextureSquare> s =
            std::make_shared<TextureSquare>(texture_path);
        s->Scale({50.f, 50.f, 1.0f});
        s->Translate({i * 100.0f + 50.f, j * 100.0f + 50.f, 0.0f});
        m_squares.push_back(s);
      }
    }

    m_s =
        std::make_shared<TextureSquare>("./src/textures/flip.jpg");
    m_s->Scale({50.0f, 50.0f, 0.0f});
    m_s->Translate({460.0f, 460.0f, 10.f});

    m_squares.push_back(m_s);

    Utils::printMapping(m_projectionMat, 800.0f, 600.0f);
  }

  void Render() {
    m_viewMat = m_camera->GetViewMatrix();
    m_projectionMat = m_camera->GetProjectionMatrix();

    TextureSquare::SetViewProjectionMatrices(m_viewMat, m_projectionMat);

    for (auto &s : m_squares) {
      s->Render();
    }
  }

  void HandleKey(int key, int action, int mods) {
    if (key == GLFW_KEY_W and (action == GLFW_PRESS or action == GLFW_REPEAT)) {
      glm::vec3 t{0.0f, 1.0f, 0.0f};
      m_camera->SetPosition(m_camera->m_cam_position + t);
      m_s->Translate(t);
    }

    if (key == GLFW_KEY_A and (action == GLFW_PRESS or action == GLFW_REPEAT)) {
      glm::vec3 t{-1.0f, 0.0f, 0.0f};
      m_camera->SetPosition(m_camera->m_cam_position + t);
      m_s->Translate(t);
    }

    if (key == GLFW_KEY_S and (action == GLFW_PRESS or action == GLFW_REPEAT)) {
      glm::vec3 t{0.0f, -1.0f, 0.0f};
      m_camera->SetPosition(m_camera->m_cam_position + t);
      m_s->Translate(t);
    }

    if (key == GLFW_KEY_D and (action == GLFW_PRESS or action == GLFW_REPEAT)) {
      glm::vec3 t{1.0f, 0.0f, 0.0f};
      m_camera->SetPosition(m_camera->m_cam_position + t);
      m_s->Translate(t);
    }
  }

  void HandleFrameBufferSize(int width, int height) {
    m_camera->SetTop(height);
    m_camera->SetRight(width);
  }

 public:
  std::vector<std::shared_ptr<TextureSquare>> m_squares;
  std::shared_ptr<Camera> m_camera;

 private:
  glm::mat4 m_viewMat = glm::mat4(1.0f);
  glm::mat4 m_projectionMat = glm::mat4(1.0f);
  std::shared_ptr<TextureSquare> m_s;
};
