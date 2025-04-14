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
        // std::shared_ptr<Square> s = std::make_shared<Square>();
        // s->Scale({0.2f, 0.2f, 1.0f});
        // s->Translate({-1.0f + j * 0.4f + 0.2f, -1.0f + i * 0.4f + 0.2f,
        // 0.0f}); s->SetColor({0.0f + i * 0.2f, 0.3f, 1.0f - j * 0.2f});
        // m_squares.push_back(s);
        std::string texture_path = "./src/textures/wall.jpg";
        if ((i * 5 + j) % 2 == 0) {
          texture_path = "./src/textures/red.jpg";
        }
        std::shared_ptr<TextureSquare> s = std::make_shared<TextureSquare>();
        s->Scale({50.2f, 50.2f, 0.1f});
        s->Translate({i * 110.0f, j * 110.0f, 0.0f});
        // s->Translate({-1.0f + j * 0.4f + 0.2f, -1.0f + i * 0.4f + 0.2f,
        // 0.0f});
        m_squares.push_back(s);
      }
    }

    std::shared_ptr<TextureSquare> s =
        std::make_shared<TextureSquare>("./src/textures/red.jpg");
    s->Scale({50.2f, 50.2f, 0.1f});
    s->Translate({460.0f, 460.0f, -10.0f});

    m_squares.push_back(s);

    Utils::printMapping(m_projectionMat, 800.0f, 600.0f);
  }

  void Render() const {
    for (auto &s : m_squares) {
      s->Render(m_viewMat, m_projectionMat);
    }
  }

 public:
  std::vector<std::shared_ptr<TextureSquare>> m_squares;
  std::shared_ptr<Camera> m_camera;

 private:
  glm::mat4 m_viewMat = glm::mat4(1.0f);
  glm::mat4 m_projectionMat = glm::mat4(1.0f);
};
