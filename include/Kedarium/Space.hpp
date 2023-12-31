#ifndef KDR_SPACE_HPP
#define KDR_SPACE_HPP

#include <math.h>
#include <cstring>

namespace kdr
{
  namespace space
  {
    /**
     * Constant representing the mathematical constant PI.
     */
    const float PI {3.141593f};

    /**
     * Converts degrees to radians.
     *
     * @param degrees The angle in degrees to be converted.
     * @return The equivalent angle in radians.
     */
    inline float radians(const float degrees)
    { return degrees * 180 / kdr::space::PI; }

    /**
     * 3D vector class representing a point or direction in 3D space.
     */
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
        /**
         * Multiplies a 3D vector by a scalar.
         *
         * @param scalar The scalar value to multiply the vector by.
         * @return The resulting vector after multiplication.
         */
        Vec3 operator*(float scalar)
        {
          return Vec3(
            this->x * scalar,
            this->y * scalar,
            this->z * scalar
          );
        }
        /**
         * Adds another 3D vector to the current vector in-place.
         *
         * @param vec The vector to be added.
         * @return Reference to the modified current vector.
         */
        Vec3& operator+=(const Vec3& vec)
        {
          this->x += vec.x;
          this->y += vec.y;
          this->z += vec.z;
          return *this;
        }
        /**
         * Subtracts another 3D vector from the current vector in-place.
         *
         * @param vec The vector to be subtracted.
         * @return Reference to the modified current vector.
         */
        Vec3& operator-=(const Vec3& vec)
        {
          this->x -= vec.x;
          this->y -= vec.y;
          this->z -= vec.z;
          return *this;
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
        /**
         * Overloaded multiplication operator for matrix multiplication.
         *
         * @param mat The matrix to be multiplied with.
         * @return The result of the matrix multiplication.
         */
        Mat4 operator*(const Mat4& mat)
        {
          Mat4 result;
          for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
              for (int k = 0; k < 4; k++) {
                result[i][j] += mat[i][k] * elements[k][j];
              }
            }
          }
          return result;
        }

      private:
        float elements[4][4];
    };

    /**
     * Computes the dot product of two 3D vectors.
     *
     * @param vecA The first 3D vector.
     * @param vecB The second 3D vector.
     * @return The dot product of the two vectors.
     */
    inline float dot(const kdr::space::Vec3& vecA, const kdr::space::Vec3& vecB)
    { return vecA.x * vecB.x + vecA.y * vecB.y + vecA.z * vecB.z; }
    /**
     * Computes the cross product of two 3D vectors.
     *
     * @param vecA The first 3D vector.
     * @param vecB The second 3D vector.
     * @return The cross product of the two vectors.
     */
    inline kdr::space::Vec3 cross(const kdr::space::Vec3& vecA, const kdr::space::Vec3& vecB)
    {
      return kdr::space::Vec3 {
        vecA.y * vecB.z - vecA.z * vecB.y,
        vecA.z * vecB.x - vecA.x * vecB.z,
        vecA.x * vecB.y - vecA.y * vecB.x
      };
    }

    /**
     * Gets a pointer to the first element of the matrix data.
     *
     * @param mat The matrix for which the pointer is obtained.
     * @return A pointer to the first element of the matrix data.
     */
    inline const float* valuePointer(const kdr::space::Mat4& mat)
    { return &mat[0][0]; }
    /**
     * Translates a 4x4 matrix by a 3D vector.
     *
     * @param mat The input 4x4 matrix.
     * @param vec The translation vector.
     * @return The resulting translated matrix.
     */
    kdr::space::Mat4 translate(const kdr::space::Mat4& mat, const kdr::space::Vec3& vec);
    /**
     * Creates a perspective projection matrix.
     *
     * @param fov The field of view angle in degrees.
     * @param aspect The aspect ratio of the viewport (width/height).
     * @param near The distance to the near clipping plane.
     * @param far The distance to the far clipping plane.
     * @return The resulting perspective projection matrix.
     */
    kdr::space::Mat4 perspective(const float fov, const float aspect, const float near, const float far);
  }
}

#endif // KDR_SPACE_HPP
