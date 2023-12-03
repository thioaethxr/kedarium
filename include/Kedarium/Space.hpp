#ifndef KDR_SPACE_HPP
#define KDR_SPACE_HPP

#include <cmath>
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
    { return degrees * kdr::space::PI / 180.f; }

    /**
     * 2D vector class representing a point or direction in 2D space.
     */
    class Vec2
    {
      public:
        float x {0.f};
        float y {0.f};

        /**
         * Constructs a Vec2 with specified x and y components.
         *
         * @param x The x-component of the vector.
         * @param y The y-component of the vector.
         */
        Vec2(const float x, const float y)
        : x(x), y(y)
        {}
        /**
         * Constructs a Vec2 with all components set to the same scalar value.
         *
         * @param scalar The scalar value to set for all components.
         */
        Vec2(const float scalar)
        : x(scalar), y(scalar)
        {}

        /**
         * Overloaded addition operator for Vec2.
         *
         * @param vec The vector to add.
         * @return A new Vec2 representing the sum of the two vectors.
         */
        Vec2 operator+(const Vec2& vec) const
        {
          return Vec2(
            this->x + vec.x,
            this->y + vec.y
          );
        }
        /**
         * Overloaded subtraction operator for Vec2.
         *
         * @param vec The vector to subtract.
         * @return A new Vec2 representing the difference between the two vectors.
         */
        Vec2 operator-(const Vec2& vec) const
        {
          return Vec2(
            this->x - vec.x,
            this->y - vec.y
          );
        }
        /**
         * Multiplies a 2D vector by a scalar.
         *
         * @param scalar The scalar value to multiply the vector by.
         * @return The resulting vector after multiplication.
         */
        Vec2 operator*(float scalar) const
        {
          return Vec2(
            this->x * scalar,
            this->y * scalar
          );
        }
        /**
         * Adds another 2D vector to the current vector in-place.
         *
         * @param vec The vector to be added.
         * @return Reference to the modified current vector.
         */
        Vec2& operator+=(const Vec2& vec)
        {
          this->x += vec.x;
          this->y += vec.y;
          return *this;
        }
        /**
         * Subtracts another 2D vector from the current vector in-place.
         *
         * @param vec The vector to be subtracted.
         * @return Reference to the modified current vector.
         */
        Vec2& operator-=(const Vec2& vec)
        {
          this->x -= vec.x;
          this->y -= vec.y;
          return *this;
        }
    };

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
        Vec3 operator+(const Vec3& vec) const
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
        Vec3 operator-(const Vec3& vec) const
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
        Vec3 operator*(float scalar) const
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
     * Normalizes a 2D vector.
     *
     * @param vec The 2D vector to be normalized.
     * @return A normalized 2D vector.
     */
    inline kdr::space::Vec2 normalize(const kdr::space::Vec2& vec)
    {
      const float length = std::sqrt(vec.x * vec.x + vec.y * vec.y);
      return length > 0.f ? kdr::space::Vec2 {
        vec.x / length,
        vec.y / length
      } : kdr::space::Vec2 {0.f};
    }
    /**
     * Normalizes a 3D vector.
     *
     * @param vec The 3D vector to be normalized.
     * @return A normalized 3D vector.
     */
    inline kdr::space::Vec3 normalize(const kdr::space::Vec3& vec)
    {
      const float length = std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
      return length > 0.f ? kdr::space::Vec3 {
        vec.x / length,
        vec.y / length,
        vec.z / length,
      } : kdr::space::Vec3 {0.f};
    }
    /**
     * Computes the dot product of two 2D vectors.
     *
     * @param vecA The first 2D vector.
     * @param vecB The second 2D vector.
     * @return The dot product of the two vectors.
     */
    inline float dot(const kdr::space::Vec2& vecA, const kdr::space::Vec2& vecB)
    { return vecA.x * vecB.x + vecA.y * vecB.y; }
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
    /**
     * Creates a view matrix to simulate a camera looking at a target.
     *
     * @param eye The position of the camera.
     * @param target The point the camera is looking at.
     * @param up The up vector of the camera.
     * @return The view matrix.
     */
    kdr::space::Mat4 lookAt(const kdr::space::Vec3& eye, const kdr::space::Vec3& target, const kdr::space::Vec3& up);
  }
}

#endif // KDR_SPACE_HPP
