#ifndef KDR_SOLIDS_HPP
#define KDR_SOLIDS_HPP

#include <GL/glew.h>

#include "Space.hpp"
#include "Graphics.hpp"

namespace kdr
{
  namespace solids
  {
    /**
     * Abstract base class for representing solids in a graphics scene.
     */
    class Solid
    {
      public:
        /**
         * Constructs a Solid object with a specified initial position.
         *
         * @param position The initial position of the solid in 3D space.
         */
        Solid(const kdr::space::Vec3& position) : position(position)
        {}
        /**
         * Destructor for the Solid class.
         */
        virtual ~Solid();

        /**
         * Renders the solid using the specified shader program.
         *
         * @param shaderID The ID of the shader program to use for rendering.
        */
        virtual void render(const GLuint shaderID) = 0;

      protected:
        kdr::space::Vec3 position {0.f};

        kdr::gfx::VAO* VAO {NULL};
        kdr::gfx::VBO* VBO {NULL};
        kdr::gfx::EBO* EBO {NULL};

        /**
         * Applies the position of the solid to the model matrix in the shader.
         *
         * @param shaderID The ID of the shader program.
         */
        void _applyPosition(const GLuint shaderID);
    };

    /**
     * A class representing a 3D cube.
     */
    class Cube : Solid
    {
      public:
        /**
         * Constructs a Cube object with a specified initial position and edge length.
         *
         * @param position   The initial position of the cube in 3D space.
         * @param edgeLength The length of each edge of the cube.
         */
        Cube(const kdr::space::Vec3& position, const float edgeLength);

        /**
         * Renders the cube using the provided shader program.
         *
         * @param shaderID The ID of the shader program to use for rendering.
         */
        void render(const GLuint shaderID);
    };

    /**
     * A class representing a 3D cuboid.
     */
    class Cuboid : Solid
    {
      public:
        /**
         * Constructs a Cuboid object with a specified initial position and dimensions.
         *
         * @param position The initial position of the cuboid in 3D space.
         * @param length   The length of the cuboid along the X-axis.
         * @param height   The height of the cuboid along the Y-axis.
         * @param width    The width of the cuboid along the Z-axis.
         */
        Cuboid(const kdr::space::Vec3& position, const float length, const float height, const float width);

        /**
         * Renders the cuboid using the provided shader program.
         *
         * @param shaderID The ID of the shader program to use for rendering.
         */
        void render(const GLuint shaderID);
    };
  };
}

#endif // KDR_SOLIDS_HPP
