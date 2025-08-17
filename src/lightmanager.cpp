#include "lightmanager.hpp"

LightManager::LightManager() {
  lightCount_ = 0;
  setupLightVAO();
}

bool LightManager::addDirLight(DirectionalLight light) {
  if (lightCount_ + 1 > MAX_LIGHT_COUNT) {
    return false;
  }
  dirLights.push_back(light);
  lightCount_++;
  return true;
}

bool LightManager::addPointLight(PointLight light) {
  if (lightCount_ + 1 > MAX_LIGHT_COUNT) {
    return false;
  }
  pointLights.push_back(light);
  lightCount_++;
  return true;
}

bool LightManager::addSpotLight(SpotLight light) {
  if (lightCount_ + 1 > MAX_LIGHT_COUNT) {
    return false;
  }
  spotLights.push_back(light);
  lightCount_++;
  return true;
}

void LightManager::sendLightsToShader(Shader& shader) {
  std::string uniformPrefix;

  shader.setInt("numDirLights", dirLights.size());
  for (int i = 0; i < dirLights.size(); i++) {
    uniformPrefix = "dirLights[" + std::to_string(i) + "]";
    shader.setVec3(uniformPrefix + ".direction", dirLights[i].direction);
    shader.setVec3(uniformPrefix + ".ambient", dirLights[i].ambient);
    shader.setVec3(uniformPrefix + ".diffuse", dirLights[i].diffuse);
    shader.setVec3(uniformPrefix + ".specular", dirLights[i].specular);
  }

  shader.setInt("numPointLights", pointLights.size());
  for (int i = 0; i < pointLights.size(); i++) {
    uniformPrefix = "pointLights[" + std::to_string(i) + "]";
    shader.setVec3(uniformPrefix + ".position", pointLights[i].position);
    shader.setVec3(uniformPrefix + ".ambient", pointLights[i].ambient);
    shader.setVec3(uniformPrefix + ".diffuse", pointLights[i].diffuse);
    shader.setVec3(uniformPrefix + ".specular", pointLights[i].specular);
    shader.setFloat(uniformPrefix + ".constant", pointLights[i].constant);
    shader.setFloat(uniformPrefix + ".linear", pointLights[i].linear);
    shader.setFloat(uniformPrefix + ".quadratic", pointLights[i].quadratic);
  }

  shader.setInt("numSpotLights", spotLights.size());
  for (int i = 0; i < spotLights.size(); i++) {
    uniformPrefix = "spotLights[" + std::to_string(i) + "]";
    shader.setVec3(uniformPrefix + ".position", spotLights[i].position);
    shader.setVec3(uniformPrefix + ".direction", spotLights[i].direction);
    shader.setVec3(uniformPrefix + ".ambient", spotLights[i].ambient);
    shader.setVec3(uniformPrefix + ".diffuse", spotLights[i].diffuse);
    shader.setVec3(uniformPrefix + ".specular", spotLights[i].specular);
    shader.setFloat(uniformPrefix + ".cutOff", spotLights[i].cutOff);
    shader.setFloat(uniformPrefix + ".outerCutOff", spotLights[i].outerCutOff);
    shader.setFloat(uniformPrefix + ".constant", spotLights[i].constant);
    shader.setFloat(uniformPrefix + ".linear", spotLights[i].linear);
    shader.setFloat(uniformPrefix + ".quadratic", spotLights[i].quadratic);
  }
}

// clang-format off
float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};
// clang-format on

void LightManager::setupLightVAO() {
  // setup light VAO
  glGenVertexArrays(1, &lightCubeVAO_);
  glBindVertexArray(lightCubeVAO_);
  // load vertex data
  glGenBuffers(1, &lightCubeVBO_);
  glBindBuffer(GL_ARRAY_BUFFER, lightCubeVBO_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  // set position attribute
  /* func(attr_pos, sizeof_vertex_attr, type_data, norm, stride, offset) */
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // set normal vector
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);
}