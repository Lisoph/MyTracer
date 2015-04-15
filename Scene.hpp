#pragma once

#include <vector>
#include <memory>

#include "SceneEntity.hpp"
#include "SceneLight.hpp"

namespace MyTracer
{
  namespace Tracing
  {
    class Scene
    {
    public:
      using EntityContainer = std::vector<std::unique_ptr<SceneEntity>>;
      using LightContainer = std::vector<std::unique_ptr<SceneLight>>;

      Eigen::Vector3f Trace(Ray const &startRay, unsigned iters);

      inline EntityContainer &GetEntities()
      { return mEntities; }

      inline LightContainer &GetLights()
      { return mLights; }
    protected:
      Eigen::Vector3f LightingForPoint(SceneEntity &hitEntity, Eigen::Vector3f const &hitWorldPoint);
      bool IsLightVisible(SceneLight &light, Eigen::Vector3f const &worldPoint);
    protected:
      EntityContainer mEntities;
      LightContainer mLights;
    };
  }
}