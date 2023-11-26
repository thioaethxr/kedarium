#ifndef KDR_GRAPHICS_HPP
#define KDR_GRAPHICS_HPP

#include <GL/glew.h>

namespace kdr
{
  namespace gfx
  {
    /**
     * Sets the OpenGL polygon mode to render points.
     */
    inline void usePointMode()
    { glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); }
    /**
     * Sets the OpenGL polygon mode to render lines.
     */
    inline void useLineMode()
    { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }
    /**
     * Sets the OpenGL polygon mode to filled polygons.
     */
    inline void useFillMode()
    { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }

    /**
     * Vertex Buffer Object (VBO) class for handling vertex data.
     */
    class VBO
    {
      public:
        /**
         * Constructs a VBO with the given vertex data and size.
         *
         * @param vertices An array of GLfloat representing the vertex data.
         * @param size The size of the vertex data in bytes.
         */
        VBO(GLfloat vertices[], GLsizeiptr size);

        /**
         * Gets the ID of the VBO.
         *
         * @return The OpenGL identifier (ID) of the VBO.
         */
        const GLuint getID() const
        { return this->ID; }

        /**
         * Binds the VBO to the OpenGL context.
         */
        void Bind()
        { glBindBuffer(GL_ARRAY_BUFFER, this->ID); }
        /**
         * Unbinds the currently bound VBO from the OpenGL context
         */
        void Unbind()
        { glBindBuffer(GL_ARRAY_BUFFER, 0); }
        /**
         * Deletes the VBO, freeing up associated resources in the GPU.
         */
        void Delete()
        { glDeleteBuffers(1, &this->ID); }

      private:
        GLuint ID;
    };
  };
}

#endif // KDR_GRAPHICS_HPP
