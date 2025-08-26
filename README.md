# SimpleGLRenderer

## Info 

Current progress: 

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

Then install some dependencies:

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

### Styleguide

`"C_Cpp.clang_format_style": "Chromium",`


### TODO:

*Setup UI elements*:
- left side the scene
- right side the details of selected object

Then, make sure that position and scale of objects can be changed. Maybe also color, if we have "just a color" for meshes.

*Change camera behavior to*:
- only move when right mouse button is held down.
- else, regular mouse to be able to select UI elements.

To mimic UE5 controls