#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <unordered_map>
#include <vector>

#include "scene/entitiy.hpp"
#include "scene/mesh_factory.hpp"
#include "shader.hpp"

class Scene {
 public:
  std::vector<std::unique_ptr<Entity>> rootEntities_;
  // cache and reuse mesh info for duplicate objects
  std::unordered_map<std::string, std::shared_ptr<Mesh>> meshCache_;
  // cache and reuse model info for duplicate objects
  std::unordered_map<std::string, std::shared_ptr<Model>> modelCache_;

  /**
   * @brief Adds an `Entity` to `rootEntities_` and thereby to the Scene
   *
   * @param entity
   */
  void addEntity(std::unique_ptr<Entity> entity);

  /**
   * @brief Get or create the Mesh object
   *
   * @param key
   * @return std::shared_ptr<Mesh>
   */
  std::shared_ptr<Mesh> getOrCreateMesh(const std::string& key);

  /**
   * @brief Get or create the Model object
   *
   * @param path
   * @return std::shared_ptr<Model>
   */
  std::shared_ptr<Model> getOrCreateModel(const std::string& path);

  /**
   * @brief Draws entire Scene defined by `rootEntities` and their children.
   *
   */
  void draw(Shader& shader) const;

 private:
};

#endif