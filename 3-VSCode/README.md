# VS Code build setup

This folder is a lightweight VS Code-friendly CMake configuration for the project, intended to avoid the Visual Studio-specific overhead while keeping the same SDL-based game code.

## Why this is a reasonable approach

The existing project is already a C++/SDL game. The main Visual Studio dependency is the hard-coded Windows include/library setup in the `.vcxproj` file, not the game logic itself. Moving the project to VS Code mainly means replacing the old Visual Studio build configuration with CMake and letting VS Code build it using a C++ toolchain.

This is similar in spirit to the Code::Blocks route: a portable build entry point without the full Visual Studio IDE.

## Files in this folder

- `CMakeLists.txt` — build definition for the project
- `.vscode/tasks.json` — optional VS Code build commands

## Requirements

Install one of these toolchains:

- MSYS2 + MinGW, or
- vcpkg + MSVC/clang, or
- a standard CMake + SDL dev environment on Windows

You will also need the SDL development packages:

- `SDL2`
- `SDL2_image`
- `SDL2_ttf`
- `SDL2_mixer`

## Typical setup

From the repository root:

```bash
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
```

Or in VS Code, use the CMake Tools extension and select the configured generator.

## Notes

This is intentionally a starter setup. The original project includes absolute Windows paths and Visual Studio-specific settings, so the easiest migration path is to keep the source files and replace the project build configuration rather than trying to run the legacy `.vcxproj` directly in VS Code.

That means this should be a moderate-effort refactor, not a huge rewrite.
