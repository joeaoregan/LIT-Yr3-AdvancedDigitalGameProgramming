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
Instead of modifying system environment variables, copy the corresponding `.dll` files directly into the project folder alongside your source files or into your build output directory. The following dynamic libraries are used at runtime:
* `SDL2.dll`
* `SDL2_image.dll`
* `SDL2_mixer.dll`
* `SDL2_ttf.dll`
* Any dependent DLLs included in the extension packages (e.g., `libfreetype-6.dll`, `libjpeg-9.dll`, `libpng16-16.dll`).