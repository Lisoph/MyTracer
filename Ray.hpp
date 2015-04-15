#pragma once

#include <Eigen/Eigen>

namespace MyTracer
{
  namespace Tracing
  {
    class Ray
    {
    public:
      Ray(Eigen::Vector3f const &origin, Eigen::Vector3f const &dir)
        : mOrigin(origin), mDir(dir)
      {}
      Ray(Ray const &other) = default;
      ~Ray() = default;

      inline Eigen::Vector3f const &GetOrigin() const
      { return mOrigin; }
      inline void SetOrigin(Eigen::Vector3f const &origin)
      { mOrigin = origin; }

      inline Eigen::Vector3f const &GetDir() const
      { return mDir; }
      inline void SetDir(Eigen::Vector3f const &dir)
      { mDir = dir; }
    protected:
      Eigen::Vector3f mOrigin;
      Eigen::Vector3f mDir;
    };
  }
}