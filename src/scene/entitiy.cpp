#include "scene/entitiy.hpp"

MeshEntity::MeshEntity(std::shared_ptr<Mesh> mesh, Transform transform)
    : Entity(transform), mesh_(std::move(mesh)) {
  useColor_ = false;
};

MeshEntity::MeshEntity(std::shared_ptr<Mesh> mesh,
                       Transform transform,
                       glm::vec3 color)
    : Entity(transform), mesh_(std::move(mesh)), color_(color) {
  useColor_ = true;
};

void MeshEntity::draw(Shader& shader) const {
  shader.setMat4("model", transform_.getModelMatrix());
  if (useColor_) {
    mesh_->draw(shader, color_);
  } else {
    mesh_->draw(shader);
  }
}

ModelEntity::ModelEntity(std::shared_ptr<Model> model, Transform transform)
    : Entity(transform), model_(std::move(model)) {};

void ModelEntity::draw(Shader& shader) const {
  shader.setMat4("model", transform_.getModelMatrix());
  model_->draw(shader);
}