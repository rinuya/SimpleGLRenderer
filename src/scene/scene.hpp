#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>

#include "scene/entitiy.hpp"
#include "shader.hpp"

class Scene {
 public:
  std::vector<std::unique_ptr<Entity>> rootEntities_;

  void addEntity(std::unique_ptr<Entity> entity);

  /**
   * @brief Draws entire Scene defined by `rootEntities` and their children.
   *
   */
  void draw(Shader& shader) const;

 private:
};

#endif