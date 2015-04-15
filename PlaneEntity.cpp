#include "PlaneEntity.hpp"

static Eigen::Matrix4f Mat3to4(Eigen::Matrix3f const &mat3)
{
  Eigen::Matrix4f mat4 = Eigen::Matrix4f::Identity();
  mat4.block(0, 0, 3, 3) = mat3.block(0, 0, 3, 3);
  return mat4;
}

static Eigen::Matrix4f QuatRotMatrix4(Eigen::Quaternionf const &quat)
{
  return Mat3to4(quat.toRotationMatrix());
}

namespace MyTracer
{
  namespace Tracing
  {
    SceneEntity::IntersResult PlaneEntity::Intersects(Ray const &ray)
    {
      float denom = mNormal.dot(ray.GetDir());
      if(std::abs(denom) > 0.0001f)
      {
        Eigen::Vector3f p0l0 = mPosition - ray.GetOrigin();
        float t = p0l0.dot(mNormal) / denom;
        //return (t >= 0);
        if(t >= 0.0001f)
        {
          return {true, {ray.GetOrigin() + ray.GetDir() * t}};
        }
        return {false, {}};
      }

      return {false, {}};
    }

    Eigen::Vector3f PlaneEntity::GetDiffuseAt(Eigen::Vector3f const &relativePos)
    {
      //return mDiffuse;

#if 1
      Eigen::Vector3f a = mNormal;
      Eigen::Vector3f b = Eigen::Vector3f::UnitZ();

      Eigen::Vector3f v = a.cross(b);
      
      float c = a.dot(b);
      float angle = std::acos(c);

      Eigen::Matrix4f rotMat = QuatRotMatrix4(Eigen::Quaternionf(Eigen::AngleAxisf(angle, Eigen::Vector3f(v))));
      rotMat *= QuatRotMatrix4(Eigen::Quaternionf(Eigen::AngleAxisf(1.0f, Eigen::Vector3f(0, 1, 0))));
      auto v4 = Eigen::Vector4f(relativePos(0), relativePos(1), relativePos(2), 1);
      auto vnew = rotMat * v4;

      auto x = int(std::round(vnew(0) / 4));
      auto y = int(std::round(vnew(1) / 4));

      if(x % 2 == 0 && y % 2 == 0)
        return {0, 1, 0};
      return {1, 1, 0};
#endif
    }
  }
}