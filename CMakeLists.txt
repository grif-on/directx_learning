cmake_minimum_required(VERSION 3.28.1)
project(directx_learning VERSION 0.1.0 LANGUAGES C CXX)


# ================ build project executable ================
set (CPPS WIN32 main.cpp Window.cpp Renderer.cpp Triangle.cpp)
add_executable(${PROJECT_NAME} ${CPPS})

set(LIBS d3d11 dxgi dxguid)
target_link_libraries(${PROJECT_NAME} ${LIBS})


# =================== Build HLSL shaders ===================
add_custom_target(shaders ALL)

set(HLSL_SHADERS shaders/DefaultPixelShader.hlsl shaders/DefaultVertexShader.hlsl)

set_source_files_properties(shaders/DefaultVertexShader.hlsl PROPERTIES ShaderType "vs")
set_source_files_properties(shaders/DefaultPixelShader.hlsl PROPERTIES ShaderType "ps")
set_source_files_properties(${HLSL_SHADERS} PROPERTIES ShaderModel "5_0")

foreach(FILE ${HLSL_SHADERS})
  get_filename_component(FILE_WE ${FILE} NAME_WE)
  get_filename_component(FILE_NAME ${FILE} NAME)
  get_source_file_property(shadertype ${FILE} ShaderType)
  get_source_file_property(shadermodel ${FILE} ShaderModel)

  set(SHADERS_FOLDER shaders)

  add_custom_command(TARGET shaders # fxc.exe can fail if there is no directory yet
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/$<IF:$<CONFIG:DEBUG>,/Debug,/Release>/${SHADERS_FOLDER}
  )
  add_custom_command(TARGET shaders COMMAND echo ===== ${FILE_NAME} =====)
  add_custom_command(TARGET shaders
                     COMMAND fxc.exe /nologo /Emain /T${shadertype}_${shadermodel} $<IF:$<CONFIG:DEBUG>,/Od,/O1> /Zi /Fo ${CMAKE_BINARY_DIR}/$<CONFIG>/${SHADERS_FOLDER}/${FILE_WE}.cso /Fd ${CMAKE_BINARY_DIR}/$<CONFIG>/${SHADERS_FOLDER}/${FILE_WE}.pdb ${FILE}
                     MAIN_DEPENDENCY ${FILE}
                     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                     VERBATIM)
endforeach(FILE)
add_custom_command(TARGET shaders COMMAND echo .)