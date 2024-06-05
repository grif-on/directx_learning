cmake_minimum_required(VERSION 3.28.1)
project(directx_learning VERSION 0.1.0 LANGUAGES C CXX)

set (CPPS WIN32 main.cpp Window.cpp Renderer.cpp Triangle.cpp)
add_executable(${PROJECT_NAME} ${CPPS})

set(LIBS d3d11 dxgi dxguid)
target_link_libraries(${PROJECT_NAME} ${LIBS})