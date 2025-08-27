#ifndef UI_H
#define UI_H

#include <stdio.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "scene/scene.hpp"

#include <GLFW/glfw3.h>

class UI {
 public:
  UI(GLFWwindow* window, Scene* scene);

  ~UI();

  void beginFrame();

  void drawUI();

  void renderFrame();

 private:
  GLFWwindow* window_;
  ImGuiIO& io_;
  ImGuiStyle& style_;
  int displayHeight_;

  Scene* scene_ = nullptr;
  Entity* selectedEntity_ = nullptr;
};

#endif