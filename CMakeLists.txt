cmake_minimum_required(VERSION 3.16)

project(mps_terminal)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(mps_terminal
    main.cpp
    IO.h
    MPS.h
    ROOT.h
    find.h
    password.h
)

target_include_directories(mps_terminal PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

#  Windows + MSVC
if(MSVC)
    target_compile_options(mps_terminal PRIVATE /W3)
else()
    # Linux / macOS 
    target_compile_options(mps_terminal PRIVATE -Wall -Wextra)
endif()
