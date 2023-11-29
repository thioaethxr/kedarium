#include "Kedarium/Window.hpp"

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
  kdr::Window* windowInstance = (kdr::Window*)glfwGetWindowUserPointer(window);
  glViewport(0, 0, width, height);

  if (windowInstance->getBoundCamera() == NULL) return;

  const float aspect = (float)width / height;
  windowInstance->getBoundCamera()->setAspect(aspect);
}

kdr::Window::~Window()
{
  glfwDestroyWindow(this->glfwWindow);
}

void kdr::Window::loop()
{
  while (!glfwWindowShouldClose(this->glfwWindow))
  {
    this->_update();
    this->_render();
  }
}

void kdr::Window::close()
{
  glfwSetWindowShouldClose(this->glfwWindow, GLFW_TRUE);
}

bool kdr::Window::_initializeGlfw()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  return true;
}

bool kdr::Window::_initializeWindow()
{
  this->glfwWindow = glfwCreateWindow(
    this->width,
    this->height,
    this->title.c_str(),
    NULL,
    NULL
  );
  if (this->glfwWindow == NULL)
  {
    std::cerr << "Failed to create a GLFW window!\n";
    return false;
  }
  glfwMakeContextCurrent(this->glfwWindow);
  glfwSetWindowUserPointer(this->glfwWindow, this);
  glfwSetFramebufferSizeCallback(this->glfwWindow, framebufferSizeCallback);
  return true;
}

bool kdr::Window::_initializeGlew()
{
  GLenum glewErr = glewInit();
  if (GLEW_OK != glewErr)
  {
    std::cerr << "Failed to initialize GLEW!\n";
    std::cerr << "Error: " << glewGetErrorString(glewErr) << '\n';
    return false;
  }
  return true;
}

bool kdr::Window::_initializeOpenGLSettings()
{
  glPointSize(5.f);
  return true;
}

void kdr::Window::_initialize()
{
  this->_initializeGlfw();
  this->_initializeWindow();
  this->_initializeGlew();
  this->_initializeOpenGLSettings();
}

void kdr::Window::_updateBoundCamera()
{
  if (this->boundCamera == NULL) return;
  if (this->boundShaderID == 0) return;

  this->boundCamera->handleMovement(this->glfwWindow);
  this->boundCamera->handleMouseMovement(this->glfwWindow);
  this->boundCamera->updateMatrix();
  this->boundCamera->applyMatrix(this->boundShaderID, "cameraMatrix");
}

void kdr::Window::_update()
{
  glfwPollEvents();
  this->_updateBoundCamera();
  this->update();
}

void kdr::Window::_render()
{
  glClear(GL_COLOR_BUFFER_BIT);
  this->render();
  glfwSwapBuffers(this->glfwWindow);
}
