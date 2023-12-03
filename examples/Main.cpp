#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <string>

#include "Kedarium/Core.hpp"
#include "Kedarium/Color.hpp"
#include "Kedarium/Keys.hpp"
#include "Kedarium/Graphics.hpp"
#include "Kedarium/Window.hpp"
#include "Kedarium/Camera.hpp"
#include "Kedarium/Solids.hpp"

// Constants
constexpr unsigned int WINDOW_WIDTH  {800};
constexpr unsigned int WINDOW_HEIGHT {600};
const     std::string  WINDOW_TITLE  {"GLFW"};

// Camera Settings
constexpr float CAMERA_FOV         {60.f};
constexpr float CAMERA_ASPECT      {(float)WINDOW_WIDTH / WINDOW_HEIGHT};
constexpr float CAMERA_NEAR        {0.1f};
constexpr float CAMERA_FAR         {100.f};
constexpr float CAMERA_SPEED       {4.f};
constexpr float CAMERA_SENSITIVITY {0.1f};

class MainWindow : public kdr::Window
{
  public:
    using kdr::Window::Window;

    ~MainWindow()
    {
      this->defaultShader.Delete();
      this->concreteTexture.Delete();
    }

    void setup()
    {
      // Engine and Version info
      kdr::core::printEngineInfo();
      std::cout << '\n';
      kdr::core::printVersionInfo();

      for (int z = 0; z < 3; z++)
      {
        for (int x = 0; x < 3; x++)
        {
          this->pyramids.push_back(new kdr::solids::Pyramid(
            {(x - 1.f), 0.f, (z - 1.f)},
            1.f,
            1.f
          ));
        }
      }

      this->magmaTexture.TextureUnit(this->defaultShader.getID(), "tex0", 0);
      this->concreteTexture.TextureUnit(this->defaultShader.getID(), "tex0", 0);
    }

    void update()
    {
      this->testMesh.rotateY(100.f * this->getDeltaTime());

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
      this->magmaTexture.Bind();
      testMesh.render(this->defaultShader.getID());
      this->concreteTexture.Bind();
      testPlane.render(this->defaultShader.getID());
    }

  private:
    kdr::gfx::Shader defaultShader {
      "resources/Shaders/default.vert",
      "resources/Shaders/default.frag"
    };
    kdr::gfx::Texture magmaTexture {
      "resources/Textures/magma.png",
      GL_TEXTURE_2D,
      GL_TEXTURE0,
      GL_RGBA,
      GL_UNSIGNED_BYTE
    };
    kdr::gfx::Texture concreteTexture {
      "resources/Textures/concrete.png",
      GL_TEXTURE_2D,
      GL_TEXTURE0,
      GL_RGBA,
      GL_UNSIGNED_BYTE
    };
    kdr::solids::Mesh testMesh {
      {0.f, 0.f, 0.f},
      "resources/Models/icosphere.obj"
    };
    kdr::solids::Plane testPlane {
      {0.f, -1.f, 0.f},
      5.f,
      5.f
    };
    std::vector<kdr::solids::Pyramid*> pyramids;
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
