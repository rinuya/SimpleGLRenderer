#include "scene/transform.hpp"

Transform::Transform(glm::vec3 position, glm::vec3 scale)
    : position_(position), scale_(scale) {}

glm::mat4 Transform::getModelMatrix() const {
  glm::mat4 model(1.0f);
  model = glm::translate(model, position_);
  model = glm::scale(model, scale_);
  return model;
}