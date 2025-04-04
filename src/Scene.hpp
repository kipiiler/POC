#pragma once

#include "Square.hpp"
#include <vector>

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
        std::shared_ptr<Square> s = std::make_shared<Square>();
        s->Scale({0.2f, 0.2f, 1.0f});
        s->Translate({-1.0f + j * 0.4f + 0.2f, -1.0f + i * 0.4f + 0.2f, 0.0f});
        s->SetColor({0.0f + i * 0.2f, 0.3f, 1.0f - j * 0.2f});
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
  std::vector<std::shared_ptr<Square>> m_squares;
};
