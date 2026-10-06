# MPS

 A terminal emulator developed with C++ as the core.

## Environment

- **Core / header-only** (IO.h, MPS.h, ROOT.h, find.h, password.h); any C++17/20 compiler examples: GCC 10+, Clang 10+, MSVC 16.8+
- **C++20 modules with .ixx:**
 - MSVC: VS2022 17.x recommended (.ixx recognized natively, /std:c++20)
 - Clang: 16+ experimental (-std=c++20 -fmodules)
 - GCC: 13/14+ experimental (-std=c++20 -fmodules-ts); GCC 10 only for non-module code, not for .ixx
- **Build system:**
- CMake 3.28+ for automatic module dependency scanning (Ninja generator recommended); manual compiler flags otherwise

## Project Brief

- A terminal emulator developed in C++, including file operations, etc.
- The author is diligently updating the project and preparing to start designing programs oriented towards statistics.
- Open to creative extensions from the community
- Annotation:
- This project is for learning purposes, but everyone is welcome to review and comment.

## Project design proposal

- Designed with C++ at its core
- library coupling Modular decoupling design
- We also welcome everyone to design creatively.

## Project Update

The project is updated approximately every 1 to 3 weeks.

The author is planning to create a new repository.

Create separate branches to implement C++20 modules and traditional header files respectively.

### Finally

Thank you all for your support.
