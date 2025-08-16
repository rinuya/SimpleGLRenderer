// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include <iostream>

#include "lightmanager.hpp"
#include "model.hpp"
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

  lightManager.addDirLight(
      glm::vec3(0.0f, -1.0f, -1.0f), glm::vec3(0.05f, 0.05f, 0.05f),
      glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(1.0f, 1.0f, 1.0f));

  // blue-ish light
  lightManager.addPointLight(
      glm::vec3(-2.0f, 2.0f, 5.0f), glm::vec3(0.0f, -1.0f, -1.0f),
      glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.4f, 0.4f, 0.7f),
      glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.0014f, 0.000007f, 0.5f);

  basicShader.use();
  lightManager.sendLightsToShader(basicShader);

  /*
    MODELS
  */
  Model guitar("./assets/models/backpack/backpack.obj");

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

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

    basicShader.setMat4("view", view);
    basicShader.setMat4("projection", projection);
    basicShader.setMat4("model", model);

    guitar.draw(basicShader);

    lightCubeShader.use();
    lightCubeShader.setMat4("view", view);
    lightCubeShader.setMat4("projection", projection);
    for (PointLight light : lightManager.pointLights) {
      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model, light.position);
      model = glm::scale(model, glm::vec3(light.scale));
      lightCubeShader.setMat4("model", model);
      glBindVertexArray(lightManager.lightCubeVAO_);
      glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    glfwSwapBuffers(window.window_);
    glfwPollEvents();
  }

  // clean / delete all of GLFW's resources that were allocated
  glDeleteProgram(basicShader.ID);
  glfwTerminate();
  return 0;
}