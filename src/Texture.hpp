#pragma once
#include <glad/glad.h>
#include <stb_image.h>

#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>

class Texture {
 public:
  // Load or fetch a cached texture
  static std::shared_ptr<Texture> Load(const std::string& imagePath) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = textureCache_.find(imagePath);
    if (it != textureCache_.end()) {
      return it->second;
    }

    auto tex = std::shared_ptr<Texture>(new Texture(imagePath));
    textureCache_[imagePath] = tex;
    return tex;
  }

  ~Texture() { glDeleteTextures(1, &textureID); }

  void Bind() const { glBindTexture(GL_TEXTURE_2D, textureID); }

  void Unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }

 private:
  GLuint textureID;

  explicit Texture(const std::string& imagePath) {
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture wrapping and filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load image
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);  // Flip image vertically
    unsigned char* data =
        stbi_load(imagePath.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
      GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
      glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                   GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
    } else {
      std::cerr << "Failed to load texture: " << imagePath << std::endl;
    }
    stbi_image_free(data);
  }

  // Cache for loaded textures
  static inline std::unordered_map<std::string, std::shared_ptr<Texture>>
      textureCache_;
  static inline std::mutex mutex_;
};