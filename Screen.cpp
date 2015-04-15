#include "Screen.hpp"

#include "ExAssert.hpp"

namespace MyTracer
{
  Screen::Screen(int width, int height, bool fullscreen, std::string const &title)
  {
    mWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               width, height, fullscreen ? SDL_WINDOW_FULLSCREEN : 0);
    ExAssertInfo(mWindow, SDL_GetError());

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_SOFTWARE);
    ExAssertInfo(mRenderer, SDL_GetError());

    mTexture = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    ExAssertInfo(mTexture, SDL_GetError());

    mSurface = SDL_CreateRGBSurface(0, width, height, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
    ExAssertInfo(mSurface, SDL_GetError());
  }

  Screen::Screen(Screen &&other)
    : mWindow(other.mWindow), mRenderer(other.mRenderer), mSurface(other.mSurface)
  {
    other.mWindow = nullptr;
    other.mRenderer = nullptr;
    other.mSurface = nullptr;
  }

  Screen::~Screen()
  {
    if(mTexture)
    { SDL_DestroyTexture(mTexture); mTexture = nullptr; }

    if(mSurface)
    { SDL_FreeSurface(mSurface); mSurface = nullptr; }

    if(mRenderer)
    { SDL_DestroyRenderer(mRenderer); mRenderer = nullptr; }

    if(mWindow)
    { SDL_DestroyWindow(mWindow); mWindow = nullptr; }
  }

  void Screen::Present()
  {
    SDL_UpdateTexture(mTexture, nullptr, mSurface->pixels, mSurface->pitch);
    SDL_RenderCopy(mRenderer, mTexture, nullptr, nullptr);
    SDL_RenderPresent(mRenderer);
  }

  Eigen::Vector2i Screen::GetSize() const
  {
    int w, h;
    SDL_GetWindowSize(mWindow, &w, &h);
    return {w, h};
  }
}