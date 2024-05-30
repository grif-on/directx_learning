#pragma once

#include <Windows.h>

class Window {
public:
  Window(int screen_x, int screen_y, int width, int height);
  HWND getHandle() { return handle; }

private:
  HWND handle;
};