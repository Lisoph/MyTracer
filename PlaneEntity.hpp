#pragma once

#include "SceneEntity.hpp"

namespace MyTracer
{
  namespace Tracing
  {
    class PlaneEntity: public SceneEntity
    {
    public:
      PlaneEntity(Eigen::Vector3f const &position, Eigen::Vector3f const &normal,
                  Eigen::Vector3f const &diffuse)
                  : SceneEntity(position, diffuse), mNormal(normal.normalized())
      {}

      IntersResult Intersects(Ray const &ray) override;

      Eigen::Vector3f GetNormalAt(Eigen::Vector3f const &relativePos) override
      { return mNormal; }

      Eigen::Vector3f GetDiffuseAt(Eigen::Vector3f const &relativePos) override;
      bool CanReflect() const override { return false; }
    protected:
      Eigen::Vector3f mNormal;
    };
  }
}