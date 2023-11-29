#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "Kedarium/Core.hpp"
#include "Kedarium/Color.hpp"
#include "Kedarium/Keys.hpp"
#include "Kedarium/Graphics.hpp"
#include "Kedarium/Window.hpp"
#include "Kedarium/Camera.hpp"
#include "Kedarium/Debug.hpp"

// Constants
constexpr unsigned int WINDOW_WIDTH  {800};
constexpr unsigned int WINDOW_HEIGHT {600};
const     std::string  WINDOW_TITLE  {"GLFW"};

// Camera Settings
constexpr float CAMERA_FOV         {60.f};
constexpr float CAMERA_ASPECT      {(float)WINDOW_WIDTH / WINDOW_HEIGHT};
constexpr float CAMERA_NEAR        {0.1f};
constexpr float CAMERA_FAR         {100.f};
constexpr float CAMERA_SPEED       {0.1f};
constexpr float CAMERA_SENSITIVITY {100.f};

// Vertices and Indices
GLfloat vertices[] = {
  -0.5f, -0.5f, 0.f, 1.f, 1.f, 1.f, 0.f, 0.f,
   0.5f, -0.5f, 0.f, 1.f, 1.f, 1.f, 1.f, 0.f,
  -0.5f,  0.5f, 0.f, 1.f, 1.f, 1.f, 0.f, 1.f,
   0.5f,  0.5f, 0.f, 1.f, 1.f, 1.f, 1.f, 1.f,
};
GLuint indices[] = {
  0, 1, 3,
  0, 3, 2,
};

class MainWindow : public kdr::Window
{
  public:
    using kdr::Window::Window;

    ~MainWindow()
    {
      this->defaultShader.Delete();
      this->concreteTexture.Delete();

      this->VAO1.Delete();
      this->VBO1.Delete();
      this->EBO1.Delete();
    }

    void setup()
    {
      // Engine and Version info
      kdr::core::printEngineInfo();
      std::cout << '\n';
      kdr::core::printVersionInfo();

      this->concreteTexture.TextureUnit(this->defaultShader.getID(), "tex0", 0);

      this->VAO1.Bind();
      this->VBO1.Bind();
      this->EBO1.Bind();

      this->VAO1.LinkAttribute(this->VBO1, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)0);
      this->VAO1.LinkAttribute(this->VBO1, 1, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
      this->VAO1.LinkAttribute(this->VBO1, 2, 2, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));

      this->VAO1.Unbind();
      this->VBO1.Unbind();
      this->EBO1.Unbind();
    }

    void update()
    {
      if (kdr::keys::isPressed(this->getGlfwWindow(), kdr::Key::E))
      {
        this->getBoundCamera()->setIsMouseLocked(true);
      }
      else if (kdr::keys::isPressed(this->getGlfwWindow(), kdr::Key::Escape))
      {
        this->getBoundCamera()->setIsMouseLocked(false);
      }

      if (kdr::keys::isPressed(this->getGlfwWindow(), kdr::Key::F))
      {
        if (!this->pressingFullscreen)
        {
          this->isFullscreenOn ? this->unmaximize() : this->maximize();
          this->pressingFullscreen = true;
        }
      }
      else
      {
        this->pressingFullscreen = false;
      }

      if (kdr::keys::isPressed(this->getGlfwWindow(), kdr::Key::C))
      {
        kdr::gfx::usePointMode();
      }
      else if (kdr::keys::isPressed(this->getGlfwWindow(), kdr::Key::V))
      {
        kdr::gfx::useLineMode();
      }
      else if (kdr::keys::isPressed(this->getGlfwWindow(), kdr::Key::B))
      {
        kdr::gfx::useFillMode();
      }
    }

    void render()
    {
      this->bindShader(this->defaultShader);
      this->VAO1.Bind();
      this->concreteTexture.Bind();
      glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
    }

  private:
    kdr::gfx::Shader defaultShader {
      "resources/Shaders/default.vert",
      "resources/Shaders/default.frag"
    };
    kdr::gfx::Texture concreteTexture {
      "resources/Textures/concrete.png",
      GL_TEXTURE_2D,
      GL_TEXTURE0,
      GL_RGBA,
      GL_UNSIGNED_BYTE
    };
    kdr::gfx::VAO VAO1;
    kdr::gfx::VBO VBO1 {vertices, sizeof(vertices)};
    kdr::gfx::EBO EBO1 {indices, sizeof(indices)};

    bool pressingFullscreen {false};
};

int main()
{
  // Window
  MainWindow mainWindow {{
    WINDOW_WIDTH,
    WINDOW_HEIGHT,
    WINDOW_TITLE
  }};

  // Camera
  kdr::Camera mainCamera {{
    CAMERA_FOV,
    CAMERA_ASPECT,
    CAMERA_NEAR,
    CAMERA_FAR,
    CAMERA_SPEED,
    CAMERA_SENSITIVITY
  }};

  mainWindow.setClearColor(kdr::Color::Black);
  mainWindow.setBoundCamera(&mainCamera);
  mainWindow.setup();
  mainWindow.loop();

  kdr::core::terminate();
  return 0;
}
