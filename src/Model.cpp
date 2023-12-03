#include "Kedarium/Model.hpp"

bool kdr::model::loadFromObj(const std::string& objPath, std::vector<kdr::space::Vec3>& vertices, std::vector<kdr::space::Vec2>& texCoords, std::vector<unsigned int>& indices)
{
  const std::string objContent = kdr::file::getContents(objPath);
  if (objContent.empty())
  {
    std::cerr << "Failed to open object file (" << objPath << ")!\n";
    return false;
  }

  std::istringstream ss(objContent);
  std::string line;

  while (std::getline(ss, line))
  {
    if (line.compare(0, 2, OBJ_VERTEX_PREFIX) == 0)
    {
      std::istringstream vertexStream(line.substr(2));
      kdr::space::Vec3 vertex {0.f};
      vertexStream >> vertex.x >> vertex.y >> vertex.z;
      vertices.push_back(vertex);
    }
    else if (line.compare(0, 2, OBJ_TEXCOORD_PREFIX) == 0)
    {
      std::istringstream texCoordStream(line.substr(2));
      kdr::space::Vec2 texCoord {0.f};
      texCoordStream >> texCoord.x >> texCoord.y;
      texCoords.push_back(texCoord);
    }
    else if (line.compare(0, 2, OBJ_FACE_PREFIX) == 0)
    {
      std::istringstream faceStream(line.substr(2));
      std::string segment;

      while (std::getline(faceStream, segment, ' '))
      {
        std::istringstream segmentStream(segment);
        std::string face;

        while (std::getline(segmentStream, face, '/'))
        {
          indices.push_back(std::stoi(face) - 1);
        }
      }
    }
  }

  return true;
}
