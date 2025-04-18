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
        std::shared_ptr<TextureSquare> s = std::make_shared<TextureSquare>(texture_path);
        s->Scale({50.f, 50.f, 1.0f});
        s->Translate({i * 100.0f + 50.f, j * 100.0f + 50.f, 0.0f});
        m_squares.push_back(s);
      }
    }

    std::shared_ptr<TextureSquare> s =
        std::make_shared<TextureSquare>("./src/textures/flip.jpg");
    s->Scale({50.0f, 50.0f, 0.0f});
    s->Translate({460.0f, 460.0f, 10.f});

    m_squares.push_back(s);

    Utils::printMapping(m_projectionMat, 800.0f, 600.0f);
  }

  void Render() const {
    TextureSquare::SetViewProjectionMatrices(m_viewMat, m_projectionMat);

    for (auto &s : m_squares) {
      s->Render();
    }
  }

 public:
  std::vector<std::shared_ptr<TextureSquare>> m_squares;
  std::shared_ptr<Camera> m_camera;

 private:
  glm::mat4 m_viewMat = glm::mat4(1.0f);
  glm::mat4 m_projectionMat = glm::mat4(1.0f);
};
