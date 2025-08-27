#ifndef UI_H
#define UI_H

#include <GLFW/glfw3.h>
#include <stdio.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class UI {
 public:
  UI(GLFWwindow* window);

  ~UI();

  void beginFrame();

  void drawUI();

  void renderFrame();

 private:
  GLFWwindow* window_;
  ImGuiIO& io_;
  ImGuiStyle& style_;
};

#endif