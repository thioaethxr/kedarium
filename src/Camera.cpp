#include "Kedarium/Camera.hpp"

void kdr::Camera::updateMatrix()
{
  kdr::space::Mat4 view  {1.f};
  kdr::space::Mat4 proj  {1.f};

  view = kdr::space::translate(
    view,
    {
      this->position.x,
      this->position.y,
      this->position.z
    }
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

void kdr::Camera::handleMovement(GLFWwindow* window)
{
  if (!this->isMouseLocked) return;

  if (kdr::keys::isPressed(window, kdr::Key::W))
  {
    this->position -= this->front * this->speed;
  }
  if (kdr::keys::isPressed(window, kdr::Key::S))
  {
    this->position += this->front * this->speed;
  }
  if (kdr::keys::isPressed(window, kdr::Key::A))
  {
    this->position -= kdr::space::cross(this->front, this->up) * this->speed;
  }
  if (kdr::keys::isPressed(window, kdr::Key::D))
  {
    this->position += kdr::space::cross(this->front, this->up) * this->speed;
  }
  if (kdr::keys::isPressed(window, kdr::Key::Space))
  {
    this->position += this->up * this->speed;
  }
  if (kdr::keys::isPressed(window, kdr::Key::LeftShift))
  {
    this->position -= this->up * this->speed;
  }
}

void kdr::Camera::handleMouseMovement(GLFWwindow* window)
{
  glfwSetInputMode(
    window,
    GLFW_CURSOR,
    this->isMouseLocked
      ? GLFW_CURSOR_DISABLED
      : GLFW_CURSOR_NORMAL
  );
}
