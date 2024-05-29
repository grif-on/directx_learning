#include <Windows.h>

#include "Window.h"

int CALLBACK WinMain(HINSTANCE app_instance, HINSTANCE previous_instance, LPSTR arguments, int arguments_count) {

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