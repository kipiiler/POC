#pragma once
#include <glad/glad.h>

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <string>

#include "Shader.hpp"
#include "Texture.hpp"
#include "Utils.hpp"

class TextureSquare {
 public:
  TextureSquare()
      : TextureSquare("./src/textures/wall.jpg") {
        };  // Default constructor loads a white texture

  TextureSquare(const std::string &texture_path) {
    // Load the texture
    m_texture = Texture::Load(texture_path);

    if (!s_shader) {
      s_shader = std::make_shared<Shader>("./src/shaders/default.vert",
                                          "./src/shaders/default.frag");

      float vertices[] = {
          -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,  // bottom-left
          -1.0f, 1.0f,  0.0f, 0.0f, 1.0f,  // top-left
          1.0f,  1.0f,  0.0f, 1.0f, 1.0f,  // top-right
          1.0f,  -1.0f, 0.0f, 1.0f, 0.0f   // bottom-right
      };  // Vertex positions and texture coordinates
      unsigned int indices[] = {0, 1, 2, 0, 2, 3};

      // Generate and bind a Vertex Array Object (VAO)
      glGenVertexArrays(1, &s_vao);
      glBindVertexArray(s_vao);

      // Generate and bind a Vertex Buffer Object (VBO)
      glGenBuffers(1, &s_vbo);
      glBindBuffer(GL_ARRAY_BUFFER, s_vbo);
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

      glGenBuffers(1, &s_ebo);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_ebo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                   GL_STATIC_DRAW);

      // Define vertex attributes
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                            (void *)0);  // Position attribute
      glEnableVertexAttribArray(0);

      glVertexAttribPointer(
          1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
          (void *)(3 * sizeof(float)));  // Texture coord attribute
      glEnableVertexAttribArray(1);

      // Unbind the VBO and VAO
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindVertexArray(0);
    };
  };

  ~TextureSquare() {
    if (m_texture) {
      m_texture->Unbind();
    }
  };

  void LoadTexture(const std::string &texture_path) {
    m_texture = Texture::Load(texture_path);
  };

  void Bind() const {
    glBindVertexArray(s_vao);
    glBindBuffer(GL_ARRAY_BUFFER, s_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_ebo);
  };

  void Unbind() const {
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  };

  void Rotate(float rad) {
    m_rotate = glm::rotate(m_rotate, -rad, {0.0f, 0.0f, 1.0f});
  };

  void Scale(const glm::vec3 &scale) { m_scale = glm::scale(m_scale, scale); };

  void Translate(const glm::vec3 &trans) {
    m_translate = glm::translate(m_translate, trans);
  };

  [[nodiscard]] glm::mat4 GetModelMatrix() const {
    return m_translate * m_rotate * m_scale;
  };

  void Render(glm::mat4 viewMat, glm::mat4 prjMat) const {
    s_shader->Use();
    m_texture->Bind();
    s_shader->setUniformMat4f("uModelMat", GetModelMatrix());
    s_shader->setUniformMat4f("uViewMat", viewMat);
    s_shader->setUniformMat4f("uProjMat", prjMat);

    glBindVertexArray(s_vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  };

 private:
  glm::mat4 m_rotate = glm::mat4(1.0f);
  glm::mat4 m_scale = glm::mat4(1.0f);
  glm::mat4 m_translate = glm::mat4(1.0f);

  std::shared_ptr<Texture> m_texture = nullptr;

  // Use the same shader for squares
  static std::shared_ptr<Shader> s_shader;

  // Reuse VAO and VBO for different squares
  static GLuint s_vao, s_vbo, s_ebo;
  static GLint s_modelMatLoc;
  static GLint s_colorLoc;
};