#pragma once
#include <glad/glad.h>

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

#include "Shader.hpp"

class Square {
 public:
  Square() {
    if (!s_shader) {
      s_shader = std::make_shared<Shader>("./src/shaders/simple.vert",
                                          "./src/shaders/simple.frag");

      float vertices[] = {-1.0f, -1.0f, 1.0f, -1.0f, 1.0f,  1.0f,
                          1.0f,  1.0f,  1.0f, 1.0f,  -1.0f, 1.0f};
      unsigned int indices[] = {0, 1, 2, 0, 2, 3};

      // Generate and bind a Vertex Array Object (VAO)
      glGenVertexArrays(1, &m_vao);
      glBindVertexArray(m_vao);

      // Generate and bind a Vertex Buffer Object (VBO)
      glGenBuffers(1, &m_vbo);
      glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

      glGenBuffers(1, &m_ebo);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                   GL_STATIC_DRAW);

      // Define vertex attributes
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                            (void *)0);
      glEnableVertexAttribArray(0);

      // Unbind the VBO and VAO
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindVertexArray(0);
    }
  }

  ~Square() {}

  [[nodiscard]] GLuint GetVAO() const { return m_vao; }

  void Bind() const {
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
  }

  void Unbind() const {
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  void SetColor(const glm::vec3 &color) { m_color = color; }

  void Rotate(float rad) {
    m_rotate = glm::rotate(m_rotate, -rad, {0.0f, 0.0f, 1.0f});
  }

  void Scale(const glm::vec3 &scale) { m_scale = glm::scale(m_scale, scale); }

  void Translate(const glm::vec3 &trans) {
    m_translate = glm::translate(m_translate, trans);
  }

  [[nodiscard]] glm::mat4 GetModelMatrix() const {
    return m_translate * m_rotate * m_scale;
  }

  void Render() const {
    s_shader->Use();
    Bind();
    s_shader->setUniformMat4f("uModelMat", GetModelMatrix());
    s_shader->setUniformVec3f("uCol", m_color);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    Unbind();
  }

 private:
  glm::mat4 m_rotate = glm::mat4(1.0f);
  glm::mat4 m_scale = glm::mat4(1.0f);
  glm::mat4 m_translate = glm::mat4(1.0f);
  glm::vec3 m_color = glm::vec3(1.0f, 1.0f, 1.0f);

  // Use the same shader for squares
  static std::shared_ptr<Shader> s_shader;

  // Reuse VAO and VBO for different squares
  static GLuint m_vao, m_vbo, m_ebo;
};
