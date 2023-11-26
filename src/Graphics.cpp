#include "Kedarium/Graphics.hpp"

kdr::gfx::VBO::VBO(GLfloat vertices[], GLsizeiptr size)
{
  glGenBuffers(1, &this->ID);
  this->Bind();
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
  this->Unbind();
}

kdr::gfx::EBO::EBO(GLuint indices[], GLsizeiptr size)
{
  glGenBuffers(1, &this->ID);
  this->Bind();
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
  this->Unbind();
}

void kdr::gfx::VAO::LinkAttribute(kdr::gfx::VBO& VBO, GLuint layout, GLuint size, GLenum type, GLsizeiptr stride, const void* offset)
{
  VBO.Bind();
  glVertexAttribPointer(layout, size, type, GL_FALSE, stride, (void*)offset);
  glEnableVertexAttribArray(layout);
  VBO.Unbind();
}
