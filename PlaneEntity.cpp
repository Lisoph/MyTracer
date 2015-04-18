#include "PlaneEntity.hpp"

#include <SDL.h>

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
      Eigen::Vector3f texturePlaneOrtho = Eigen::Vector3f::UnitZ();     // The normal vector that is orthogonal to the 2D 'texture' plane.
      Eigen::Vector3f rotationAxis = mNormal.cross(texturePlaneOrtho);  // It determines on which axes the relativePos should be projected on.
      
      float angle = std::acos(mNormal.dot(texturePlaneOrtho));
      Eigen::Matrix4f rotMat = QuatRotMatrix4(Eigen::Quaternionf(Eigen::AngleAxisf(angle, rotationAxis)));

      float const extraRot = SDL_GetTicks() / 1000.0f * 0.05f;
      auto const extraRotMat = QuatRotMatrix4(Eigen::Quaternionf(Eigen::AngleAxisf(extraRot, Eigen::Vector3f::UnitY())));
      rotMat *= extraRotMat;

      auto v4 = Eigen::Vector4f(relativePos(0), relativePos(1), relativePos(2), 1);
      auto vnew = rotMat * v4;

      auto x = int(std::round(vnew(0) / 4));
      auto y = int(std::round(vnew(1) / 4));

      if((x + y) % 2 == 0)
        return {0, 1, 0};
      return {1, 1, 0};
    }
  }
}