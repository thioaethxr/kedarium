#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "Kedarium/Core.hpp"
#include "Kedarium/Color.hpp"
#include "Kedarium/Keys.hpp"
#include "Kedarium/Graphics.hpp"
#include "Kedarium/Window.hpp"
#include "Kedarium/Space.hpp"
#include "Kedarium/Debug.hpp"

// Constants
constexpr unsigned int WINDOW_WIDTH  {800};
constexpr unsigned int WINDOW_HEIGHT {600};
const     std::string  WINDOW_TITLE  {"GLFW"};

// Camera Settings
constexpr float CAMERA_FOV    {60.f};
constexpr float CAMERA_ASPECT {(float)WINDOW_WIDTH / WINDOW_HEIGHT};
constexpr float CAMERA_NEAR   {0.1f};
constexpr float CAMERA_FAR    {100.f};

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

class MainWindow : public kdr::Window
{
  public:
    using kdr::Window::Window;

    void setup()
    {
      // Engine and Version info
      kdr::core::printEngineInfo();
      std::cout << '\n';
      kdr::core::printVersionInfo();

      this->VAO1.Bind();
      this->VBO1.Bind();
      this->EBO1.Bind();

      this->VAO1.LinkAttribute(this->VBO1, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)0);
      this->VAO1.LinkAttribute(this->VBO1, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

      this->VAO1.Unbind();
      this->VBO1.Unbind();
      this->EBO1.Unbind();
    }

    void update()
    {
      if (kdr::Keys::isPressed(this->getGlfwWindow(), kdr::Key::C))
      {
        kdr::gfx::usePointMode();
      }
      else if (kdr::Keys::isPressed(this->getGlfwWindow(), kdr::Key::V))
      {
        kdr::gfx::useLineMode();
      }
      else if (kdr::Keys::isPressed(this->getGlfwWindow(), kdr::Key::B))
      {
        kdr::gfx::useFillMode();
      }
    }

    void render()
    {
      this->defaultShader.Use();
      this->VAO1.Bind();

      kdr::space::Mat4 model {1.f};
      kdr::space::Mat4 view  {1.f};
      kdr::space::Mat4 proj  {1.f};

      view = kdr::space::translate(
        view,
        {0.f, 0.f, -3.f}
      );
      proj = kdr::space::perspective(
        CAMERA_FOV,
        CAMERA_ASPECT,
        CAMERA_NEAR,
        CAMERA_FAR
      );

      GLuint modelLoc = glGetUniformLocation(this->defaultShader.getID(), "model");
      GLuint viewLoc = glGetUniformLocation(this->defaultShader.getID(), "view");
      GLuint projLoc = glGetUniformLocation(this->defaultShader.getID(), "proj");

      glUniformMatrix4fv(modelLoc, 1, GL_FALSE, kdr::space::valuePointer(model));
      glUniformMatrix4fv(viewLoc, 1, GL_FALSE, kdr::space::valuePointer(view));
      glUniformMatrix4fv(projLoc, 1, GL_FALSE, kdr::space::valuePointer(proj));

      glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
    }

  private:
    kdr::gfx::Shader defaultShader {
      "resources/Shaders/default.vert",
      "resources/Shaders/default.frag"
    };
    kdr::gfx::VAO VAO1;
    kdr::gfx::VBO VBO1 {vertices, sizeof(vertices)};
    kdr::gfx::EBO EBO1 {indices, sizeof(indices)};
};

int main()
{
  MainWindow mainWindow {{
    WINDOW_WIDTH,
    WINDOW_HEIGHT,
    WINDOW_TITLE
  }};

  mainWindow.setClearColor(kdr::Color::Black);
  mainWindow.setup();
  mainWindow.loop();

  kdr::core::terminate();
  return 0;
}
