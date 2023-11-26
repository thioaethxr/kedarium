#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "Kedarium/Core.hpp"
#include "Kedarium/File.hpp"
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

  // Shader Sources
  const std::string vertexShaderSource = kdr::file::getContents("resources/Shaders/default.vert");
  const std::string fragmentShaderSource = kdr::file::getContents("resources/Shaders/default.frag");

  const char* vertexShaderSourceC = vertexShaderSource.c_str();
  const char* fragmentShaderSourceC = fragmentShaderSource.c_str();

  // Vertex and Fragment Shaders
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(vertexShader, 1, &vertexShaderSourceC, NULL);
  glShaderSource(fragmentShader, 1, &fragmentShaderSourceC, NULL);

  glCompileShader(vertexShader);
  glCompileShader(fragmentShader);

  // Validating the Shaders
  int success;
  char infoLog[512];

  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cerr << "Failed to compile the vertex shader!\n";
    std::cerr << "Error: " << infoLog << '\n';
  }

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cerr << "Failed to compile the fragment shader!\n";
    std::cerr << "Error: " << infoLog << '\n';
  }

  // Shader Program
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  // VAO, VBO, and EBO
  GLuint VAO;
  kdr::gfx::VBO VBO1 {vertices, sizeof(vertices)};
  kdr::gfx::EBO EBO1 {indices, sizeof(indices)};

  glGenVertexArrays(1, &VAO);

  glBindVertexArray(VAO);
  VBO1.Bind();
  EBO1.Bind();

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);
  VBO1.Unbind();
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // Validating the Shader Program
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cerr << "Failed to link the shader program!\n";
    std::cerr << "Error: " << infoLog << '\n';
  }

  // Deleting the Shaders
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

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
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
    glfwSwapBuffers(window);
  }

  glDeleteVertexArrays(1, &VAO);
  VBO1.Delete();
  EBO1.Delete();
  glDeleteProgram(shaderProgram);
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
