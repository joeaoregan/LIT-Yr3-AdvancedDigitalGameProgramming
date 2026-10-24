# Quick Setup: SDL 2.0 and Extensions

This guide outlines the setup required for SDL 2.0, SDL_image, SDL_mixer, and SDL_ttf for the Alien Attack project.

## 1. Download and Extract
Download the Visual C++ development libraries for the following from the official SDL GitHub releases or website:

* SDL2
* SDL2_image
* SDL2_mixer
* SDL2_ttf

Extract all downloaded `.zip` files to a stable directory on your development machine (e.g., `C:\SDL2`).

## 2. Visual Studio Properties Configuration
Open the `Alien Attack K00203642.vcxproj` project file in Visual Studio. Right-click the project name in the Solution Explorer, select **Properties**, and make certain the **Configuration** dropdown at the top is set to **All Configurations**.

!!! important "Target Architecture"  
    Ensure your Visual Studio build target (e.g. `x86` vs `x64`) strictly matches the library subfolder referenced in Linker properties (`lib\x86` vs `lib\x64`). Architecture mismatches will produce `LNK2019` unresolved external symbols or `LNK1112` module machine type conflicts.

### Include Directories
Navigate to **C/C++** -> **General** -> **Additional Include Directories**. Add the paths to the `include` directories for all four libraries.

### Library Directories
Navigate to **Linker** -> **General** -> **Additional Library Directories**. Add the paths to the `lib\x86` or `lib\x64` directories for all four libraries, depending on your target build architecture.

### Linker Dependencies
Navigate to **Linker** -> **Input** -> **Additional Dependencies**. Add the following libraries to the list:

* `SDL2.lib`
* `SDL2main.lib`
* `SDL2_image.lib`
* `SDL2_mixer.lib`
* `SDL2_ttf.lib`

## 3. Runtime Configuration
!!! tip "Local DLL Deployment"  
    Deploying the runtime `.dll` files directly adjacent to the compiled executable or project file keeps the development environment portable and avoids modifying global Windows `PATH` environment variables.

The following dynamic libraries are required at runtime:

* `SDL2.dll`
* `SDL2_image.dll`
* `SDL2_mixer.dll`
* `SDL2_ttf.dll`
* Any dependent DLLs included in the extension packages (e.g., `libfreetype-6.dll`, `libjpeg-9.dll`, `libpng16-16.dll`).