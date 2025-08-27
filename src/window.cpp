#include "window.hpp"

Window::Window(unsigned int width,
               unsigned int height,
               const char* title,
               Camera& camera)
    : width_(width), height_(height), title_(title), camera_(camera) {
  // if constructor fails at any point, initFailed_ will be set to true
  initFailed_ = false;

  moveCamera_ = true;
  firstMouse_ = true;

  lastX_ = 0.0f;
  lastY_ = 0.0f;
  deltaTime_ = 0.0f;
  lastFrame_ = 0.0f;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window_ = glfwCreateWindow(width_, height_, title_, NULL, NULL);
  // set what the window pointer is for  the function glfwGetWindowUserPointer
  glfwSetWindowUserPointer(window_, this);

  if (window_ == NULL) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    initFailed_ = true;
    return;
  }

  glfwMakeContextCurrent(window_);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to init GLAD" << std::endl;
    initFailed_ = true;
    return;
  }

  glViewport(0, 0, width_, height_);

  glfwSetCursorPosCallback(window_, Window::mouseCallback);
  glfwSetScrollCallback(window_, Window::scrollCallback);
  glfwSetFramebufferSizeCallback(window_, Window::framebufferSizeCallback);

  glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  // enable v-sync
  glfwSwapInterval(1);
}

void Window::updateDeltaTime() {
  float currentFrame = (float)glfwGetTime();
  deltaTime_ = currentFrame - lastFrame_;
  lastFrame_ = currentFrame;

  // FPS display
  frames_++;
  fpsTimer_ += deltaTime_;
  if (fpsTimer_ >= 1.0f) {
    fps_ = frames_;
    frames_ = 0;
    fpsTimer_ = 0.0f;

    std::string newTitle =
        std::string(title_) + " - FPS: " + std::to_string(fps_);
    glfwSetWindowTitle(window_, newTitle.c_str());
  }
}

void Window::processInput() {
  if (glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window_, true);

  // WASD Camera movement
  if (moveCamera_) {
    if (glfwGetKey(window_, GLFW_KEY_W) == GLFW_PRESS) {
      camera_.processKeyboard(FORWARD, deltaTime_);
    }
    if (glfwGetKey(window_, GLFW_KEY_S) == GLFW_PRESS) {
      camera_.processKeyboard(BACKWARD, deltaTime_);
    }
    if (glfwGetKey(window_, GLFW_KEY_A) == GLFW_PRESS) {
      camera_.processKeyboard(LEFT, deltaTime_);
    }
    if (glfwGetKey(window_, GLFW_KEY_D) == GLFW_PRESS) {
      camera_.processKeyboard(RIGHT, deltaTime_);
    }
  }

  // Update mouse capture based on right mouse button
  if (glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
    moveCamera_ = true;
    glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  } else {
    moveCamera_ = false;
    glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    firstMouse_ = true;
  }
}

void Window::framebufferSizeCallback(GLFWwindow* window,
                                     int width,
                                     int height) {
  static_cast<Window*>(glfwGetWindowUserPointer(window))
      ->handleResizeInput(width, height);
}

void Window::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
  static_cast<Window*>(glfwGetWindowUserPointer(window))
      ->handleMouseInput(xpos, ypos);
}

void Window::scrollCallback(GLFWwindow* window,
                            double xoffset,
                            double yoffset) {
  static_cast<Window*>(glfwGetWindowUserPointer(window))
      ->handleScrollInput(xoffset, yoffset);
}

void Window::handleResizeInput(int width, int height) {
  glViewport(0, 0, width, height);
  width_ = width;
  height_ = height;
}

void Window::handleMouseInput(double xposIn, double yposIn) {
  if (!moveCamera_) {
    return;
  }

  if (firstMouse_) {
    lastX_ = (float)xposIn;
    lastY_ = (float)yposIn;
    firstMouse_ = false;
    return;  // skip this frame so no jump
  }

  float xpos = (float)xposIn;
  float ypos = (float)yposIn;

  float xoffset = xpos - lastX_;
  float yoffset =
      lastY_ - ypos;  // reversed since y-coordinates go from bottom to top

  lastX_ = xpos;
  lastY_ = ypos;

  camera_.processMouseMovement(xoffset, yoffset);
}

void Window::handleScrollInput(double xoffset, double yoffset) {
  if (!moveCamera_) {
    return;
  }
  camera_.processMouseScroll((float)yoffset);
}