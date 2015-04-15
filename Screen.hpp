#pragma once

#include <string>
#include <Eigen/Eigen>

#include <SDL.h>

namespace MyTracer
{
  class Screen
  {
  public:
    Screen(int width, int height, bool fullscreen, std::string const &title);
    Screen(Screen const &) = delete;
    Screen(Screen &&other);
    virtual ~Screen();

    void Present();

    inline SDL_Window *GetWindow() { return mWindow; }
    inline operator SDL_Window* () { return GetWindow(); }

    inline SDL_Surface *GetSurface() { return mSurface; }
    inline operator SDL_Surface* () { return GetSurface(); }

    Eigen::Vector2i GetSize() const;
  protected:
    SDL_Window *mWindow = nullptr;
    SDL_Renderer *mRenderer = nullptr;
    SDL_Texture *mTexture = nullptr;
    SDL_Surface *mSurface = nullptr;
  };
}