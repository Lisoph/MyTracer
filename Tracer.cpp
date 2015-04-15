#include "Tracer.hpp"

#include <SDL.h>
#include <sstream>

using namespace Eigen;

static const float Pi = 3.14159265359f;

namespace MyTracer
{
  namespace Tracing
  {
    Vector3f Tracer::TracePixel(int x, int y, int width, int height)
    {
      Ray startRay = GenPixelRay((float)x, (float)y, (float)width, (float)height);
      return mScene.Trace(startRay, 512);
    }

    Ray Tracer::GenPixelRay(float x, float y, float width, float height)
    {
      float fovx = Pi / 4;
      float fovy = (height / width) * fovx;

      float xDir = (2 * x - width) / width * std::tan(fovx);
      float yDir = (height - 2 * y) / height * std::tan(fovy);

      return {Eigen::Vector3f::Zero(), Eigen::Vector3f(xDir, yDir, 1).normalized()};

      /*float const hw = width / 2;
      float const hh = height / 2;
      float xDir = (x - hw) / hw;
      float yDir = (hh - y) / hh;

      Eigen::Vector3f dir = (Eigen::Vector3f(xDir, yDir, 0) - Eigen::Vector3f(0, 0, -10)).normalized();

      return {Eigen::Vector3f::Zero(), {dir}};*/
    }
  }
}