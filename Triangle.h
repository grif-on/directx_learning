#pragma once

#include <vector>

#include "Renderer.h"

class Triangle {

public:
  Triangle(Renderer& renderer);
  ~Triangle();
  void draw(Renderer& renderer);

private:
  void createMesh(Renderer& renderer);
  void createShaders(Renderer& renderer);
  void createInputLayout(Renderer& renderer, std::vector<char>& vertex_shader_data);

  ID3D11Buffer* vertex_buffer       = nullptr;
  ID3D11VertexShader* vertex_shader = nullptr;
  ID3D11PixelShader* pixel_shader   = nullptr;
  ID3D11InputLayout* input_layout   = nullptr;
};