#include "scene.hpp"

void Scene::addEntity(std::unique_ptr<Entity> entity) {
  rootEntities_.push_back(std::move(entity));
}

void Scene::draw(Shader& shader) const {
  for (auto& entity : rootEntities_) {
    entity->draw(shader);
  }
}