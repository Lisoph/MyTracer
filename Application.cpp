#include "Application.hpp"

#include "SphereEntity.hpp"
#include "PlaneEntity.hpp"
#include "PointLight.hpp"

template <typename T>
inline T Clamp(T min, T max, T val)
{ return val < min ? min : val > max ? max : val; }

inline Uint32 Vec3ToColor(Eigen::Vector3f const &vec)
{
  auto r = Uint32(Clamp(0.0f, 1.0f, vec(0)) * 255);
  auto g = Uint32(Clamp(0.0f, 1.0f, vec(1)) * 255);
  auto b = Uint32(Clamp(0.0f, 1.0f, vec(2)) * 255);
  return (r << 24) | (g << 16) | (b << 8) | 0xFF;
}

namespace MyTracer
{
  void Application::Run()
  {
    Tracing::SceneEntity *foo = new Tracing::SphereEntity({-20, 10, 60}, 50, {0.5f, 0, 0});
    Tracing::PointLight *light = new Tracing::PointLight({0, 20, 0}, {0.5f, 0.5f, 0.5f});

    mTracer.GetScene().GetEntities().emplace_back(foo);
    mTracer.GetScene().GetEntities().emplace_back(new Tracing::SphereEntity({20, 1, 60}, 50, {0, 0.5f, 0}));
    mTracer.GetScene().GetEntities().emplace_back(new Tracing::PlaneEntity({0, -20, 60}, {0, 1, 0}, {0.5f, 0.5f, 0.5f}));

    mTracer.GetScene().GetLights().emplace_back(light);

    float rot = 0;

    while(mRunning)
    {
      Uint32 timeStart = SDL_GetTicks();

      PollEvents();

      Eigen::Vector3f basePos{-20, 10, 60};
      Eigen::Vector3f lightBasePos{0, 60, 0};

      foo->Position(basePos + Eigen::Vector3f{0, std::cos(rot) * -2, 0});
      light->Position(lightBasePos + Eigen::Vector3f{std::cos(rot) * 50, 0, 0});

      rot += 0.1f;

      auto const res = mScreen.GetSize();
      auto const width = res(0);
      auto const height = res(1);

      Uint32 *pixels = (Uint32*)mScreen.GetSurface()->pixels;

#pragma omp parallel for
      for(int y = 0; y < height; ++y)
      {
        for(int x = 0; x < width; ++x)
        {
          auto color = mTracer.TracePixel(x, y, width, height);
          pixels[width * y + x] = Vec3ToColor(color);
        }
      }

      mScreen.Present();

      Uint32 frameTime = SDL_GetTicks() - timeStart;
      if(frameTime < 16)
        SDL_Delay(16 - frameTime);
    }
  }

  void Application::PollEvents()
  {
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
      if(event.type == SDL_QUIT)
        Quit();
      else if(event.type == SDL_KEYDOWN)
      {
        if(event.key.keysym.sym == SDLK_ESCAPE)
          Quit();
      }
    }
  }
}