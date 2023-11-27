#include "Kedarium/Space.hpp"

kdr::space::Mat4 kdr::space::translate(const kdr::space::Mat4& mat, const kdr::space::Vec3& vec)
{
  kdr::space::Mat4 result {mat};
  result[3][0] += vec.x;
  result[3][1] += vec.y;
  result[3][2] += vec.z;
  return result;
}

kdr::space::Mat4 kdr::space::perspective(const float fov, const float aspect, const float near, const float far)
{
  kdr::space::Mat4 result;
  const float halfTanFOV = tanf(kdr::space::radians(fov)) / 2.f;

  result[0][0] = 1.f / (halfTanFOV * aspect);
  result[1][1] = 1.f / halfTanFOV;
  result[2][2] = (far + near) / (near - far);
  result[2][3] = -1.f;
  result[3][2] = -(2.f * far * near) / (far - near);

  return result;
}
