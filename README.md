# SimpleGLRenderer

## Info 

![img](/docs/img/image.png)

### Description

A simple renderer build with OpenGL on Linux (Ubuntu).

### Setup 

Clone the repo including submodules:

```bash
git clone --recurse-submodules <repo-url>
cd <repo-name>
```

If you already cloned without submodules, run:

```bash
git submodule update --init --recursive
```

To update later:

```bash
git pull --recurse-submodules
git submodule update --recursive --remote
```

Then install the following dependencies (assumes Ubuntu 24 or later):

`sudo apt install libglm-dev` -> math lib for opengl

`sudo apt install libglfw3-dev` -> glfw3

`sudo apt install libassimp-dev` -> assimp


### Building the project

```bash
cd build
cmake ..
make
./renderer
```

### Features

- **Asset Loading:** Load 3D models via [Assimp](https://www.assimp.org/).  
- **Shaders & Lighting:** Phong shading with a flexible light manager system.  
- **User Interface:** Integrated UI using [Dear ImGui](https://github.com/ocornut/imgui).  
- **Window Management:** Abstracted window handling and OpenGL context setup.  
- **Utilities:** Helper functions for loading models and other assets.  
- **Camera:** First-person camera with Unreal Engine-style controls (hold right mouse button to navigate).  
- **Scene Graph:** Basic scene graph with entities, transforms, meshes, models, and hierarchical structure.  
- **Mesh Factory:** Easily create common 3D geometry like boxes, planes, and spheres.  


### Styleguide

Using VSCode, the C++ style of choice is **Chromium**.

`"C_Cpp.clang_format_style": "Chromium",`

