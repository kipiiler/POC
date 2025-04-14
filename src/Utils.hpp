#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

namespace Utils {
inline void printDebugMatrix4(const glm::mat4 &mat) {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      std::cout << mat[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

inline void printDebugMatrix3(const glm::mat3 &mat) {
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      std::cout << mat[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

inline void printDebugMatrix2(const glm::mat2 &mat) {
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      std::cout << mat[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

inline void printDebugVector3(const glm::vec3 &vec) {
  std::cout << vec.x << ", " << vec.y << ", " << vec.z << std::endl;
}

inline void printMapping(const glm::mat4 &mat, float w, float h) {
  glm::vec3 test_pos = {0.0f, 0.0f, 0.0f};
  glm::vec3 test_pos2 = {w, 0.0f, 0.0f};
  glm::vec3 test_pos3 = {0.0f, h, 0.0f};
  glm::vec3 test_pos4 = {w, h, 0.0f};

  glm::vec3 result1 = mat * glm::vec4(test_pos, 1.0f);
  glm::vec3 result2 = mat * glm::vec4(test_pos2, 1.0f);
  glm::vec3 result3 = mat * glm::vec4(test_pos3, 1.0f);
  glm::vec3 result4 = mat * glm::vec4(test_pos4, 1.0f);

  std::cout << "Top Left: ";
  printDebugVector3(result1);

  std::cout << "Top Right: ";
  printDebugVector3(result2);

  std::cout << "Bottom Left: ";
  printDebugVector3(result3);

  std::cout << "Bottom Right: ";
  printDebugVector3(result4);
}
}  // namespace Utils