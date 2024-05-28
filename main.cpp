#include <Windows.h>

#include "Window.h"

int CALLBACK WinMain(HINSTANCE app_instance, HINSTANCE previous_instance, LPSTR arguments, int arguments_count) {

  Window window(100, 100, 800, 600);

  Sleep(5000);
  return 0;
}