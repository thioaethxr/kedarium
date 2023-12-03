#include "Kedarium/Space.hpp"

kdr::space::Mat4 kdr::space::translate(const kdr::space::Mat4& mat, const kdr::space::Vec3& vec)
{
  kdr::space::Mat4 result {mat};
  result[3][0] += vec.x;
  result[3][1] += vec.y;
  result[3][2] += vec.z;
  return result;
}

kdr::space::Mat4 kdr::space::rotate(const kdr::space::Mat4& mat, const float angle, const kdr::space::Vec3& axis)
{
  const kdr::space::Vec3 normalizedAxis = kdr::space::normalize(axis);
  float cosTheta = std::cos(kdr::space::radians(angle));
  float sinTheta = std::sin(kdr::space::radians(angle));
  float oneMinusCosTheta = 1 - cosTheta;
  kdr::space::Mat4 viewMatrix {mat};

  viewMatrix[0][0] = cosTheta + normalizedAxis.x * normalizedAxis.x * oneMinusCosTheta;
  viewMatrix[0][1] = normalizedAxis.x * normalizedAxis.y * oneMinusCosTheta - normalizedAxis.z * sinTheta;
  viewMatrix[0][2] = normalizedAxis.x * normalizedAxis.z * oneMinusCosTheta + normalizedAxis.y * sinTheta;
  viewMatrix[1][0] = normalizedAxis.y * normalizedAxis.x * oneMinusCosTheta + normalizedAxis.z * sinTheta;
  viewMatrix[1][1] = cosTheta + normalizedAxis.y * normalizedAxis.y * oneMinusCosTheta;
  viewMatrix[1][2] = normalizedAxis.y * normalizedAxis.z * oneMinusCosTheta - normalizedAxis.x * sinTheta;
  viewMatrix[2][0] = normalizedAxis.z * normalizedAxis.x * oneMinusCosTheta - normalizedAxis.y * sinTheta;
  viewMatrix[2][1] = normalizedAxis.z * normalizedAxis.y * oneMinusCosTheta + normalizedAxis.x * sinTheta;
  viewMatrix[2][2] = cosTheta + normalizedAxis.z * normalizedAxis.z * oneMinusCosTheta;

  return viewMatrix * mat;
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
