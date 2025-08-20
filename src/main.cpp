// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include <iostream>
#include <memory>

#include "lightmanager.hpp"
#include "scene/model.hpp"
#include "scene/scene.hpp"
#include "shader.hpp"
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

  /*
    SHADERS
  */
  Shader basicShader("./shaders/vLightShader.glsl",
                     "./shaders/fLightShader.glsl");

  Shader lightCubeShader("./shaders/vLightCubeShader.glsl",
                         "./shaders/fLightCubeShader.glsl");

  /*
    LIGHT MANAGER
  */
  LightManager lightManager;

  // generic directional light
  lightManager.addDirLight({.direction = glm::vec3(0.0f, -1.0f, -1.0f),
                            .ambient = glm::vec3(0.05f, 0.05f, 0.05f),
                            .diffuse = glm::vec3(0.4f, 0.4f, 0.4f),
                            .specular = glm::vec3(1.0f, 1.0f, 1.0f)});

  // blue-ish light
  lightManager.addPointLight({.position = glm::vec3(-2.0f, 2.0f, -5.0f),
                              .ambient = glm::vec3(0.0f, 0.0f, 0.0f),
                              .diffuse = glm::vec3(0.2f, 0.2f, 0.7f),
                              .specular = glm::vec3(1.0f, 1.0f, 1.0f),
                              .constant = 1.0f,
                              .linear = 0.0014f,
                              .quadratic = 0.000007f,
                              .scale = 0.3f});

  // orange-ish light
  lightManager.addSpotLight({.position = glm::vec3(0.0f, 4.0f, 0.3f),
                             .direction = glm::vec3(0.0f, -1.0f, 0.0f),
                             .ambient = glm::vec3(0.0f, 0.0f, 0.0f),
                             .diffuse = glm::vec3(0.7f, 0.4f, 0.2f),
                             .specular = glm::vec3(1.0f, 1.0f, 1.0f),
                             .cutOff = glm::cos(glm::radians(12.5f)),
                             .outerCutOff = glm::cos(glm::radians(18.0f)),
                             .constant = 1.0f,
                             .linear = 0.0014f,
                             .quadratic = 0.000007f,
                             .scale = 0.3f});

  basicShader.use();
  lightManager.sendLightsToShader(basicShader);

  /*
    MODELS
  */
  Scene scene;

  glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

  std::unique_ptr<Entity> guitar = std::make_unique<ModelEntity>(
      scene.getOrCreateModel("./assets/models/backpack/backpack.obj"),
      Transform(position, scale));

  // position = glm::vec3(1.0f, 0.0f, 3.0f);
  // std::unique_ptr<Entity> guitar2 = std::make_unique<ModelEntity>(
  //     scene.getOrCreateModel("./assets/models/backpack/backpack.obj"),
  //     Transform(position, scale));

  scene.addEntity(std::move(guitar));
  // scene.addEntity(std::move(guitar2));

  glEnable(GL_DEPTH_TEST);

  while (!glfwWindowShouldClose(window.window_)) {
    window.updateDeltaTime();
    window.processInput();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    basicShader.use();
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 projection = glm::perspective(
        glm::radians(camera.Fov),
        (float)window.getWidth() / (float)window.getHeight(), 0.1f, 100.0f);

    basicShader.setMat4("view", view);
    basicShader.setMat4("projection", projection);

    scene.draw(basicShader);

    lightManager.drawLights(lightCubeShader, view, projection);

    glfwSwapBuffers(window.window_);
    glfwPollEvents();
  }

  // clean / delete all of GLFW's resources that were allocated
  glDeleteProgram(basicShader.ID);
  glDeleteProgram(lightCubeShader.ID);
  glfwTerminate();
  return 0;
}