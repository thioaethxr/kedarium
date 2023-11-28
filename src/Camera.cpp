#include "Kedarium/Camera.hpp"

void kdr::Camera::updateMatrix()
{
  kdr::space::Mat4 view  {1.f};
  kdr::space::Mat4 proj  {1.f};

  view = kdr::space::translate(
    view,
    {0.f, 0.f, -3.f}
  );
  proj = kdr::space::perspective(
    this->fov,
    this->aspect,
    this->near,
    this->far
  );

  this->matrix = proj * view;
}

void kdr::Camera::applyMatrix(const GLuint shaderID, const std::string& uniformName)
{
  GLuint cameraMatrixLoc = glGetUniformLocation(shaderID, uniformName.c_str());
  glUniformMatrix4fv(cameraMatrixLoc, 1, GL_FALSE, kdr::space::valuePointer(this->matrix));
}
