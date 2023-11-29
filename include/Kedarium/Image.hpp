#ifndef KDR_IMAGE_HPP
#define KDR_IMAGE_HPP

#include <GL/glew.h>
#include <png.h>
#include <string.h>
#include <iostream>
#include <string>

namespace kdr
{
  namespace img
  {
    /**
     * Loads image data from a PNG file.
     *
     * @param pngPath The file path to the PNG image.
     * @param data A pointer to the location where the image data will be stored.
     *             The memory is allocated inside the function and needs to be freed by the caller.
     * @param imgWidth Reference to store the width of the loaded image.
     * @param imgHeight Reference to store the height of the loaded image.
     * @return True if the image is loaded successfully, false otherwise.
     */
    bool loadFromPNG(const std::string& pngPath, GLubyte** data, int& imgWidth, int& imgHeight);
  }
}

#endif // KDR_IMAGE_HPP
