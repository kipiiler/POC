#pragma once
#include <glad/glad.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>

class Square {
public:
  Square() {
    float vertices[] = {
      -1.0f, -1.0f, 1.0f,
      -1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, 1.0f,
      1.0f, -1.0f, 1.0f};
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

  ~Square() {}

  [[nodiscard]] GLuint GetVAO() const { return m_vao; }

  void Bind() {
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
  }

  void Unbind() {
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

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

private:
  GLuint m_vao, m_vbo, m_ebo;
  glm::mat4 m_rotate = glm::mat4(1.0f);
  glm::mat4 m_scale = glm::mat4(1.0f);
  glm::mat4 m_translate = glm::mat4(1.0f);
};
