#include "lightmanager.hpp"

LightManager::LightManager() {
  lightCount_ = 0;
}

bool LightManager::addDirLight(glm::vec3 direction,
                               glm::vec3 ambient,
                               glm::vec3 diffuse,
                               glm::vec3 specular) {
  if (lightCount_ + 1 > MAX_LIGHT_COUNT) {
    return false;
  }

  DirectionalLight newLight;
  newLight.direction = direction;
  newLight.ambient = ambient;
  newLight.diffuse = diffuse;
  newLight.specular = specular;

  dirLights.push_back(newLight);
  lightCount_++;

  return true;
}

void LightManager::sendLightsToShader(Shader& shader) {
  shader.setInt("numDirLights", dirLights.size());

  for (int i = 0; i < dirLights.size(); i++) {
    std::string uniformPrefix = "dirLights[" + std::to_string(i) + "]";
    shader.setVec3(uniformPrefix + ".direction", dirLights[i].direction);
    shader.setVec3(uniformPrefix + ".ambient", dirLights[i].ambient);
    shader.setVec3(uniformPrefix + ".diffuse", dirLights[i].diffuse);
    shader.setVec3(uniformPrefix + ".specular", dirLights[i].specular);
  }

  shader.setInt("numPointLights", pointLights.size());

  shader.setInt("numSpotLights", spotLights.size());
}