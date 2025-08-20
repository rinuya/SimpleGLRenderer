# SimpleGLRenderer

## Info 

Current progress: 

![img](/docs/img/image.png)

### Description

A simple renderer build with OpenGL on Linux.

### Setup 
`sudo apt install libglm-dev` -> math lib for opengl

### Building the project
```
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