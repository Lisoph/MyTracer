#pragma once

#include <Eigen/Eigen>

namespace MyTracer
{
  namespace Tracing
  {
    class SceneLight
    {
    public:
      SceneLight(Eigen::Vector3f const &position, Eigen::Vector3f const &diffuse)
        : mPosition(position), mDiffuse(diffuse)
      {}

      SceneLight(SceneLight const &other) = default;
      virtual ~SceneLight() = default;

      virtual float GetDiffuseContri(Eigen::Vector3f const &worldPoint, Eigen::Vector3f const &normal) = 0;

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