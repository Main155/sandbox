cmake_minimum_required(VERSION 3.28)
project(mps_terminal LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(mps
    main.cpp              
    IO.h
    MPS.h
    ROOT.h
    find.h
    password.h
    color.h
    error.h
    file.h
    log.h
    math.h
    Statistics.h
)

target_include_directories(mps PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(mps PRIVATE
    FILE_SET CXX_MODULES
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    FILES command.ixx control.ixx
)

if(NOT MSVC)
    message(WARNING
      "C++20 模块在非 MSVC 工具链上支持不完整（Clang 需 Ninja + -fmodules，GCC 仍偏实验）。"
      "建议改用 mps_hpp 头文件版 target，或切换至 MSVC / Ninja 生成器。")
endif()
