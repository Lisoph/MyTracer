#include "PointLight.hpp"

#include <cmath>

namespace MyTracer
{
  namespace Tracing
  {
    float PointLight::GetDiffuseContri(Eigen::Vector3f const &worldPoint, Eigen::Vector3f const &normal)
    {
      Eigen::Vector3f pointToLight = (mPosition - worldPoint).normalized();
      return std::max(pointToLight.dot(normal), 0.0f);
    }
  }
}