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

struct PointLight {
  glm::vec3 position;
  glm::vec3 direction;
  glm::vec3 ambient;
  glm::vec3 diffuse;
  glm::vec3 specular;
  float constant;
  float linear;
  float quadratic;
  float scale;  // size of rendered cube
};

struct SpotLight {};

class LightManager {
 public:
  // VAO to be used when drawing light cubes
  unsigned int lightCubeVAO_;

  std::vector<DirectionalLight> dirLights;
  std::vector<PointLight> pointLights;
  std::vector<SpotLight> spotLights;

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

  /**
   * @brief Adds a `PointLight` to the LightManager.
   *
   * The added light will be rendered on consequent calls to the scene.
   * Attenuation is calculated based on the formula:
   *
   * F_att = 1.0 / ( K_c + (K_l * d) + (K_q * d^2) )
   *
   * More info for values can be found here:
   * https://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation
   *
   * @param position
   * @param direction
   * @param ambient
   * @param diffuse
   * @param specular
   * @param constant attenuation variable K_c
   * @param linear attenuation variable K_l
   * @param quadratic attenuation variable K_q
   * @param scale size of the light cube
   * @return true on success,
   * @return false on failure
   */
  bool addPointLight(glm::vec3 position,
                     glm::vec3 direction,
                     glm::vec3 ambient,
                     glm::vec3 diffuse,
                     glm::vec3 specular,
                     float constant = 1.0f,
                     float linear = 0.09f,
                     float quadratic = 0.032f,
                     float scale = 1.0f);

  void sendLightsToShader(Shader& shader);

 private:
  unsigned int lightCubeVBO_;
  unsigned int lightCount_;

  void setupLightVAO();
};

#endif