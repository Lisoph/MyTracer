#pragma once

#include <Eigen/Eigen>
#include <utility>

#include "Ray.hpp"

namespace MyTracer
{
  namespace Tracing
  {
    class SceneEntity
    {
    public:
      using IntersResult = std::pair<bool, Eigen::Vector3f>;

      SceneEntity() = delete;
      SceneEntity(Eigen::Vector3f const &pos, Eigen::Vector3f const &diffuse)
        : mPosition(pos), mDiffuse(diffuse)
      {}
      virtual ~SceneEntity() {}

      virtual IntersResult Intersects(Ray const &ray) = 0;
      virtual Eigen::Vector3f GetNormalAt(Eigen::Vector3f const &relativePos) = 0;

      virtual Eigen::Vector3f GetDiffuseAt(Eigen::Vector3f const &relativePos) { return mDiffuse; }
      virtual bool CanReflect() const { return true; }

      inline Eigen::Vector3f const &Position() const
      { return mPosition; }
      inline void Position(Eigen::Vector3f const &position)
      { mPosition = position; }

      inline Eigen::Vector3f const &Diffuse() const
      { return mDiffuse; }
      inline void Diffuse(Eigen::Vector3f const &diffuse)
      { mDiffuse = diffuse; }
    protected:
      Eigen::Vector3f mPosition;
      Eigen::Vector3f mDiffuse;
    };
  }
}