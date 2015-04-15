#pragma once

#include "Screen.hpp"
#include "Tracer.hpp"

namespace MyTracer
{
  class Application
  {
  public:
    Application() = default;
    Application(Application const &) = delete;
    virtual ~Application() = default;

    void Run();

    inline void Quit() { mRunning = false; }

    inline Screen &GetScreen() { return mScreen; }
    inline operator Screen& () { return GetScreen(); }
  private:
    void PollEvents();
  protected:
    bool mRunning = true;
    Screen mScreen{1280, 720, false, "MyTracer"};
    Tracing::Tracer mTracer;
  };
}