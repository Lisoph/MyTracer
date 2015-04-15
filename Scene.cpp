#include "Scene.hpp"

#include <SDL.h>

static Eigen::Vector3f Reflect(Eigen::Vector3f const &vec, Eigen::Vector3f &normal)
{ return vec - ((normal * vec.normalized().dot(normal)) * 2); }

namespace MyTracer
{
  namespace Tracing
  {
    Eigen::Vector3f Scene::Trace(Ray const &startRay, unsigned iters)
    {
      //Eigen::Vector3f finalColor;
      Eigen::Vector3f finalColor{1, 1, 1};
      unsigned i;

      Ray ray = startRay;

      for(i = 0; i < iters; ++i)
      {
        float closestHitDist = 9999999999.0f;
        SceneEntity *closestEntity = nullptr;
        Eigen::Vector3f closestHitPos;

        // Find closest hit entity
        for(auto &ent : mEntities)
        {
          auto inters = ent->Intersects(ray);

          if(inters.first)
          {
            float dist = inters.second.norm();

            if(dist < closestHitDist)
            {
              closestHitDist = dist;
              closestEntity = ent.get();
              closestHitPos = inters.second;
            }
          }
        }

        if(!closestEntity)
          break;

        if(!closestEntity->CanReflect())
        {
          finalColor = LightingForPoint(*closestEntity, closestHitPos);
          ++i;
          break;
        }

        finalColor = finalColor.cwiseProduct(LightingForPoint(*closestEntity, closestHitPos));
        
        auto relativeHitPos = closestHitPos - closestEntity->Position();
        ray.SetOrigin(closestHitPos);
        ray.SetDir(Reflect(ray.GetDir(), closestEntity->GetNormalAt(relativeHitPos)).normalized());
      }

      if(i <= 0)
        return{0.2f, 0.4f, 0.8f};

      return finalColor /*/ (float)i*/;
    }

    Eigen::Vector3f Scene::LightingForPoint(SceneEntity &hitEntity, Eigen::Vector3f const &hitWorldPoint)
    {
      Eigen::Vector3f relativePoint = hitWorldPoint - hitEntity.Position();
      Eigen::Vector3f normal = hitEntity.GetNormalAt(relativePoint);
      Eigen::Vector3f totalColor {0, 0, 0};
      int i = 0;

      for(auto &light : mLights)
      {
        float diffuseContri = light->GetDiffuseContri(hitWorldPoint, normal);
        Eigen::Vector3f diffuse = (hitEntity.GetDiffuseAt(relativePoint) + light->Diffuse()) * diffuseContri;

        bool lightVisible = IsLightVisible(*light, hitWorldPoint);
        
        Eigen::Vector3f color = (diffuse /* + specular + ambient ... */) * (lightVisible ? 1.0f : 0.2f);
        //totalColor = totalColor.cwiseProduct(color);

        totalColor += color;
        ++i;
      }

      return totalColor / (float)i;
    }

    bool Scene::IsLightVisible(SceneLight &light, Eigen::Vector3f const &worldPoint)
    {
      Eigen::Vector3f pointToLight = (light.Position() - worldPoint).normalized();
      Ray ray{worldPoint, pointToLight};

      for(auto &ent : mEntities)
      {
        if(ent->Intersects(ray).first)
          return false;
      }

      return true;
    }
  }
}