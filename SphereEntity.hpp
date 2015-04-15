#pragma once

#include "SceneEntity.hpp"

namespace MyTracer
{
  namespace Tracing
  {
    class SphereEntity: public SceneEntity
    {
    public:
      SphereEntity(Eigen::Vector3f const &pos, float radius, Eigen::Vector3f const &color)
        : SceneEntity(pos, color), mRadius(radius)
      {}
      SphereEntity(SphereEntity const &other) = default;
      virtual ~SphereEntity() = default;

      IntersResult Intersects(Ray const &ray) override;
      Eigen::Vector3f GetNormalAt(Eigen::Vector3f const &relativePos) override;
    protected:
      float mRadius;
    };
  }
}