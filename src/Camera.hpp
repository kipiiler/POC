#pragma once
#include <glad/glad.h>

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
 public:
  glm::vec3 m_cam_position;
  glm::vec3 m_cam_front;
  glm::vec3 m_cam_up;

  float m_left;
  float m_right;
  float m_top;
  float m_bottom;

  float m_near;
  float m_far;

  Camera()
      : m_cam_position(0.0f, 0.0f, 100.0f),
        m_cam_front(0.0f, 0.0f, -1.0f),
        m_cam_up(0.0f, 1.0f, 0.0f),
        m_left(0.0f),
        m_right(800.0f),
        m_bottom(600.0f),
        m_top(0.0f),
        m_near(0.0f),
        m_far(1000.0f) {};

  ~Camera() {
    // Cleanup code here if needed
  };

  void SetPosition(const glm::vec3& position) { m_cam_position = position; };

  void SetFront(const glm::vec3& front) { m_cam_front = front; };

  void SetUp(const glm::vec3& up) { m_cam_up = up; };

  void SetLeft(float left) { m_left = left; };

  void SetRight(float right) { m_right = right; };

  void SetTop(float top) { m_top = top; };

  void SetBottom(float bottom) { m_bottom = bottom; };

  void SetNear(float near) { m_near = near; };

  void SetFar(float far) { m_far = far; };

  void SetProjection(float left, float right, float top, float bottom,
                     float near, float far) {
    m_left = left;
    m_right = right;
    m_top = top;
    m_bottom = bottom;
    m_near = near;
    m_far = far;
  };

  [[nodiscard]] glm::mat4 GetViewMatrix() const {
    return glm::lookAt(m_cam_position, m_cam_position + m_cam_front, m_cam_up);
  };

  [[nodiscard]] glm::mat4 GetProjectionMatrix() const {
    return glm::ortho(m_left, m_right, m_bottom, m_top, m_near, m_far);
  };
};  // camera class
