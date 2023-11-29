#include "Kedarium/Image.hpp"

bool kdr::img::loadFromPNG(const std::string& pngPath, GLubyte** data, int& imgWidth, int& imgHeight)
{
  png_structp  pngPtr;
  png_infop    infoPtr;
  unsigned int sigRead {0};

  FILE* file = fopen(pngPath.c_str(), "rb");
  if (!file)
  {
    std::cerr << "Failed to open file (" << pngPath << ")!\n";
    return false;
  }

  pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (pngPtr == NULL)
  {
    std::cerr << "Failed to create a read struct for a PNG!\n";
    fclose(file);
    return false;
  }

  infoPtr = png_create_info_struct(pngPtr);
  if (infoPtr == NULL)
  {
    std::cerr << "Failed to create an info struct for a PNG!\n";
    fclose(file);
    png_destroy_read_struct(&pngPtr, NULL, NULL);
    return false;
  }

  if (setjmp(png_jmpbuf(pngPtr)))
  {
    fclose(file);
    png_destroy_read_struct(&pngPtr, NULL, NULL);
    return false;
  }

  png_init_io(pngPtr, file);
  png_set_sig_bytes(pngPtr, sigRead);

  png_read_png(
    pngPtr,
    infoPtr,
    PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND,
    NULL
  );
  png_uint_32 width;
  png_uint_32 height;

  png_get_IHDR(pngPtr, infoPtr, &width, &height, NULL, NULL, NULL, NULL, NULL);
  imgWidth = width;
  imgHeight = height;

  unsigned int rowBytes = png_get_rowbytes(pngPtr, infoPtr);
  *data = (unsigned char*)malloc(rowBytes * imgHeight);
  png_bytepp rowPointers = png_get_rows(pngPtr, infoPtr);

  for (int i = 0; i < imgHeight; i++)
  {
    memcpy(*data + (rowBytes * (imgHeight - 1 - i)), rowPointers[i], rowBytes);
  }

  fclose(file);
  png_destroy_read_struct(&pngPtr, NULL, NULL);

  return true;
}
