#include "Kedarium/Graphics.hpp"

kdr::gfx::VBO::VBO(GLfloat vertices[], GLsizeiptr size)
{
  glGenBuffers(1, &this->ID);
  this->Bind();
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
  this->Unbind();
}
