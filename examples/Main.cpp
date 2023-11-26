#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "Kedarium/Core.hpp"
#include "Kedarium/Keys.hpp"
#include "Kedarium/Graphics.hpp"

// Constants
constexpr unsigned int WINDOW_WIDTH  {800};
constexpr unsigned int WINDOW_HEIGHT {600};
const     std::string  WINDOW_TITLE  {"GLFW"};

// Vertices and Indices
GLfloat vertices[] = {
  -0.5f, -0.5f, 0.f, 1.f, 1.f, 1.f,
   0.5f, -0.5f, 0.f, 1.f, 1.f, 1.f,
  -0.5f,  0.5f, 0.f, 1.f, 1.f, 1.f,
   0.5f,  0.5f, 0.f, 1.f, 1.f, 1.f,
};
GLuint indices[] = {
  0, 1, 3,
  0, 3, 2,
};

int main()
{
  // Initializing GLFW
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Creating a GLFW Window
  GLFWwindow* window = glfwCreateWindow(
    WINDOW_WIDTH,
    WINDOW_HEIGHT,
    WINDOW_TITLE.c_str(),
    NULL,
    NULL
  );
  if (window == NULL)
  {
    std::cerr << "Failed to create a GLFW window!\n";
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glPointSize(5.f);

  // Initializing GLEW
  GLenum glewErr = glewInit();
  if (GLEW_OK != glewErr)
  {
    std::cerr << "Failed to initialize GLEW!\n";
    std::cerr << "Error: " << glewGetErrorString(glewErr) << '\n';
    glfwTerminate();
    return -1;
  }

  // Clear Color
  GLclampf red   {0.f};
  GLclampf green {0.f};
  GLclampf blue  {0.f};
  GLclampf alpha {0.f};
  glClearColor(red, green, blue, alpha);

  // Shader Program
  kdr::gfx::Shader defaultShader {
    "resources/Shaders/default.vert",
    "resources/Shaders/default.frag"
  };

  // VAO, VBO, and EBO
  kdr::gfx::VAO VAO1;
  kdr::gfx::VBO VBO1 {vertices, sizeof(vertices)};
  kdr::gfx::EBO EBO1 {indices, sizeof(indices)};

  VAO1.Bind();
  VBO1.Bind();
  EBO1.Bind();

  VAO1.LinkAttribute(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)0);
  VAO1.LinkAttribute(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

  VAO1.Unbind();
  VBO1.Unbind();
  EBO1.Unbind();

  // Engine and Version info
  kdr::core::printEngineInfo();
  std::cout << '\n';
  kdr::core::printVersionInfo();

  // Main Loop
  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();

    if (kdr::Keys::isPressed(window, kdr::Key::C))
    {
      kdr::gfx::usePointMode();
    }
    else if (kdr::Keys::isPressed(window, kdr::Key::V))
    {
      kdr::gfx::useLineMode();
    }
    else if (kdr::Keys::isPressed(window, kdr::Key::B))
    {
      kdr::gfx::useFillMode();
    }

    glClear(GL_COLOR_BUFFER_BIT);
    defaultShader.Use();
    VAO1.Bind();
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
    glfwSwapBuffers(window);
  }

  VAO1.Delete();
  VBO1.Delete();
  EBO1.Delete();
  defaultShader.Delete();
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
