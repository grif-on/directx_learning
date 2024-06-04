#include "Triangle.h"

struct Vertex {
  float x, y;
  float r, g, b;
};

Triangle::Triangle(Renderer& renderer) {
  Vertex vertices[] = {
      {-1.0f, -1.0f, 1.0f, 0.0f, 0.0f},
      {0.0f, 1.0f, 0.0f, 1.0f, 0.0f},
      {1.0f, 0.0f, -1.0f, 0.0f, 1.0f}};

  CD3D11_BUFFER_DESC vertex_buffer_description = CD3D11_BUFFER_DESC(sizeof(vertices), D3D10_BIND_VERTEX_BUFFER);
  D3D11_SUBRESOURCE_DATA vertext_data          = {0};
  vertext_data.pSysMem                         = vertices;
  renderer.getDevice()->CreateBuffer(&vertex_buffer_description, &vertext_data, &vertex_buffer);
}

void Triangle::draw(Renderer& renderer) {
  UINT stride = sizeof(Vertex);
  UINT offset = 0;
  renderer.getDeviceContext()->IASetVertexBuffers(0, 1, &vertex_buffer, &stride, &offset);
  renderer.getDeviceContext()->Draw(3, 0);
}