#pragma once

#include "Renderer.h"

class Triangle {

public:
  Triangle(Renderer& renderer);
  void draw(Renderer& renderer);

private:
  ID3D11Buffer* vertex_buffer = nullptr;
};