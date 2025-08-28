#ifndef UI_H
#define UI_H

#include <stdio.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "scene/scene.hpp"

#include <GLFW/glfw3.h>

const int SCENE_WINDOW_MIN_WIDTH = 150;

class UI {
 public:
  /**
   * @brief Construct the UI system.
   *
   * Initializes ImGui with GLFW and OpenGL backends.
   *
   * @param window Pointer to the GLFW window.
   * @param scene Pointer to the Scene object to visualize and edit.
   */
  UI(GLFWwindow* window, Scene* scene);

  /**
   * @brief Destructor for UI.
   *
   * Cleans up ImGui backends and context.
   */
  ~UI();

  /**
   * @brief Start a new ImGui frame.
   *
   * Prepares ImGui for UI rendering. Must be called once per frame
   * before drawing UI elements.
   */
  void beginFrame();

  /**
   * @brief Draw all UI elements.
   *
   * Renders the scene graph, entity properties, and other UI panels.
   * Should be called after beginFrame() and before renderFrame().
   */
  void drawUI();

  /**
   * @brief Finalize and render the ImGui frame.
   *
   * Submits ImGui draw data to OpenGL.
   */
  void renderFrame();

 private:
  GLFWwindow* window_;
  ImGuiIO& io_;
  ImGuiStyle& style_;
  int displayWidth_;
  int displayHeight_;

  Scene* scene_ = nullptr;
  Entity* selectedEntity_ = nullptr;

  void drawSceneGraph();
  void drawEntity();
};

#endif