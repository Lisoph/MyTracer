#include "SphereEntity.hpp"

namespace MyTracer
{
  namespace Tracing
  {
    SceneEntity::IntersResult SphereEntity::Intersects(Ray const &ray)
    {
      float t0/*, t1*/;
      Eigen::Vector3f L = mPosition - ray.GetOrigin();
      float tca = L.dot(ray.GetDir());
      if(tca < 0) return {false, {}};
      float d2 = L.dot(L) - tca * tca;
      if(d2 > mRadius * 2) return {false, {}};
      float thc = std::sqrt(mRadius * 2 - d2);
      t0 = tca - thc;
      //t1 = tca + thc;

      Eigen::Vector3f P = ray.GetOrigin() + t0 * ray.GetDir();
      return {true, P};
    }

    Eigen::Vector3f SphereEntity::GetNormalAt(Eigen::Vector3f const &relativePos) 
    {
      return relativePos.normalized();
    }
  }
}