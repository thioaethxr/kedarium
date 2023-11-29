#include "Kedarium/Graphics.hpp"

kdr::gfx::Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
  const std::string vertexShaderSource = kdr::file::getContents(vertexPath);
  const std::string fragmentShaderSource = kdr::file::getContents(fragmentPath);

  const char* vertexShaderSourceC = vertexShaderSource.c_str();
  const char* fragmentShaderSourceC = fragmentShaderSource.c_str();

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(vertexShader, 1, &vertexShaderSourceC, NULL);
  glShaderSource(fragmentShader, 1, &fragmentShaderSourceC, NULL);

  glCompileShader(vertexShader);
  glCompileShader(fragmentShader);

  int success;
  char infoLog[512];

  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cerr << "Failed to compile the vertex shader!\n";
    std::cerr << "Error: " << infoLog << '\n';
  }

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cerr << "Failed to compile the fragment shader!\n";
    std::cerr << "Error: " << infoLog << '\n';
  }

  this->ID = glCreateProgram();
  glAttachShader(this->ID, vertexShader);
  glAttachShader(this->ID, fragmentShader);
  glLinkProgram(this->ID);

  glGetProgramiv(this->ID, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(this->ID, 512, NULL, infoLog);
    std::cerr << "Failed to link the shader program (" << this->ID << ")!\n";
    std::cerr << "Error: " << infoLog << '\n';
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

kdr::gfx::VBO::VBO(GLfloat vertices[], GLsizeiptr size)
{
  glGenBuffers(1, &this->ID);
  this->Bind();
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
  this->Unbind();
}

kdr::gfx::EBO::EBO(GLuint indices[], GLsizeiptr size)
{
  glGenBuffers(1, &this->ID);
  this->Bind();
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
  this->Unbind();
}

void kdr::gfx::VAO::LinkAttribute(kdr::gfx::VBO& VBO, GLuint layout, GLuint size, GLenum type, GLsizeiptr stride, const void* offset)
{
  VBO.Bind();
  glVertexAttribPointer(layout, size, type, GL_FALSE, stride, (void*)offset);
  glEnableVertexAttribArray(layout);
  VBO.Unbind();
}

kdr::gfx::Texture::Texture(const std::string& imagePath, GLenum type, GLenum slot, GLenum format, GLenum pixelType)
{
  this->type = type;

  int width     {0};
  int height    {0};
  GLubyte* data {NULL};
  kdr::img::loadFromPNG(imagePath, &data, width, height);

  glGenTextures(1, &this->ID);
  glActiveTexture(slot);
  glBindTexture(this->type, this->ID);

  glTexParameteri(this->type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(this->type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexImage2D(this->type, 0, GL_RGBA, width, height, 0, format, pixelType, data);
  glGenerateMipmap(this->type);

  delete data;
  glBindTexture(this->type, 0);
}

void kdr::gfx::Texture::TextureUnit(const GLuint shaderID, const std::string& uniform, GLuint unit)
{
  GLuint texUnitLoc = glGetUniformLocation(shaderID, uniform.c_str());
  glUniform1i(texUnitLoc, unit);
}
