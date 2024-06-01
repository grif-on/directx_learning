#include "Renderer.h"


Renderer::Renderer(Window& window) {
  createDevice(window);
  createRenderTargetView();
}

void Renderer::createDevice(Window& window) {
  // Define swap chain
  DXGI_SWAP_CHAIN_DESC swap_chain_description = {0};

  swap_chain_description.OutputWindow      = window.getHandle();
  swap_chain_description.BufferCount       = 1;                                // enable double buffering
  swap_chain_description.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;       // each pixel is represented by 4 bytes
  swap_chain_description.BufferUsage       = DXGI_USAGE_RENDER_TARGET_OUTPUT;  // draw on surface
  swap_chain_description.SampleDesc.Count  = 1;                                // antialiasing stuff
  swap_chain_description.Windowed          = true;

  // Create swap chain , device and device context
  HRESULT result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
                                                 nullptr, 0, D3D11_SDK_VERSION, &swap_chain_description,
                                                 &swap_chain, &device, nullptr, &device_context);

  if (result != S_OK) {
    MessageBox(nullptr, "Failed to initialize DirectX11 swap chain", "Error", MB_OK);
    exit(1);
  }
}

void Renderer::createRenderTargetView() {
  ID3D11Texture2D* back_buffer = nullptr;
  swap_chain->GetBuffer(0 /*index of the buffer*/, __uuidof(ID3D11Texture2D), (void**)&back_buffer);
  device->CreateRenderTargetView(back_buffer, nullptr, &render_target_view);
  back_buffer->Release();
}

void Renderer::beginFrame() {
  // Set the background color
  float clearColor[] = {.25f, .5f, 1.0f, 1.0f};
  device_context->ClearRenderTargetView(render_target_view, clearColor);
}

void Renderer::endFrame() {
  // Swap the buffer
  swap_chain->Present(1 /*vsync stuff*/, 0);
}