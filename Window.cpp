#include "Window.h"

LRESULT CALLBACK windowProcessing(HWND handle, UINT message, WPARAM w_param, LPARAM l_param) {

  switch (message) {
    case WM_CLOSE:
    case WM_DESTROY:

      PostQuitMessage(0);

      return 0;
  }

  return DefWindowProc(handle, message, w_param, l_param);
}

Window::Window(int screen_x, int screen_y, int width, int height) {
  WNDCLASS window_class      = {0};
  window_class.style         = CS_OWNDC;
  window_class.lpfnWndProc   = windowProcessing;
  window_class.hCursor       = LoadCursor(nullptr, IDC_ARROW);
  window_class.lpszClassName = (LPCSTR) "DirectXLearing";
  RegisterClass(&window_class);

  handle = CreateWindow((LPCSTR) "DirectXLearing", (LPCSTR) "DirectX learning",
                        WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
                        screen_x, screen_y, width, height,
                        nullptr, nullptr, nullptr, nullptr);
}