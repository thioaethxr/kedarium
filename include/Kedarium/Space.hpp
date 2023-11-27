#ifndef KDR_SPACE_HPP
#define KDR_SPACE_HPP

#include <cstring>

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

    /**
     * 4x4 matrix class for representing transformations in 3D space.
     */
    class Mat4
    {
      public:
        /**
         * Default constructor. Initializes the matrix to the zero matrix.
         */
        Mat4()
        {
          memset(this->elements, 0.f, sizeof(this->elements));
        }
        /**
         * Constructs a diagonal matrix with the specified diagonal number.
         *
         * @param diagonalNumber The value to set on the diagonal elements.
         */
        Mat4(const float diagonalNumber)
        {
          memset(this->elements, 0.f, sizeof(this->elements));
          for (int i = 0; i < 4; i++)
          {
            this->elements[i][i] = diagonalNumber;
          }
        }

        /**
         * Overloaded indexing operator for accessing matrix elements.
         *
         * @param i The row index.
         * @return A pointer to the specified row of matrix elements.
         */
        float* operator[](int i)
        { return this->elements[i]; }
        /**
         * Overloaded const indexing operator for accessing matrix elements.
         *
         * @param i The row index.
         * @return A const pointer to the specified row of matrix elements.
         */
        const float* operator[](int i) const
        { return this->elements[i]; }

      private:
        float elements[4][4];
    };

    /**
     * Gets a pointer to the first element of the matrix data.
     *
     * @param mat The matrix for which the pointer is obtained.
     * @return A pointer to the first element of the matrix data.
     */
    const float* valuePointer(const kdr::space::Mat4& mat)
    { return &mat[0][0]; }
  }
}

#endif // KDR_SPACE_HPP
