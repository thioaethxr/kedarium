#include "Kedarium/Solids.hpp"

kdr::solids::Solid::~Solid()
{
  this->VAO->Delete();
  this->VBO->Delete();
  this->EBO->Delete();

  delete this->VAO;
  delete this->VBO;
  delete this->EBO;
}

void kdr::solids::Solid::_applyPosition(const GLuint shaderID)
{
  kdr::space::Mat4 model {1.f};
  model = kdr::space::translate(
    model,
    this->position
  );
  GLuint modelLoc = glGetUniformLocation(shaderID, "model");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, kdr::space::valuePointer(model));
}

GLuint cubeIndices[] = {
  0,  1,  3,  // FT
  0,  3,  2,  // FT
  4,  5,  7,  // RT
  4,  7,  6,  // RT
  8,  9,  11, // BK
  8,  11, 10, // BK
  12, 13, 15, // LT
  12, 15, 14, // LT
  16, 17, 19, // TP
  16, 19, 18, // TP
  20, 21, 23, // BT
  20, 23, 22, // BT
};

kdr::solids::Cube::Cube(const kdr::space::Vec3& position, const float edgeLength) : kdr::solids::Solid(position)
{
  GLfloat cubeVertices[] = {
    -(edgeLength / 2.f), -(edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 0.f, // FT 000 0
     (edgeLength / 2.f), -(edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 0.f, // FT 100 1
    -(edgeLength / 2.f),  (edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 1.f, // FT 010 2
     (edgeLength / 2.f),  (edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 1.f, // FT 110 3
     (edgeLength / 2.f), -(edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 0.f, // RT 100 4
     (edgeLength / 2.f), -(edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 0.f, // RT 101 5
     (edgeLength / 2.f),  (edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 1.f, // RT 110 6
     (edgeLength / 2.f),  (edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 1.f, // RT 111 7
     (edgeLength / 2.f), -(edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 0.f, // BK 101 8
    -(edgeLength / 2.f), -(edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 0.f, // BK 001 9
     (edgeLength / 2.f),  (edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 1.f, // BK 111 10
    -(edgeLength / 2.f),  (edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 1.f, // BK 011 11
    -(edgeLength / 2.f), -(edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 0.f, // LT 001 12
    -(edgeLength / 2.f), -(edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 0.f, // LT 000 13
    -(edgeLength / 2.f),  (edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 1.f, // LT 011 14
    -(edgeLength / 2.f),  (edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 1.f, // LT 010 15
    -(edgeLength / 2.f),  (edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 0.f, // TP 010 16
     (edgeLength / 2.f),  (edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 0.f, // TP 110 17
    -(edgeLength / 2.f),  (edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 1.f, // TP 011 18
     (edgeLength / 2.f),  (edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 1.f, // TP 111 19
    -(edgeLength / 2.f), -(edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 0.f, // BT 001 20
     (edgeLength / 2.f), -(edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 0.f, // BT 101 21
    -(edgeLength / 2.f), -(edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 1.f, // BT 000 22
     (edgeLength / 2.f), -(edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 1.f, // BT 100 23
  };

  this->VAO = new kdr::gfx::VAO();
  this->VBO = new kdr::gfx::VBO {cubeVertices, sizeof(cubeVertices)};
  this->EBO = new kdr::gfx::EBO {cubeIndices, sizeof(cubeIndices)};

  this->VAO->Bind();
  this->VBO->Bind();
  this->EBO->Bind();

  this->VAO->LinkAttribute(*this->VBO, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)0);
  this->VAO->LinkAttribute(*this->VBO, 1, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
  this->VAO->LinkAttribute(*this->VBO, 2, 2, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));

  this->VAO->Unbind();
  this->VBO->Unbind();
  this->EBO->Unbind();
}

void kdr::solids::Cube::render(const GLuint shaderID)
{
  this->VAO->Bind();
  this->_applyPosition(shaderID);
  glDrawElements(GL_TRIANGLES, sizeof(cubeIndices) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
  this->VAO->Unbind();
}

GLuint cuboidIndices[] = {
  0,  1,  3,  // FT
  0,  3,  2,  // FT
  4,  5,  7,  // RT
  4,  7,  6,  // RT
  8,  9,  11, // BK
  8,  11, 10, // BK
  12, 13, 15, // LT
  12, 15, 14, // LT
  16, 17, 19, // TP
  16, 19, 18, // TP
  20, 21, 23, // BT
  20, 23, 22, // BT
};

kdr::solids::Cuboid::Cuboid(const kdr::space::Vec3& position, const float length, const float height, const float width) : kdr::solids::Solid(position)
{
  GLfloat cuboidVertices[] = {
    -(length / 2.f), -(height / 2.f),  (width / 2.f), 1.f, 1.f, 1.f, 0.f,    0.f,    // FT 000 0
     (length / 2.f), -(height / 2.f),  (width / 2.f), 1.f, 1.f, 1.f, length, 0.f,    // FT 100 1
    -(length / 2.f),  (height / 2.f),  (width / 2.f), 1.f, 1.f, 1.f, 0.f,    height, // FT 010 2
     (length / 2.f),  (height / 2.f),  (width / 2.f), 1.f, 1.f, 1.f, length, height, // FT 110 3
     (length / 2.f), -(height / 2.f),  (width / 2.f), 1.f, 1.f, 1.f, 0.f,    0.f,    // RT 100 4
     (length / 2.f), -(height / 2.f), -(width / 2.f), 1.f, 1.f, 1.f, width,  0.f,    // RT 101 5
     (length / 2.f),  (height / 2.f),  (width / 2.f), 1.f, 1.f, 1.f, 0.f,    height, // RT 110 6
     (length / 2.f),  (height / 2.f), -(width / 2.f), 1.f, 1.f, 1.f, width,  height, // RT 111 7
     (length / 2.f), -(height / 2.f), -(width / 2.f), 1.f, 1.f, 1.f, 0.f,    0.f,    // BK 101 8
    -(length / 2.f), -(height / 2.f), -(width / 2.f), 1.f, 1.f, 1.f, length, 0.f,    // BK 001 9
     (length / 2.f),  (height / 2.f), -(width / 2.f), 1.f, 1.f, 1.f, 0.f,    height, // BK 111 10
    -(length / 2.f),  (height / 2.f), -(width / 2.f), 1.f, 1.f, 1.f, length, height, // BK 011 11
    -(length / 2.f), -(height / 2.f), -(width / 2.f), 1.f, 1.f, 1.f, 0.f,    0.f,    // LT 001 12
    -(length / 2.f), -(height / 2.f),  (width / 2.f), 1.f, 1.f, 1.f, width,  0.f,    // LT 000 13
    -(length / 2.f),  (height / 2.f), -(width / 2.f), 1.f, 1.f, 1.f, 0.f,    height, // LT 011 14
    -(length / 2.f),  (height / 2.f),  (width / 2.f), 1.f, 1.f, 1.f, width,  height, // LT 010 15
    -(length / 2.f),  (height / 2.f),  (width / 2.f), 1.f, 1.f, 1.f, 0.f,    0.f,    // TP 010 16
     (length / 2.f),  (height / 2.f),  (width / 2.f), 1.f, 1.f, 1.f, length, 0.f,    // TP 110 17
    -(length / 2.f),  (height / 2.f), -(width / 2.f), 1.f, 1.f, 1.f, 0.f,    height, // TP 011 18
     (length / 2.f),  (height / 2.f), -(width / 2.f), 1.f, 1.f, 1.f, length, height, // TP 111 19
    -(length / 2.f), -(height / 2.f), -(width / 2.f), 1.f, 1.f, 1.f, length, 0.f,    // BT 001 20
     (length / 2.f), -(height / 2.f), -(width / 2.f), 1.f, 1.f, 1.f, 0.f,    0.f,    // BT 101 21
    -(length / 2.f), -(height / 2.f),  (width / 2.f), 1.f, 1.f, 1.f, length, height, // BT 000 22
     (length / 2.f), -(height / 2.f),  (width / 2.f), 1.f, 1.f, 1.f, 0.f,    height, // BT 100 23
  };

  this->VAO = new kdr::gfx::VAO();
  this->VBO = new kdr::gfx::VBO {cuboidVertices, sizeof(cuboidVertices)};
  this->EBO = new kdr::gfx::EBO {cuboidIndices, sizeof(cuboidIndices)};

  this->VAO->Bind();
  this->VBO->Bind();
  this->EBO->Bind();

  this->VAO->LinkAttribute(*this->VBO, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)0);
  this->VAO->LinkAttribute(*this->VBO, 1, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
  this->VAO->LinkAttribute(*this->VBO, 2, 2, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));

  this->VAO->Unbind();
  this->VBO->Unbind();
  this->EBO->Unbind();
}

void kdr::solids::Cuboid::render(const GLuint shaderID)
{
  this->VAO->Bind();
  this->_applyPosition(shaderID);
  glDrawElements(GL_TRIANGLES, sizeof(cuboidIndices) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
  this->VAO->Unbind();
}

GLuint pyramidIndices[] = {
  0,  1,  3,  // BT
  0,  3,  2,  // BT
  4,  5,  12, // FT
  6,  7,  12, // RT
  8,  9,  12, // BK
  10, 11, 12, // LT
};

kdr::solids::Pyramid::Pyramid(const kdr::space::Vec3& position, const float edgeLength, const float height) : kdr::solids::Solid(position)
{
  GLfloat pyramidVertices[] = {
    -(edgeLength / 2.f), -(height / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f,  0.f, // BT 001 0
     (edgeLength / 2.f), -(height / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f,  0.f, // BT 101 1
    -(edgeLength / 2.f), -(height / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f,  1.f, // BT 000 2
     (edgeLength / 2.f), -(height / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f,  1.f, // BT 100 3
    -(edgeLength / 2.f), -(height / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f,  0.f, // FT 000 4
     (edgeLength / 2.f), -(height / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f,  0.f, // FT 100 5
     (edgeLength / 2.f), -(height / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f,  0.f, // RT 100 6
     (edgeLength / 2.f), -(height / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f,  0.f, // RT 101 7
     (edgeLength / 2.f), -(height / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f,  0.f, // BK 101 8
    -(edgeLength / 2.f), -(height / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f,  0.f, // BK 001 9
    -(edgeLength / 2.f), -(height / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f,  0.f, // LT 001 10
    -(edgeLength / 2.f), -(height / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f,  0.f, // LT 000 11
     0.f,                 (height / 2.f),  0.f,                1.f, 1.f, 1.f, 0.5f, 1.f, // TP 111 12
  };

  this->VAO = new kdr::gfx::VAO();
  this->VBO = new kdr::gfx::VBO {pyramidVertices, sizeof(pyramidVertices)};
  this->EBO = new kdr::gfx::EBO {pyramidIndices, sizeof(pyramidIndices)};

  this->VAO->Bind();
  this->VBO->Bind();
  this->EBO->Bind();

  this->VAO->LinkAttribute(*this->VBO, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)0);
  this->VAO->LinkAttribute(*this->VBO, 1, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
  this->VAO->LinkAttribute(*this->VBO, 2, 2, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));

  this->VAO->Unbind();
  this->VBO->Unbind();
  this->EBO->Unbind();
}

void kdr::solids::Pyramid::render(const GLuint shaderID)
{
  this->VAO->Bind();
  this->_applyPosition(shaderID);
  glDrawElements(GL_TRIANGLES, sizeof(pyramidIndices) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
  this->VAO->Unbind();
}

GLuint planeIndices[] = {
  0, 1, 3,
  0, 3, 2,
};

kdr::solids::Plane::Plane(const kdr::space::Vec3& position, const float length, const float width) : kdr::solids::Solid(position)
{
  GLfloat planeVertices[] = {
    -(length / 2.f), 0.f,  (width / 2.f), 1.f, 1.f, 1.f, 0.f,    0.f,   // 00 0
     (length / 2.f), 0.f,  (width / 2.f), 1.f, 1.f, 1.f, length, 0.f,   // 10 1
    -(length / 2.f), 0.f, -(width / 2.f), 1.f, 1.f, 1.f, 0.f,    width, // 01 2
     (length / 2.f), 0.f, -(width / 2.f), 1.f, 1.f, 1.f, length, width, // 11 3
  };

  this->VAO = new kdr::gfx::VAO();
  this->VBO = new kdr::gfx::VBO {planeVertices, sizeof(planeVertices)};
  this->EBO = new kdr::gfx::EBO {planeIndices, sizeof(planeIndices)};

  this->VAO->Bind();
  this->VBO->Bind();
  this->EBO->Bind();

  this->VAO->LinkAttribute(*this->VBO, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)0);
  this->VAO->LinkAttribute(*this->VBO, 1, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
  this->VAO->LinkAttribute(*this->VBO, 2, 2, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));

  this->VAO->Unbind();
  this->VBO->Unbind();
  this->EBO->Unbind();
}

void kdr::solids::Plane::render(const GLuint shaderID)
{
  this->VAO->Bind();
  this->_applyPosition(shaderID);
  glDrawElements(GL_TRIANGLES, sizeof(planeIndices) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
  this->VAO->Unbind();
}
