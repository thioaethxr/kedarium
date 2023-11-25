#include "Kedarium/Core.hpp"

void kdr::core::printEngineInfo()
{
  std::cout << ENGINE_NAME << ' ' << ENGINE_VERSION << '\n';
  std::cout << "Created by " << ENGINE_AUTHOR << '\n';
  std::cout << "Licensed under " << ENGINE_LICENSE << '\n';
}

void kdr::core::printVersionInfo()
{
  std::cout << "OpenGL: " << glGetString(GL_VERSION) << '\n';
  std::cout << "GLEW:   " << glewGetString(GLEW_VERSION) << '\n';
  std::cout << "GLFW:   " << glfwGetVersionString() << '\n';
}
