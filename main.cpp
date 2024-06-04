#include <Windows.h>

#include "Renderer.h"
#include "Triangle.h"
#include "Window.h"

int CALLBACK WinMain(HINSTANCE app_instance, HINSTANCE previous_instance, LPSTR arguments, int arguments_count) {

  /*
  AllocConsole();
  // requires #include <iostream> at the top of the file
  freopen("conin$", "r", stdin);
  freopen("conout$", "w", stdout);
  freopen("conout$", "w", stderr);
  */

  Window window(100, 100, 800, 600);
  Renderer renderer(window);

  Triangle triangle(renderer);

  MSG message = {0};
  while (true) {
    if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE)) {
      TranslateMessage(&message);
      DispatchMessage(&message);

      if (message.message == WM_QUIT) {
        break;
      }
    }

    // ...
    // our update code
    // ...

    renderer.beginFrame();

    triangle.draw(renderer);

    renderer.endFrame();
  }

  return 0;
}