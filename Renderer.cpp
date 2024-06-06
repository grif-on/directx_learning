#include "Renderer.h"
#include "Panic.h"


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

  PANIC(result != S_OK, "Failed to initialize DirectX11 swap chain");
}

void Renderer::createRenderTargetView() {
  ID3D11Texture2D* back_buffer = nullptr;
  swap_chain->GetBuffer(0 /*index of the buffer*/, __uuidof(ID3D11Texture2D), (void**)&back_buffer);
  device->CreateRenderTargetView(back_buffer, nullptr, &render_target_view);
  back_buffer->GetDesc(&back_buffer_description);
  back_buffer->Release();
}

void Renderer::beginFrame() {
  // bind the render target
  device_context->OMSetRenderTargets(1, &render_target_view, nullptr);

  // set viewport
  CD3D11_VIEWPORT viewport = CD3D11_VIEWPORT(0.0f, 0.0f, back_buffer_description.Width, back_buffer_description.Height);
  device_context->RSSetViewports(1, &viewport);

  // Set the background color
  float clearColor[] = {.25f, .5f, 1.0f, 1.0f};
  device_context->ClearRenderTargetView(render_target_view, clearColor);
}

void Renderer::endFrame() {
  // Swap the buffer
  swap_chain->Present(1 /*vsync stuff*/, 0);
}
