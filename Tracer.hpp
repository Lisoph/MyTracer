#pragma once

#include "Scene.hpp"

#include <Eigen/Eigen>

namespace MyTracer
{
  namespace Tracing
  {
    class Tracer
    {
    public:
      Eigen::Vector3f TracePixel(int x, int y, int width, int height);

      inline Scene &GetScene()
      { return mScene; }
    protected:
      Ray GenPixelRay(float x, float y, float width, float height);
    protected:
      Scene mScene;
    };
  }
}