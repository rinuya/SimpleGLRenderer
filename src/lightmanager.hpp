#ifndef LIGHTMANAGER_H
#define LIGHTMANAGER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "shader.hpp"
#include "shapes/unitCube.hpp"

constexpr unsigned int MAX_LIGHT_COUNT = 16;

struct DirectionalLight {
  glm::vec3 direction;

  glm::vec3 ambient;
  glm::vec3 diffuse;
  glm::vec3 specular;
};

/**
 * @brief
 *
 * Attenuation is calculated based on the formula:
 *
 * F_att = 1.0 / ( K_c + (K_l * d) + (K_q * d^2) )
 *
 * More info for values can be found here:
 * https://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation
 *
 * @param position
 * @param ambient
 * @param diffuse
 * @param specular
 * @param constant attenuation variable K_c
 * @param linear attenuation variable K_l
 * @param quadratic attenuation variable K_q
 * @param scale size of the light cube
 */
struct PointLight {
  glm::vec3 position;

  glm::vec3 ambient;
  glm::vec3 diffuse;
  glm::vec3 specular;

  float constant;
  float linear;
  float quadratic;

  float scale;  // size of rendered cube
};

/**
 * @brief
 *
 * Attenuation is calculated based on the formula:
 *
 * F_att = 1.0 / ( K_c + (K_l * d) + (K_q * d^2) )
 *
 * More info for values can be found here:
 * https://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation
 *
 * Soft edges are added by using `cutOff` and `outerCutOff`
 *
 * @param position
 * @param direction
 * @param ambient
 * @param diffuse
 * @param specular
 * @param cutOff angle between SpotDir and LightDir
 * @param outerCutOff angle between SpotDir and outerLightDir
 * @param constant attenuation variable K_c
 * @param linear attenuation variable K_l
 * @param quadratic attenuation variable K_q
 * @param scale size of the light cube
 */
struct SpotLight {
  glm::vec3 position;
  glm::vec3 direction;

  glm::vec3 ambient;
  glm::vec3 diffuse;
  glm::vec3 specular;

  float cutOff;
  float outerCutOff;

  float constant;
  float linear;
  float quadratic;

  float scale;  // size of rendered cube
};

class LightManager {
 public:
  // VAO to be used when drawing light cubes
  unsigned int lightCubeVAO_;

  std::vector<DirectionalLight> dirLights_;
  std::vector<PointLight> pointLights_;
  std::vector<SpotLight> spotLights_;

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
  unsigned int getDirectionalLightCount() const { return dirLights_.size(); }

  /**
   * @brief Get the PointLight count
   *
   * @return unsigned int
   */
  unsigned int getPointLightCount() const { return pointLights_.size(); }

  /**
   * @brief Get the SpotLight count
   *
   * @return unsigned int
   */
  unsigned int getSpotLightCount() const { return spotLights_.size(); }

  /**
   * @brief Adds a `DirectionalLight` to the LightManager.
   *
   * The added light will be rendered on consequent calls to the scene.
   *
   * @param light
   * @return true
   * @return false
   */
  bool addDirLight(DirectionalLight light);

  /**
   * @brief Adds a `PointLight` to the LightManager.
   *
   * The added light will be rendered on consequent calls to the scene.
   *
   * @param light
   * @return true on success,
   * @return false on failure
   */
  bool addPointLight(PointLight light);

  /**
   * @brief Adds a `SpotLight` to the LightManager.
   *
   * The added light will be rendered on consequent calls to the scene.
   *
   * @param light
   * @return true on success,
   * @return false on failure
   */
  bool addSpotLight(SpotLight light);

  /**
   * @brief Sets uniforms on Shader for all lights.
   *
   * Lights can be accessed on the shader from the following 3 arrays:
   *
   * `dirLights[]`
   *
   * `pointLights[]`
   *
   * `spotLights[]`
   *
   * @param shader
   */
  void sendLightsToShader(Shader& shader) const;

  /**
   * @brief Draws light sources as cubes for visualization purposes
   *
   */
  void drawLights(Shader& shader, glm::mat4 view, glm::mat4 projection) const;

 private:
  unsigned int lightCubeVBO_;
  unsigned int lightCount_;

  /**
   * @brief Creates the VAO to render a light source (currently just a square)
   *
   */
  void setupLightVAO();
};

#endif