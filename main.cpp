#include <Windows.h>

#include "Window.h"

int CALLBACK WinMain(HINSTANCE app_instance, HINSTANCE previous_instance, LPSTR arguments, int arguments_count) {
  
  //AllocConsole();
  //// requires #include <iostream> at the top of the file
  //freopen("conin$", "r", stdin);
  //freopen("conout$", "w", stdout);
  //freopen("conout$", "w", stderr);

  Window window(100, 100, 800, 600);

  MSG message = {0};
  while (true) {
    if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE)) {
      TranslateMessage(&message);
      DispatchMessage(&message);

      if (message.message == WM_QUIT) {
        break;
      }
    }
  }

  return 0;
}