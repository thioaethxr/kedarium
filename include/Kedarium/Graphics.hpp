#ifndef KDR_GRAPHICS_HPP
#define KDR_GRAPHICS_HPP

#include <GL/glew.h>
#include <iostream>

#include "File.hpp"
#include "Image.hpp"

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
     * Shader class for handling vertex and fragment shaders.
     */
    class Shader
    {
      public:
        /**
         * Constructs a Shader with the given vertex and fragment shader file paths.
         *
         * @param vertexPath The file path to the vertex shader.
         * @param fragmentPath The file path to the fragment shader.
         */
        Shader(const std::string& vertexPath, const std::string& fragmentPath);

        /**
         * Gets the ID of the shader program.
         *
         * @return The OpenGL identifier (ID) of the shader program.
         */
        GLuint getID() const
        { return this->ID; }

        /**
         * Uses the shader program.
         */
        void Use()
        { glUseProgram(this->ID); }
        /**
         * Deletes the shader program, freeing up associated resources in the GPU.
         */
        void Delete()
        { glDeleteProgram(this->ID); }

      private:
        GLuint ID;
    };

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
        GLuint getID() const
        { return this->ID; }

        /**
         * Binds the VBO to the OpenGL context.
         */
        void Bind()
        { glBindBuffer(GL_ARRAY_BUFFER, this->ID); }
        /**
         * Unbinds the currently bound VBO from the OpenGL context.
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

    /**
     * Element Buffer Object (EBO) class for handling index data.
     */
    class EBO
    {
      public:
        /**
         * Constructs an EBO with the given index data and size.
         *
         * @param indices An array of GLuint representing the index data.
         * @param size The size of the index data in bytes.
         */
        EBO(GLuint indices[], GLsizeiptr size);

        /**
         * Gets the ID of the EBO.
         *
         * @return The OpenGL identifier (ID) of the EBO.
         */
        GLuint getID() const
        { return this->ID; }

        /**
         * Binds the EBO to the OpenGL context.
         */
        void Bind()
        { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID); }
        /**
         * Unbinds the currently bound EBO from the OpenGL context.
         */
        void Unbind()
        { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
        /**
         * Deletes the EBO, freeing up associated resources in the GPU.
         */
        void Delete()
        { glDeleteBuffers(1, &this->ID); }

      private:
        GLuint ID;
    };

    /**
     * Vertex Array Object (VAO) class for handling vertex array data.
     */
    class VAO
    {
      public:
        /**
         * Constructs a VAO and generates its identifier.
         */
        VAO()
        { glGenVertexArrays(1, &this->ID); }

        /**
         * Gets the ID of the VAO.
         *
         * @return The OpenGL identifier (ID) of the VAO.
         */
        GLuint getID() const
        { return this->ID; }

        /**
         * Links a vertex buffer object (VBO) attribute to the VAO.
         *
         * @param VBO The VBO containing the attribute data.
         * @param layout The attribute layout location.
         * @param size The number of components per attribute.
         * @param type The data type of each component.
         * @param stride The byte offset between consecutive attributes.
         * @param offset The byte offset of the first component in the attribute.
         */
        void LinkAttribute(kdr::gfx::VBO& VBO, GLuint layout, GLuint size, GLenum type, GLsizeiptr stride, const void* offset);
        /**
         * Binds the VAO to the OpenGL context.
         */
        void Bind()
        { glBindVertexArray(this->ID); }
        /**
         * Unbinds the currently bound VAO from the OpenGL context.
         */
        void Unbind()
        { glBindVertexArray(0); }
        /**
         * Deletes the VAO, freeing up associated resources in the GPU.
         */
        void Delete()
        { glDeleteVertexArrays(1, &this->ID); }

      private:
        GLuint ID;
    };

    /**
     * A class for handling OpenGL textures.
     */
    class Texture
    {
      public:
        /**
         * Constructor for creating a texture from an image file.
         *
         * @param imagePath The file path to the PNG image.
         * @param type The type of the texture (e.g., GL_TEXTURE_2D).
         * @param slot The texture unit slot to bind the texture to.
         * @param format The internal format of the texture.
         * @param pixelType The data type of the pixel data.
         */
        Texture(const std::string& imagePath, GLenum type, GLenum slot, GLenum format, GLenum pixelType);

         /**
         * Gets the ID of the texture.
         *
         * @return The ID of the texture.
         */
        const GLuint getID() const
        { return this->ID; }

        /**
         * Sets the texture unit of a shader uniform variable.
         *
         * @param shaderID The ID of the shader program.
         * @param uniform The name of the uniform variable in the shader.
         * @param unit The texture unit to bind.
         */
        void TextureUnit(const GLuint shaderID, const std::string& uniform, GLuint unit);
        /**
         * Binds the texture to the OpenGL context.
         */
        void Bind()
        { glBindTexture(this->type, this->ID); }
        /**
         * Unbinds the currently bound texture from the OpenGL context.
         */
        void Unbind()
        { glBindTexture(this->type, 0); }
        /**
         * Deletes the texture, freeing up associated resources in the GPU.
         */
        void Delete()
        { glDeleteTextures(1, &this->ID); }

      private:
        GLuint ID;
        GLenum type;
    };
  };
}

#endif // KDR_GRAPHICS_HPP
