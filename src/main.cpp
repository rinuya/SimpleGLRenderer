// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include <iostream>

#include "window.hpp"

const unsigned int SCR_WIDTH = 1200;  // screen width
const unsigned int SCR_HEIGHT = 800;  // screen height

int main() {
  /*
    SETUP
  */
  if (!glfwInit()) {
    std::cerr << "ERROR: Failed to initialize GLFW\n";
    return -1;
  }

  Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
  const char* windowTitle = "MyFirstRenderer";
  Window window(SCR_WIDTH, SCR_HEIGHT, windowTitle, camera);

  if (window.initFailed() == true) {
    // window init failed
    return -1;
  }

  glEnable(GL_DEPTH_TEST);

  while (!glfwWindowShouldClose(window.window_)) {
    window.updateDeltaTime();
    window.processInput();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glClearColor(0.9f, 0.1f, 0.1f, 1.0f);

    glfwSwapBuffers(window.window_);
    glfwPollEvents();
  }

  // clean / delete all of GLFW's resources that were allocated
  glfwTerminate();
  return 0;
}