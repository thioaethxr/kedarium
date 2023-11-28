#ifndef KDR_CAMERA_HPP
#define KDR_CAMERA_HPP

#include <GL/glew.h>
#include <string>

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

    private:
      float fov;
      float aspect;
      float near;
      float far;
      float speed;
      float sensitivity;

      kdr::space::Mat4 matrix;
  };
}

#endif // KDR_CAMERA_HPP
