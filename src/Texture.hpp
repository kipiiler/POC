#pragma once
#include <string>
#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>

class Texture {
public:
    Texture(const std::string& imagePath) {
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        // Set texture wrapping and filtering options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Load image
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true); // Flip image vertically
        unsigned char* data = stbi_load(imagePath.c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cerr << "Failed to load texture: " << imagePath << std::endl;
        }
        stbi_image_free(data);
    }

    ~Texture() {
        glDeleteTextures(1, &textureID);
    }

    void Bind() const {
        glBindTexture(GL_TEXTURE_2D, textureID);
    }

    void Unbind() const {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

private:
    GLuint textureID;
};