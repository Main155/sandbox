# MPS Terminal
A modular terminal command system in C++20 — command dispatch via unordered_map+std::function, file management, ROOT read/write subsystem, cross-platform I/O (RAII terminal guards, hidden password input, ANSI color, logging). Statistics module planned.

## Environment
- Core / header-only (IO.h, MPS.h, ROOT.h, find.h, password.h): any C++17/20 compiler
  examples: GCC 10+, Clang 10+, MSVC 16.8+ for concepts/ranges basics
- C++20 modules with .ixx:
  - MSVC: VS2022 17.x recommended (.ixx recognized natively, /std:c++20)
  - Clang: 16+ experimental (-std=c++20 -fmodules)
  - GCC: 13/14+ experimental (-std=c++20 -fmodules-ts); GCC 10 only for non-module code, not for .ixx
- Build system: CMake 3.28+ for automatic module dependency scanning (Ninja generator recommended); manual compiler flags otherwise

## Project Brief
A terminal emulator developed in C++, including file operations, etc.

The author is diligently updating the project and preparing to start designing programs oriented towards statistics.

Annotation:

This project is for learning purposes, but everyone is welcome to review and comment.

## Project design proposal
Designed with C++ at its core

library coupling
Modular decoupling design

## Project Update
The project is updated approximately every 1 to 3 weeks.

During this period, everyone is welcome to leave comments.
