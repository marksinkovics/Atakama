#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Window.hpp"

#include <stdint.h>

namespace OGLSample {

class Application
{
public:

  static constexpr uint32_t WIDTH = 1024;
  static constexpr uint32_t HEIGHT = 768;

  Application();
  ~Application();

  Application(const Application&) = delete;
  Application &operator=(const Application&) = delete;

  void run();
private:
  Scope<Window> m_Window;
};

}

#endif
