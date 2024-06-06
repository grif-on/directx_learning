#include <fstream>

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
  input_layout->Release();
}

void Triangle::draw(Renderer& renderer) {
  ID3D11DeviceContext* device_context = renderer.getDeviceContext();

  // Bind our shaders
  device_context->IASetInputLayout(input_layout);
  device_context->VSSetShader(vertex_shader, nullptr, 0);
  device_context->PSSetShader(pixel_shader, nullptr, 0);

  // Bind our vertex buffer
  UINT stride = sizeof(Vertex);
  UINT offset = 0;
  device_context->IASetVertexBuffers(0, 1, &vertex_buffer, &stride, &offset);
  device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

  // Draw
  device_context->Draw(3, 0);
}

void Triangle::createMesh(Renderer& renderer) {
  Vertex vertices[] = {
      {-1.0f, -1.0f, 1.0f, 0.0f, 0.0f},
      {0.0f, 1.0f, 0.0f, 1.0f, 0.0f},
      {1.0f, -1.0f, 0.0f, 0.0f, 1.0f}};

  CD3D11_BUFFER_DESC vertex_buffer_description = CD3D11_BUFFER_DESC(sizeof(vertices), D3D10_BIND_VERTEX_BUFFER);
  D3D11_SUBRESOURCE_DATA vertext_data          = {0};
  vertext_data.pSysMem                         = vertices;
  renderer.getDevice()->CreateBuffer(&vertex_buffer_description, &vertext_data, &vertex_buffer);
}

void Triangle::createShaders(Renderer& renderer) {
  std::ifstream vertex_shader_file("shaders/DefaultVertexShader.cso", std::ios::binary);
  std::ifstream pixel_shader_file("shaders/DefaultPixelShader.cso", std::ios::binary);

  std::vector<char> vertex_shader_data = {std::istreambuf_iterator<char>(vertex_shader_file), std::istreambuf_iterator<char>()};
  std::vector<char> pixel_shader_data  = {std::istreambuf_iterator<char>(pixel_shader_file), std::istreambuf_iterator<char>()};

  renderer.getDevice()->CreateVertexShader(vertex_shader_data.data(), vertex_shader_data.size(), nullptr, &vertex_shader);
  renderer.getDevice()->CreatePixelShader(pixel_shader_data.data(), pixel_shader_data.size(), nullptr, &pixel_shader);

  createInputLayout(renderer, vertex_shader_data);
}

void Triangle::createInputLayout(Renderer& renderer, std::vector<char>& vertex_shader_data) {
  D3D11_INPUT_ELEMENT_DESC input_layout_description[] = {
      {"POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0 /*offset 0*/, D3D11_INPUT_PER_VERTEX_DATA, 0},
      {"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT /*auto offset 8*/, D3D11_INPUT_PER_VERTEX_DATA, 0}};

  renderer.getDevice()->CreateInputLayout(input_layout_description, 2, vertex_shader_data.data(), vertex_shader_data.size(), &input_layout);
}