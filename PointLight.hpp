#include "SceneLight.hpp"

namespace MyTracer
{
  namespace Tracing
  {
    class PointLight: public SceneLight
    {
    public:
      PointLight(Eigen::Vector3f const &position, Eigen::Vector3f const &diffuse)
        : SceneLight(position, diffuse)
      {}

      PointLight(PointLight const &other) = default;
      virtual ~PointLight() = default;

      float GetDiffuseContri(Eigen::Vector3f const &worldPoint, Eigen::Vector3f const &normal) override;
    };
  }
}