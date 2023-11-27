#include "Kedarium/Color.hpp"

kdr::Color::RGB::RGB(const std::string& hexCode)
{
  if (hexCode.size() != 7 || hexCode[0] != '#')
  {
    std::cerr << "Invalid HEX code for RGB color: " << hexCode << "!\n";
  }

  std::istringstream iss(hexCode.substr(1));
  unsigned int hexValue;
  iss >> std::hex >> hexValue;

  if (iss.fail())
  {
    std::cerr << "Invalid HEX code for RGB color: " << hexCode << "!\n";
  }

  this->red = ((hexValue >> 16) & 0xFF) / 255.f;
  this->green = ((hexValue >> 8) & 0xFF) / 255.f;
  this->blue = (hexValue & 0xFF) / 255.f;
}

kdr::Color::RGBA::RGBA(const std::string& hexCode, const float alpha) : alpha(alpha)
{
  if (hexCode.size() != 7 || hexCode[0] != '#')
  {
    std::cerr << "Invalid HEX code for RGB color: " << hexCode << "!\n";
  }

  std::istringstream iss(hexCode.substr(1));
  unsigned int hexValue;
  iss >> std::hex >> hexValue;

  if (iss.fail())
  {
    std::cerr << "Invalid HEX code for RGB color: " << hexCode << "!\n";
  }

  this->red = ((hexValue >> 16) & 0xFF) / 255.f;
  this->green = ((hexValue >> 8) & 0xFF) / 255.f;
  this->blue = (hexValue & 0xFF) / 255.f;
}
