#include "Square.hpp"

std::shared_ptr<Shader> Square::s_shader = nullptr;
GLint Square::s_modelMatLoc;
GLint Square::s_colorLoc;
GLuint Square::m_vao, Square::m_vbo, Square::m_ebo;

