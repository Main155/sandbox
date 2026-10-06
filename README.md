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
- Open to creative extensions from the community.

  **Below is a screenshot of the running program:**
  
<img width="445" height="455" alt="image" src="https://github.com/user-attachments/assets/dbcc219c-e2d0-4488-adfc-ffa67506a2a3" />
<img width="394" height="440" alt="{087E1713-8B58-409A-9189-B111BC23C7B8}" src="https://github.com/user-attachments/assets/7198a4a8-a713-44ac-93f5-dc739f712136" />


<img width="307" height="238" alt="{25EB781B-F0BE-4B1C-928B-F65A570AB9B5}" src="https://github.com/user-attachments/assets/126f3d0c-ea5c-4b64-8937-bbef37852141" />

<img width="401" height="181" alt="{A01FA87C-D490-48AB-95EA-AB6DBB82B8FF}" src="https://github.com/user-attachments/assets/6a6b7827-e365-43e8-852e-30f8300d576f" />

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
