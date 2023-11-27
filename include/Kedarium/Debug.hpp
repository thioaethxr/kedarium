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
     */
    inline void printVector(const kdr::space::Vec3& vec)
    {
      std::cout << "X: " << vec.x << "; Y: " << vec.y << "; Z: " << vec.z << '\n';
    }
  }
}

#endif // KDR_UTILS_HPP
