#include <memory>

#include <SDL.h>

#include "Application.hpp"

void ClearSurface(SDL_Surface *surf)
{
  Uint32 *pixels = (Uint32*)surf->pixels;

  int const max = surf->w * surf->h;
  for(int i = 0; i < max; ++i)
  {
    pixels[i] = 0xFF0000FF;
  }
}

int main(int argc, char **argv)
{
  using namespace MyTracer;

  SDL_Init(SDL_INIT_VIDEO);

  Application *appPtr = nullptr;

  try
  {
    Application app;
    appPtr = &app;
    app.Run();
  }
  catch(std::exception &ex)
  {
    SDL_Window *msgBoxWin = (appPtr ? appPtr->GetScreen().GetWindow() : nullptr);
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Critical error!", ex.what(), msgBoxWin);
  }

  SDL_Quit();
  return 0;
}