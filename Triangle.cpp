#include <fstream>
#include <vector>

#include "Triangle.h"

struct Vertex {
  float x, y;
  float r, g, b;
};

Triangle::Triangle(Renderer& renderer) {
  createMesh(renderer);
  createShaders(renderer);
}

Triangle::~Triangle() {
  vertex_buffer->Release();
  vertex_shader->Release();
  pixel_shader->Release();
}

void Triangle::draw(Renderer& renderer) {
  // Bind our shaders
  renderer.getDeviceContext()->VSSetShader(vertex_shader, nullptr, 0);
  renderer.getDeviceContext()->PSSetShader(pixel_shader, nullptr, 0);

  // Bind our vertex buffer
  UINT stride = sizeof(Vertex);
  UINT offset = 0;
  renderer.getDeviceContext()->IASetVertexBuffers(0, 1, &vertex_buffer, &stride, &offset);

  // Draw
  renderer.getDeviceContext()->Draw(3, 0);
}

void Triangle::createMesh(Renderer& renderer) {
  Vertex vertices[] = {
      {-1.0f, -1.0f, 1.0f, 0.0f, 0.0f},
      {0.0f, 1.0f, 0.0f, 1.0f, 0.0f},
      {1.0f, 0.0f, -1.0f, 0.0f, 1.0f}};

  CD3D11_BUFFER_DESC vertex_buffer_description = CD3D11_BUFFER_DESC(sizeof(vertices), D3D10_BIND_VERTEX_BUFFER);
  D3D11_SUBRESOURCE_DATA vertext_data          = {0};
  vertext_data.pSysMem                         = vertices;
  renderer.getDevice()->CreateBuffer(&vertex_buffer_description, &vertext_data, &vertex_buffer);
}

void Triangle::createShaders(Renderer& renderer) {
  std::ifstream vertex_shader_file("shaders/DefaultVertexShader.cso", std::ios::binary);
  std::ifstream pixel_shader_file("shaders/DefaultPixelShader.cso", std::ios::binary);

  std::vector<char> vertex_shader_date = {std::istreambuf_iterator<char>(vertex_shader_file), std::istreambuf_iterator<char>()};
  std::vector<char> pixel_shader_data  = {std::istreambuf_iterator<char>(pixel_shader_file), std::istreambuf_iterator<char>()};

  renderer.getDevice()->CreateVertexShader(vertex_shader_date.data(), vertex_shader_date.size(), nullptr, &vertex_shader);
  renderer.getDevice()->CreatePixelShader(pixel_shader_data.data(), pixel_shader_data.size(), nullptr, &pixel_shader);
}