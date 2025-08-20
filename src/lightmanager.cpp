#include "lightmanager.hpp"

LightManager::LightManager() {
  lightCount_ = 0;
  setupLightVAO();
}

bool LightManager::addDirLight(DirectionalLight light) {
  if (lightCount_ + 1 > MAX_LIGHT_COUNT) {
    return false;
  }
  dirLights_.push_back(light);
  lightCount_++;
  return true;
}

bool LightManager::addPointLight(PointLight light) {
  if (lightCount_ + 1 > MAX_LIGHT_COUNT) {
    return false;
  }
  pointLights_.push_back(light);
  lightCount_++;
  return true;
}

bool LightManager::addSpotLight(SpotLight light) {
  if (lightCount_ + 1 > MAX_LIGHT_COUNT) {
    return false;
  }
  spotLights_.push_back(light);
  lightCount_++;
  return true;
}

void LightManager::sendLightsToShader(Shader& shader) const {
  std::string uniformPrefix;

  shader.setInt("numDirLights", dirLights_.size());
  for (int i = 0; i < dirLights_.size(); i++) {
    uniformPrefix = "dirLights[" + std::to_string(i) + "]";
    shader.setVec3(uniformPrefix + ".direction", dirLights_[i].direction);
    shader.setVec3(uniformPrefix + ".ambient", dirLights_[i].ambient);
    shader.setVec3(uniformPrefix + ".diffuse", dirLights_[i].diffuse);
    shader.setVec3(uniformPrefix + ".specular", dirLights_[i].specular);
  }

  shader.setInt("numPointLights", pointLights_.size());
  for (int i = 0; i < pointLights_.size(); i++) {
    uniformPrefix = "pointLights[" + std::to_string(i) + "]";
    shader.setVec3(uniformPrefix + ".position", pointLights_[i].position);
    shader.setVec3(uniformPrefix + ".ambient", pointLights_[i].ambient);
    shader.setVec3(uniformPrefix + ".diffuse", pointLights_[i].diffuse);
    shader.setVec3(uniformPrefix + ".specular", pointLights_[i].specular);
    shader.setFloat(uniformPrefix + ".constant", pointLights_[i].constant);
    shader.setFloat(uniformPrefix + ".linear", pointLights_[i].linear);
    shader.setFloat(uniformPrefix + ".quadratic", pointLights_[i].quadratic);
  }

  shader.setInt("numSpotLights", spotLights_.size());
  for (int i = 0; i < spotLights_.size(); i++) {
    uniformPrefix = "spotLights[" + std::to_string(i) + "]";
    shader.setVec3(uniformPrefix + ".position", spotLights_[i].position);
    shader.setVec3(uniformPrefix + ".direction", spotLights_[i].direction);
    shader.setVec3(uniformPrefix + ".ambient", spotLights_[i].ambient);
    shader.setVec3(uniformPrefix + ".diffuse", spotLights_[i].diffuse);
    shader.setVec3(uniformPrefix + ".specular", spotLights_[i].specular);
    shader.setFloat(uniformPrefix + ".cutOff", spotLights_[i].cutOff);
    shader.setFloat(uniformPrefix + ".outerCutOff", spotLights_[i].outerCutOff);
    shader.setFloat(uniformPrefix + ".constant", spotLights_[i].constant);
    shader.setFloat(uniformPrefix + ".linear", spotLights_[i].linear);
    shader.setFloat(uniformPrefix + ".quadratic", spotLights_[i].quadratic);
  }
}

void LightManager::drawLights(Shader& shader,
                              glm::mat4 view,
                              glm::mat4 projection) const {
  shader.use();
  shader.setMat4("view", view);
  shader.setMat4("projection", projection);

  glBindVertexArray(lightCubeVAO_);

  for (PointLight light : pointLights_) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, light.position);
    model = glm::scale(model, glm::vec3(light.scale));
    shader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
  }

  for (SpotLight light : spotLights_) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, light.position);
    model = glm::scale(model, glm::vec3(light.scale));
    shader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
  }
}

// clang-format off
static float unitCubeVertices[36 * 6] = {
  // positions          // normals
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
  glBufferData(GL_ARRAY_BUFFER, sizeof(unitCubeVertices), unitCubeVertices,
               GL_STATIC_DRAW);
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