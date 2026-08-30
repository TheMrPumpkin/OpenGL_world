# OpenGL Terrain Project

A learning project exploring Modern OpenGL (4.4 core profile) in C++ — built while
working through terrain rendering, texturing, and camera controls.

> This README is a living document. Update the **Features**, **Roadmap**, and
> **Project Structure** sections as the project grows (see the note at the bottom).

## Features

- OpenGL 4.4 core profile context with debug output enabled
- Textured cube rendering (multi-texture blending via two bound texture units)
- Free-fly camera with WASD movement, mouse-look, and scroll-to-zoom (FOV)
- Simple `VertexArray` class wrapping VAO/VBO setup
- Terrain rendering *(in progress — see Roadmap)*

## Dependencies

| Library | Purpose |
|---|---|
| [GLFW](https://www.glfw.org/) | Window creation and input handling |
| [GLAD](https://glad.dav1d.de/) | OpenGL function loader |
| [GLM](https://github.com/g-truc/glm) | Math library (vectors, matrices, transforms) |
| [stb_image](https://github.com/nothings/stb) | Image loading for textures |

GLFW is expected to be found via `find_package(glfw3)` (install it system-wide,
e.g. via your distro's package manager). GLAD, GLM, and stb_image are expected
under `include/` in the project root.

## Building with CMake

```bash
# Clone the repo
git clone <your-repo-url>
cd OpenGL_project2

# Configure and build
mkdir build && cd build
cmake ..
make -j$(nproc)

# Run
./OpenGL-project
```

### Rebuilding after adding/removing source files or moving folders

CMake's `file(GLOB_RECURSE ...)` only scans `src/` at **configure time**
(when `cmake ..` runs) — not on every `make`. If you add, remove, or move
`.cpp`/`.h` files, you need to re-run `cmake ..` (or wipe and reconfigure)
for the build to pick up the change:

```bash
cd build
cmake ..          # re-scan src/ for new/removed files
make -j$(nproc)
```

If the build is in a broken state (stale paths, weird linker errors), the
safest fix is a clean rebuild:

```bash
cd ~/Documents/VSC/OpenGL/OpenGL_project2
rm -rf build
mkdir build && cd build
cmake ..
make -j$(nproc)
```

### Updating dependencies / GLM path

If CMake can't find GLM (`Could not find GLM_INCLUDE_DIR`), make sure GLM's
headers live under `include/glm/glm/glm.hpp` relative to the project root,
matching the `HINTS` path in `CMakeLists.txt`. Adjust the `HINTS` path there
if you relocate the GLM folder.

## Controls

| Input | Action |
|---|---|
| `W` / `A` / `S` / `D` | Move camera forward / left / back / right |
| Mouse movement | Look around |
| Scroll wheel | Zoom (adjusts FOV) |

## Project Structure

```
OpenGL_project2/
├── CMakeLists.txt
├── include/           # GLAD, GLM, stb_image, shader.h
├── images/            # Textures (copied to build/ on configure)
└── src/
    ├── main.cpp
    ├── camera.h / camera.cpp
    ├── Mouse.h / Mouse.cpp
    ├── VertexArray.h / VertexArray.cpp
    ├── OpenGLDebug.h / OpenGLDebug.cpp
    ├── VertexShader.vs
    └── FragmentShader.fs
```

## Roadmap

- [ ] Terrain generation (heightmap-based)
- [ ] Lighting (Phong/Blinn-Phong)
- [ ] Element buffer objects for indexed drawing
- [ ] Multiple objects / scene graph

---

### Keeping this README up to date

As the project evolves, update:
- **Features** — check off/add items as they're implemented
- **Roadmap** — move completed items up to Features, add new goals
- **Project Structure** — reflect new files/folders as they're added
- **Dependencies** — add any new libraries you pull in
