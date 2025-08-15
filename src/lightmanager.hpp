#ifndef LIGHTMANAGER_H
#define LIGHTMANAGER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "shader.hpp"

constexpr unsigned int MAX_LIGHT_COUNT = 16;

struct DirectionalLight {
  glm::vec3 direction;

  glm::vec3 ambient;
  glm::vec3 diffuse;
  glm::vec3 specular;
};

struct PointLight {};

struct SpotLight {};

class LightManager {
 public:
  /**
   * @brief Construct a new Light Manager object
   *
   */
  LightManager();

  /**
   * @brief Get the total Light count
   *
   * @return unsigned int
   */
  unsigned int getLightCount() const { return lightCount_; }

  /**
   * @brief Get the DirectionalLight count
   *
   * @return unsigned int
   */
  unsigned int getDirectionalLightCount() const { return dirLights.size(); }

  /**
   * @brief Get the PointLight count
   *
   * @return unsigned int
   */
  unsigned int getPointLightCount() const { return pointLights.size(); }

  /**
   * @brief Get the SpotLight count
   *
   * @return unsigned int
   */
  unsigned int getSpotLightCount() const { return spotLights.size(); }

  /**
   * @brief Adds a `DirectionalLight` to the LightManager.
   *
   * The added light will be rendered on consequent calls to the scene.
   *
   * @param direction
   * @param ambient
   * @param diffuse
   * @param specular
   * @return true on success,
   * @return false on failure
   */
  bool addDirLight(glm::vec3 direction,
                   glm::vec3 ambient,
                   glm::vec3 diffuse,
                   glm::vec3 specular);

  void sendLightsToShader(Shader& shader);

 private:
  std::vector<DirectionalLight> dirLights;
  std::vector<PointLight> pointLights;
  std::vector<SpotLight> spotLights;

  unsigned int lightCount_;
};

#endif