#ifndef KDR_CAMERA_HPP
#define KDR_CAMERA_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

#include "Keys.hpp"
#include "Space.hpp"

namespace kdr
{
  /**
   * Struct containing properties for configuring a camera.
   */
  struct CameraProps
  {
    float fov;
    float aspect;
    float near;
    float far;
    float speed;
    float sensitivity;

    /**
     * Constructs a CameraProps with the specified parameters.
     *
     * @param fov The field of view angle in degrees.
     * @param aspect The aspect ratio of the viewport (width/height).
     * @param near The distance to the near clipping plane.
     * @param far The distance to the far clipping plane.
     * @param speed The movement speed of the camera.
     * @param sensitivity The mouse sensitivity for camera rotation.
     */
    CameraProps(
      const float fov,
      const float aspect,
      const float near,
      const float far,
      const float speed,
      const float sensitivity
    ) : fov(fov), aspect(aspect), near(near), far(far), speed(speed), sensitivity(sensitivity)
    {}
  };

  class Camera
  {
    public:
      /**
       * Constructs a Camera with the specified properties.
       *
       * @param cameraProps The properties to configure the camera.
       */
      Camera(const kdr::CameraProps& cameraProps)
      : fov(cameraProps.fov),
        aspect(cameraProps.aspect),
        near(cameraProps.near),
        far(cameraProps.far),
        speed(cameraProps.speed),
        sensitivity(cameraProps.sensitivity)
      {}

      /**
       * Sets the aspect ratio of the camera.
       *
       * @param aspect The new aspect ratio to set.
       */
      void setAspect(const float aspect)
      { this->aspect = aspect; }
      /**
       * Sets the mouse lock status for the camera.
       *
       * @param locked If true, the mouse is locked; if false, the mouse is unlocked.
       */
      void setIsMouseLocked(const bool locked)
      { this->isMouseLocked = locked; }

      /**
       * Updates the internal transformation matrix of the camera.
       */
      void updateMatrix();
      /**
       * Applies the camera matrix to a shader uniform.
       *
       * @param shaderID The ID of the shader program.
       * @param uniformName The name of the uniform variable in the shader.
       */
      void applyMatrix(const GLuint shaderID, const std::string& uniformName);
      /**
       * Handles camera movement based on user input.
       *
       * @param window The GLFW window for input handling.
       * @param deltaTime The time difference (delta time) since the last update.
       */
      void handleMovement(GLFWwindow* window, const float deltaTime);
      /**
       * Handles mouse movement for the camera.
       *
       * @param window The GLFW window for input handling.
       */
      void handleMouseMovement(GLFWwindow* window);

    private:
      float fov         {60.f};
      float aspect      {1.f};
      float near        {0.1f};
      float far         {100.f};
      float speed       {4.f};
      float sensitivity {12.f};

      kdr::space::Mat4 matrix;
      kdr::space::Vec3 position {0.f,  0.f, -5.f};
      kdr::space::Vec3 up       {0.f, -1.f,  0.f};
      kdr::space::Vec3 front    {0.f,  0.f, -1.f};

      bool isMouseLocked {false};
  };
}

#endif // KDR_CAMERA_HPP
