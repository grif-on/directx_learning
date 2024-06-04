#pragma once

#include <d3d11.h>

#include "Window.h"

class Renderer {
public:
  Renderer(Window& window);
  void beginFrame();
  void endFrame();
  ID3D11Device* getDevice() { return device; }
  ID3D11DeviceContext* getDeviceContext() { return device_context; }

private:
  void createDevice(Window& window);
  void createRenderTargetView();

  IDXGISwapChain* swap_chain          = nullptr;
  ID3D11Device* device                = nullptr;
  ID3D11DeviceContext* device_context = nullptr;

  ID3D11RenderTargetView* render_target_view = nullptr;  // aka surface/texture
};
