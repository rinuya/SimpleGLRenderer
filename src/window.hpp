#ifndef CALLBACK_H
#define CALLBACK_H
// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on
#include <iostream>

#include "camera.hpp"

class Window {
 public:
  GLFWwindow* window_;

  /**
   * @brief Construct a new Window object
   *
   * If the object init fails at any point, `initFailed_` will be set to `true`.
   * This status can be checked with the `initFailed()` function.
   *
   * @param width Initial window width
   * @param height Initial window height
   * @param title Window title
   */
  Window(unsigned int width,
         unsigned int height,
         const char* title,
         Camera& camera);

  /**
   * @brief Get init state
   *
   * @return true
   * @return false
   */
  bool initFailed() const { return initFailed_; }

  /**
   * @brief Get the Window width
   *
   * @return unsigned int
   */
  unsigned int getWidth() { return width_; }

  /**
   * @brief Get the Widow height
   *
   * @return unsigned int
   */
  unsigned int getHeight() { return height_; }

  /**
   * @brief Called inbetween each write to update lastFrame and deltaTime
   *
   */
  void updateDeltaTime();

  /**
   * @brief Handles user keyboard input
   *
   */
  void processInput();

 private:
  bool initFailed_;

  Camera camera_;
  bool captureMouse_;
  bool firstMouse_;
  float lastX_;
  float lastY_;

  float deltaTime_;  // Time between current frame and last frame
  float lastFrame_;  // Time of last frame

  const char* title_;
  unsigned int width_;
  unsigned int height_;

  static void framebufferSizeCallback(GLFWwindow* window,
                                      int width,
                                      int height);
  static void mouseCallback(GLFWwindow* window, double xposIn, double yposIn);
  static void scrollCallback(GLFWwindow* window,
                             double xoffset,
                             double yoffset);

  void handleResizeInput(int width, int height);
  void handleMouseInput(double xposIn, double yposIn);
  void handleScrollInput(double xoffset, double yoffset);
};

#endif