#include "scene.hpp"

void Scene::addEntity(std::unique_ptr<Entity> entity) {
  rootEntities_.push_back(std::move(entity));
}

std::shared_ptr<Mesh> Scene::getOrCreateMesh(const char* key) {
  auto it = meshCache_.find(key);
  if (it != meshCache_.end()) {
    return it->second;
  }

  std::shared_ptr<Mesh> mesh;
  if (key == "box") {
    mesh = MeshFactory::makeBox();
  }
  meshCache_[key] = mesh;
  return mesh;
}

std::shared_ptr<Model> Scene::getOrCreateModel(const char* path) {
  auto it = modelCache_.find(path);
  if (it != modelCache_.end()) {
    return it->second;
  }

  std::shared_ptr<Model> model = std::make_shared<Model>(path);
  modelCache_[path] = model;
  return model;
}

void Scene::draw(Shader& shader) const {
  for (auto& entity : rootEntities_) {
    entity->draw(shader);
  }
}