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

kdr::space::Mat4 kdr::space::lookAt(const kdr::space::Vec3& eye, const kdr::space::Vec3& target, const kdr::space::Vec3& up)
{
  kdr::space::Vec3 front = kdr::space::normalize(eye - target);
  kdr::space::Vec3 right = kdr::space::normalize(kdr::space::cross(up, front));
  kdr::space::Vec3 newUp = kdr::space::cross(front, right);
  kdr::space::Mat4 result;

  result[0][0] = right.x;
  result[1][0] = right.y;
  result[2][0] = right.z;
  result[0][1] = newUp.x;
  result[1][1] = newUp.y;
  result[2][1] = newUp.z;
  result[0][2] = front.x;
  result[1][2] = front.y;
  result[2][2] = front.z;
  result[3][0] = -kdr::space::dot(right, eye);
  result[3][1] = -kdr::space::dot(newUp, eye);
  result[3][2] = -kdr::space::dot(front, eye);
  result[3][3] = 1.f;

  return result;
}
