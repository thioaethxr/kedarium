#include "Kedarium/Camera.hpp"

void kdr::Camera::updateMatrix()
{
  kdr::space::Mat4 view  {1.f};
  kdr::space::Mat4 proj  {1.f};

  kdr::space::Vec3 tempFront {0.f};
  tempFront.x = cos(kdr::space::radians(yaw)) * cos(kdr::space::radians(pitch));
  tempFront.y = sin(kdr::space::radians(pitch));
  tempFront.z = sin(kdr::space::radians(yaw)) * cos(kdr::space::radians(pitch));
  this->front = kdr::space::normalize(tempFront);

  view = kdr::space::lookAt(
    this->position,
    this->position + this->front,
    this->up
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

void kdr::Camera::handleMovement(GLFWwindow* window, const float deltaTime)
{
  if (!this->isMouseLocked) return;

  if (kdr::keys::isPressed(window, kdr::Key::W))
  {
    this->position += this->front * this->speed * deltaTime;
  }
  if (kdr::keys::isPressed(window, kdr::Key::S))
  {
    this->position -= this->front * this->speed * deltaTime;
  }
  if (kdr::keys::isPressed(window, kdr::Key::A))
  {
    this->position -= kdr::space::cross(this->front, this->up) * this->speed * deltaTime;
  }
  if (kdr::keys::isPressed(window, kdr::Key::D))
  {
    this->position += kdr::space::cross(this->front, this->up) * this->speed * deltaTime;
  }
  if (kdr::keys::isPressed(window, kdr::Key::Space))
  {
    this->position += this->up * this->speed * deltaTime;
  }
  if (kdr::keys::isPressed(window, kdr::Key::LeftShift))
  {
    this->position -= this->up * this->speed * deltaTime;
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
  if (!this->isMouseLocked) return;

  double mouseX {0.f};
  double mouseY {0.f};
  glfwGetCursorPos(window, &mouseX, &mouseY);

  int windowWidth;
  int windowHeight;
  glfwGetFramebufferSize(window, &windowWidth, &windowHeight);

  float deltaX = (mouseX - (float)windowWidth / 2.f) * this->sensitivity;
  float deltaY = (mouseY - (float)windowHeight / 2.f) * this->sensitivity;

  this->yaw += deltaX;
  this->pitch -= deltaY;

  if (pitch > 89.0f) pitch = 89.0f;
  if (pitch < -89.0f) pitch = -89.0f;

  yaw = std::remainderf(yaw, 360.f);

  glfwSetCursorPos(window, (double)windowWidth / 2.f, (double)windowHeight / 2.f);
}
