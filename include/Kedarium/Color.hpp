#ifndef KDR_COLOR_HPP
#define KDR_COLOR_HPP

#include <sstream>
#include <iostream>
#include <string>
#include <stdint.h>

namespace kdr
{
  namespace Color
  {
    /**
     * Struct representing an RGB color.
     */
    struct RGB
    {
      float red;
      float green;
      float blue;

      /**
       * Constructs an RGB color from 8-bit components.
       *
       * @param red The red component (0-255).
       * @param green The green component (0-255).
       * @param blue The blue component (0-255).
       */
      RGB(
        const uint8_t red,
        const uint8_t green,
        const uint8_t blue
      ) : red(red / 255.f), green(green / 255.f), blue(blue / 255.f)
      {}
      /**
       * Constructs an RGB color from a hexadecimal code.
       *
       * @param hexCode The hexadecimal color code.
       */
      RGB(const std::string& hexCode);
    };

    /**
     * Struct representing an RGBA color.
     */
    struct RGBA
    {
      float red;
      float green;
      float blue;
      float alpha;

      /**
       * Constructs an RGBA color from 8-bit components.
       *
       * @param red The red component (0-255).
       * @param green The green component (0-255).
       * @param blue The blue component (0-255).
       * @param alpha The alpha component (0.0-1.0).
       */
      RGBA(
        const uint8_t red,
        const uint8_t green,
        const uint8_t blue,
        const float alpha
      ) : red(red / 255.f), green(green / 255.f), blue(blue / 255.f), alpha(alpha)
      {}
      /**
       * Constructs an RGBA color from a hexadecimal code and alpha value.
       *
       * @param hexCode The hexadecimal color code.
       * @param alpha The alpha component (0.0-1.0).
       */
      RGBA(const std::string& hexCode, const float alpha);
    };

    /**
     * Predefined white RGBA color.
     */
    inline const kdr::Color::RGBA White {255, 255, 255, 1.f};
    /**
     * Predefined black RGBA color.
     */
    inline const kdr::Color::RGBA Black {0, 0, 0, 1.f};
    /**
     * Predefined red RGBA color.
     */
    inline const kdr::Color::RGBA Red {255, 0, 0, 1.f};
    /**
     * Predefined green RGBA color.
     */
    inline const kdr::Color::RGBA Green {0, 255, 0, 1.f};
    /**
     * Predefined blue RGBA color.
     */
    inline const kdr::Color::RGBA Blue {0, 0, 255, 1.f};
    /**
     * Predefined yellow RGBA color.
     */
    inline const kdr::Color::RGBA Yellow {255, 255, 0, 1.f};
    /**
     * Predefined cyan RGBA color.
     */
    inline const kdr::Color::RGBA Cyan {0, 255, 255, 1.f};
    /**
     * Predefined magenta RGBA color.
     */
    inline const kdr::Color::RGBA Magenta {255, 0, 255, 1.f};
  }
}

#endif // KDR_COLOR_HPP
