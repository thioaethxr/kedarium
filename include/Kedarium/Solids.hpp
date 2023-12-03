#ifndef KDR_SOLIDS_HPP
#define KDR_SOLIDS_HPP

#include <GL/glew.h>
#include <string>

#include "Space.hpp"
#include "Graphics.hpp"
#include "Model.hpp"

#include "Debug.hpp"

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
        {
          this->model = kdr::space::translate(this->model, position);
        }
        /**
         * Destructor for the Solid class.
         */
        virtual ~Solid();

        /**
         * Rotates the Solid around the X-axis by a specified angle.
         *
         * @param angle The angle of rotation in radians.
         */
        void rotateX(const float angle);
        /**
         * Rotates the Solid around the Y-axis by a specified angle.
         *
         * @param angle The angle of rotation in radians.
         */
        void rotateY(const float angle);
        /**
         * Rotates the Solid around the Z-axis by a specified angle.
         *
         * @param angle The angle of rotation in radians.
         */
        void rotateZ(const float angle);

        /**
         * Renders the solid using the specified shader program.
         *
         * @param shaderID The ID of the shader program to use for rendering.
        */
        virtual void render(const GLuint shaderID) = 0;

      protected:
        kdr::space::Vec3 position {0.f};
        kdr::space::Mat4 model    {1.f};

        kdr::gfx::VAO* VAO {NULL};
        kdr::gfx::VBO* VBO {NULL};
        kdr::gfx::EBO* EBO {NULL};

        /**
         * Initializes the graphical components (VAO, VBO, EBO) for rendering the solid.
         *
         * @param vertices      An array containing the vertex data of the solid.
         * @param verticesSize  The size of the vertices array in bytes.
         * @param indices       An array containing the index data for forming triangles.
         * @param indicesSize   The size of the indices array in bytes.
         */
        void _initializeComponents(GLfloat vertices[], GLsizeiptr verticesSize, GLuint indices[], GLsizeiptr indicesSize);
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
    class Cube : public Solid
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
    class Cuboid : public Solid
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

    /**
     * A class representing a 3D pyramid.
     */
    class Pyramid : public Solid
    {
      public:
        /**
         * Constructs a Pyramid object with a specified initial position, edge length, and height.
         *
         * @param position   The initial position of the pyramid in 3D space.
         * @param edgeLength The length of the edges of the pyramid's base.
         * @param height     The height of the pyramid.
         */
        Pyramid(const kdr::space::Vec3& position, const float edgeLength, const float height);

        /**
         * Renders the pyramid using the provided shader program.
         *
         * @param shaderID The ID of the shader program to use for rendering.
         */
        void render(const GLuint shaderID);
    };

    /**
     * A class representing a 3D plane.
     */
    class Plane : public Solid
    {
      public:
        /**
         * @brief Constructs a Plane object with a specified initial position, length, and width.
         *
         * @param position The initial position of the plane in 3D space.
         * @param length   The length of the plane.
         * @param width    The width of the plane.
         */
        Plane(const kdr::space::Vec3& position, const float length, const float width);

        /**
         * Renders the plane using the provided shader program.
         *
         * @param shaderID The ID of the shader program to use for rendering.
         */
        void render(const GLuint shaderID);
    };

    /**
     * A class representing a 3D mesh.
     */
    class Mesh : public Solid
    {
      public:
        /**
         * Constructs a Mesh object with a specified initial position and loads mesh data from an OBJ file.
         *
         * @param position The initial position of the mesh in 3D space.
         * @param objPath  The file path to the OBJ model.
         */
        Mesh(const kdr::space::Vec3& position, const std::string& objPath);

        /**
         * Generates vertex array object (VAO), vertex buffer object (VBO), and element buffer object (EBO) components for the Mesh.
         *
         * @param vertices  A vector containing vertex positions.
         * @param texCoords A vector containing texture coordinates.
         * @param indices   A vector containing face indices.
         * @return True if the component generation is successful; false otherwise.
         */
        bool generateComponents(const std::vector<kdr::space::Vec3>& vertices, const std::vector<kdr::space::Vec2>& texCoords, const std::vector<unsigned int>& indices);

        /**
         * Renders the mesh using the provided shader program.
         *
         * @param shaderID The ID of the shader program to use for rendering.
         */
        void render(const GLuint shaderID);

      private:
        unsigned int indicesCount;
    };
  }
}

#endif // KDR_SOLIDS_HPP
