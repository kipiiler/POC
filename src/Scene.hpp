#pragma once

// #include "Square.hpp"
#include <vector>

#include "TextureSquare.hpp"

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
        s->Scale({0.2f, 0.2f, 1.0f});
        s->Translate({-1.0f + j * 0.4f + 0.2f, -1.0f + i * 0.4f + 0.2f, 0.0f});
        m_squares.push_back(s);
      }
    }
  }

  void Render() const {
    for (auto &s : m_squares) {
      s->Render();
    }
  }

 public:
  std::vector<std::shared_ptr<TextureSquare>> m_squares;
};
