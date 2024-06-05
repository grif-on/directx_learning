#pragma once

#include "Renderer.h"

class Triangle {

public:
  Triangle(Renderer& renderer);
  ~Triangle();
  void draw(Renderer& renderer);

private:
  void createMesh(Renderer& renderer);
  void createShaders(Renderer& renderer);

  ID3D11Buffer* vertex_buffer       = nullptr;
  ID3D11VertexShader* vertex_shader = nullptr;
  ID3D11PixelShader* pixel_shader   = nullptr;
};