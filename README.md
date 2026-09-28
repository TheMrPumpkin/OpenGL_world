# OpenGL_world

A learning project exploring **Modern OpenGL (4.4 core profile)** in C++, built while working through texturing, camera controls, lighting, and (next) terrain rendering.

<!-- Add a screenshot or GIF here, e.g.: ![Screenshot](docs/screenshot.png) -->

## Features

- OpenGL 4.4 core profile context with debug output enabled
- Textured cube rendering with multi-texture blending (two bound texture units)
- Free-fly camera: WASD movement, mouse-look, scroll-to-zoom (FOV)
- Basic Phong lighting (ambient + diffuse + specular) on a cube, with a separate cube marking the light source
- Light casters: directional, point (with attenuation), and spotlight (soft edges)
- `VertexArray` class wrapping VAO/VBO setup
- `Texture2D` class for loading and binding textures
- Terrain rendering *(in progress, see [Roadmap](#roadmap))*

## Dependencies

| Library                                      | Purpose                                      |
|----------------------------------------------|----------------------------------------------|
| [GLFW](https://www.glfw.org/)                | Window creation and input handling           |
| [GLAD](https://glad.dav1d.de/)               | OpenGL function loader                       |
| [GLM](https://github.com/g-truc/glm)         | Math library (vectors, matrices, transforms) |
| [stb_image](https://github.com/nothings/stb) | Image loading for textures                   |

- **GLFW** is found via `find_package(glfw3)`, so install it system-wide (e.g. with your distro's package manager).
- **GLAD**, **GLM**, and **stb_image** are expected under `include/` in the project root.

## Building

```bash
git clone https://github.com/TheMrPumpkin/OpenGL_world.git
cd OpenGL_world

mkdir build && cd build
cmake ..
make -j$(nproc)

./OpenGL-project
```

### Adding, removing, or moving source files

Sources are collected with `file(GLOB_RECURSE ...)` over `src/` at **configure time** only. After adding, removing, or moving `.cpp`/`.h` files, re-run CMake:

```bash
cd build
cmake ..
make -j$(nproc)
```

If the build is in a broken state (stale paths, odd linker errors), do a clean rebuild:

```bash
rm -rf build
mkdir build && cd build
cmake ..
make -j$(nproc)
```

### GLM not found

If CMake reports `Could not find GLM_INCLUDE_DIR`, make sure GLM's headers are at `include/glm/glm/glm.hpp` (relative to the project root), matching the `HINTS` path in `CMakeLists.txt`. If you move the GLM folder, update `HINTS` accordingly.

## Controls

| Input                 | Action                                    |
|-----------------------|-------------------------------------------|
| `W` / `A` / `S` / `D` | Move camera forward / left / back / right |
| Mouse movement        | Look around                               |
| Scroll wheel          | Zoom (adjusts FOV)                        |

## Project Structure

```
OpenGL_world/
├── CMakeLists.txt
├── include/
│   ├── glad/
│   ├── glfw-3.4/
│   ├── glm/
│   ├── shaders/
│   │   ├── cubelightshader.vs / .fs   # lit object (Phong)
│   │   └── lightshader.vs / .fs       # light-source cube (solid color)
│   ├── shader_debug.h                 # shader compile/link error checking
│   └── stb_image.h
├── src/
│   ├── main.cpp
│   ├── camera.h / camera.cpp
│   ├── Mouse.h / Mouse.cpp
│   ├── VertexArray.h / VertexArray.cpp
│   ├── Texture2D.h / Textrue2D.cpp
│   └── OpenGLDebug.h / OpenGLDebug.cpp
├── .gitattributes
├── .gitignore
└── LICENSE
```

## Updates

### Light casters (2026-09-28)

- Extended the Phong lighting shader to support different types of light casters:
  - **Directional light**: a light with no position, only a direction (like the sun), so all rays are parallel.
  - **Point light**: a light with a position that radiates in all directions, with distance attenuation (constant, linear, and quadratic terms) so it fades with distance.
  - **Spotlight**: a light with a position, direction, and cutoff angle, with a smooth inner/outer cone falloff for soft edges.
- Light properties (direction, position, attenuation, cutoff angles) are passed to `cubelightshader.fs` as uniforms.

## Roadmap

- [x] Lighting (Phong: ambient/diffuse/specular)
- [x] Light casters (directional, point, spotlight)
- [ ] Terrain generation (heightmap-based)
- [ ] Load and render 3D models (e.g. via Assimp)
- [ ] Full object rotation controls (all axes)
- [ ] Blinn-Phong lighting variant
- [ ] Config system for swapping textures/materials/parameters without recompiling
- [ ] Element buffer objects for indexed drawing
- [ ] Multiple objects / scene graph

## License

See [LICENSE](LICENSE).

<!--
Maintenance notes:
- Features: add items as they're implemented
- Roadmap: check off finished items, add new goals
- Project Structure: reflect new files/folders
- Dependencies: add any new libraries
- Updates: add a dated entry for each completed feature or fix
-->
