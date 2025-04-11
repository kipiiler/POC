#include "TextureSquare.hpp"

std::shared_ptr<Shader> TextureSquare::s_shader = nullptr;
GLint TextureSquare::s_modelMatLoc;
GLint TextureSquare::s_colorLoc;
GLuint TextureSquare::s_vao, TextureSquare::s_vbo, TextureSquare::s_ebo;

