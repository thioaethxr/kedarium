#ifndef KDR_SPACE_HPP
#define KDR_SPACE_HPP

namespace kdr
{
  namespace space
  {
    class Vec3
    {
      public:
        float x {0.f};
        float y {0.f};
        float z {0.f};

        /**
         * Constructs a Vec3 with specified x, y, and z components.
         *
         * @param x The x-component of the vector.
         * @param y The y-component of the vector.
         * @param z The z-component of the vector.
         */
        Vec3(const float x, const float y, const float z)
        : x(x), y(y), z(z)
        {}
        /**
         * Constructs a Vec3 with all components set to the same scalar value.
         *
         * @param scalar The scalar value to set for all components.
         */
        Vec3(const float scalar)
        : x(scalar), y(scalar), z(scalar)
        {}

        /**
         * Overloaded addition operator for Vec3.
         *
         * @param vec The vector to add.
         * @return A new Vec3 representing the sum of the two vectors.
         */
        Vec3 operator+(const Vec3& vec)
        {
          return Vec3(
            this->x + vec.x,
            this->y + vec.y,
            this->z + vec.z
          );
        }
        /**
         * Overloaded subtraction operator for Vec3.
         *
         * @param vec The vector to subtract.
         * @return A new Vec3 representing the difference between the two vectors.
         */
        Vec3 operator-(const Vec3& vec)
        {
          return Vec3(
            this->x - vec.x,
            this->y - vec.y,
            this->z - vec.z
          );
        }
    };
  }
}

#endif // KDR_SPACE_HPP
