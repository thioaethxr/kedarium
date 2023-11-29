#ifndef KDR_WINDOW_HPP
#define KDR_WINDOW_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "Color.hpp"
#include "Graphics.hpp"
#include "Camera.hpp"

namespace kdr
{
  /**
   * Structure representing properties for creating a window.
   */
  struct WindowProps
  {
    unsigned int width;
    unsigned int height;
    std::string title;

    /**
     * Constructs WindowProps with the specified width, height, and title.
     *
     * @param width The width of the window.
     * @param height The height of the window.
     * @param title The title of the window.
     */
    WindowProps(
      const unsigned int width,
      const unsigned int height,
      const std::string& title
    ) : width(width), height(height), title(title)
    {}
  };

  /**
   * Base class representing a window.
   */
  class Window
  {
    public:
      /**
       * Constructs a window with the specified properties.
       *
       * @param windowProps Properties for configuring the window.
       */
      Window(const kdr::WindowProps& windowProps)
      : width(windowProps.width), height(windowProps.height), title(windowProps.title)
      { this->_initialize(); }
      /**
       * Constructs a window with the specified width and height.
       *
       * @param width The width of the window.
       * @param height The height of the window.
       */
      Window(const unsigned int width, const unsigned int height)
      : width(width), height(height)
      { this->_initialize(); }
      /**
       * Constructs a window with the specified width, height, and title.
       *
       * @param width The width of the window.
       * @param height The height of the window.
       * @param title The title of the window.
       */
      Window(const unsigned int width, const unsigned int height, const std::string& title)
      : width(width), height(height), title(title)
      { this->_initialize(); }
      /**
       * Virtual destructor for the Window class.
       */
      virtual ~Window();

      /**
       * Gets the width of the window.
       *
       * @return The width of the window.
       */
      unsigned int getWidth() const
      { return this->width; }
      /**
       * Gets the height of the window.
       *
       * @return The height of the window.
       */
      unsigned int getHeight() const
      { return this->height; }
      /**
       * Gets the title of the window.
       *
       * @return The title of the window.
       */
      std::string getTitle() const
      { return this->title; }
      /**
       * Gets the GLFW window handle.
       *
       * @return The GLFW window handle.
       */
      GLFWwindow* getGlfwWindow() const
      { return this->glfwWindow; }
      /**
       * Gets the currently bound camera.
       *
       * @return A pointer to the currently bound camera.
       */
      kdr::Camera* getBoundCamera() const
      { return this->boundCamera; }

      /**
       * Sets the clear color for the window.
       *
       * @param clearColor The RGBA color to set as the clear color.
       */
      void setClearColor(const kdr::Color::RGBA& clearColor)
      {
        this->clearColor = clearColor;
        glClearColor(
          clearColor.red,
          clearColor.green,
          clearColor.blue,
          clearColor.alpha
        );
      }
      /**
       * Sets the camera to be used for rendering.
       *
       * @param camera A pointer to the camera to be used for rendering.
       */
      void setBoundCamera(kdr::Camera* camera)
      { this->boundCamera = camera; }

      /**
       * Stars the main loop function for the window.
       */
      void loop();
      /**
       * Closes the window.
       */
      void close();
      /**
       * Maximizes the window.
       */
      void maximize();
      /**
       * Unmaximizes the window.
       */
      void unmaximize();
      /**
       * Binds a shader for rendering.
       *
       * @param shader The shader to be bound.
       */
      void bindShader(kdr::gfx::Shader& shader)
      {
        shader.Use();
        this->boundShaderID = shader.getID();
      }

    protected:
      bool isFullscreenOn {false};

      /**
       * Pure virtual function for setting up the window.
       */
      virtual void setup() = 0;
      /**
       * Pure virtual function for updating the window.
       */
      virtual void update() = 0;
      /**
       * Pure virtual function for rendering the window.
       */
      virtual void render() = 0;

    private:
      unsigned int width  {800};
      unsigned int height {600}; 
      std::string  title  {"Kedarium"};

      GLFWwindow*      glfwWindow {NULL};
      kdr::Color::RGBA clearColor = kdr::Color::Black;

      kdr::Camera* boundCamera   {NULL};
      GLuint       boundShaderID {0};

      /**
       * Initializes GLFW.
       *
       * @return True if initialization is successful, false otherwise.
       */
      bool _initializeGlfw();
      /**
       * Initializes the window.
       *
       * @return True if initialization is successful, false otherwise.
       */
      bool _initializeWindow();
      /**
       * Initializes GLEW.
       *
       * @return True if initialization is successful, false otherwise.
       */
      bool _initializeGlew();
      /**
       * Initializes OpenGL settings.
       * 
       * @return True if initialization is successful, false otherwise.
       */
      bool _initializeOpenGLSettings();
      /**
       * Overall initialization function.
       */
      void _initialize();
      /**
       * @brief Updates the currently bound camera.
       */
      void _updateBoundCamera();
      /**
       * Updates the window.
       */
      void _update();
      /**
       * Renders the window.
       */
      void _render();
  };
}

#endif // KDR_WINDOW_HPP
