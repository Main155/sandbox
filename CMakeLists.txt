cmake_minimum_required(VERSION 3.28)
project(mps_terminal LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_executable(mps
    main.cpp
)

target_sources(mps PRIVATE
    IO.h
    MPS.h
    ROOT.h
    find.h
    password.h
)


if(MSVC)
    target_sources(mps PRIVATE
        command.ixx
        control.ixx
    )
else()

    set_source_files_properties(command.ixx control.ixx
        PROPERTIES COMPILE_FLAGS "-fmodules-ts"
    )
    target_sources(mps PRIVATE
        command.ixx
        control.ixx
    )
endif()
