#ifndef KDR_MODEL_HPP
#define KDR_MODEL_HPP

#include <sstream>
#include <iostream>
#include <vector>
#include <string>

#include "Core.hpp"
#include "File.hpp"
#include "Space.hpp"
#include "Graphics.hpp"

namespace kdr
{
  namespace model
  {
    /**
     * Loads vertex, texture coordinate, and index data from an OBJ file.
     *
     * @param objPath   The file path to the OBJ file.
     * @param vertices  A vector to store the extracted vertex positions.
     * @param texCoords A vector to store the extracted texture coordinates.
     * @param indices   A vector to store the extracted face indices.
     * @return True if the loading process is successful; false otherwise.
     */
    bool loadFromObj(const std::string& objPath, std::vector<kdr::space::Vec3>& vertices, std::vector<kdr::space::Vec2>& texCoords, std::vector<unsigned int>& indices);
  }
}

#endif // KDR_MODEL_HPP
