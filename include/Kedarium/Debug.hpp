#ifndef KDR_UTILS_HPP
#define KDR_UTILS_HPP

#include <iostream>

#include "Space.hpp"

namespace kdr
{
  namespace debug
  {
    /**
     * Prints the components of a 3D vector to the console.
     *
     * @param vec The 3D vector to be printed.
     * @param label An optional label for the vector (default is an empty string).
     */
    inline void printVector(const kdr::space::Vec3& vec, const std::string& label = "")
    {
      if (!label.empty()) std::cout << label << " (Vector)\n";
      std::cout << "X: " << vec.x << "; Y: " << vec.y << "; Z: " << vec.z << '\n';
    }
    /**
     * Prints the elements of a 4x4 matrix to the console.
     *
     * @param mat The 4x4 matrix to be printed.
     * @param label An optional label for the matrix (default is an empty string).
     */
    inline void printMatrix(const kdr::space::Mat4& mat, const std::string& label = "")
    {
      if (!label.empty()) std::cout << label << " (Matrix)\n";
      for (int i = 0; i < 4; i++)
      {
        for (int j = 0; j < 4; j++)
        {
          std::cout << mat[i][j] << ' ';
        }
        std::cout << '\n';
      }
    }
  }
}

#endif // KDR_UTILS_HPP
