#ifndef ENTITY_H
#define ENTITY_H

#include <memory>
#include <vector>
#include "scene/mesh.hpp"
#include "scene/model.hpp"
#include "scene/transform.hpp"
#include "shader.hpp"

class Entity {
 public:
  Transform transform_;
  Entity(Transform transform) : transform_(transform) {};
  virtual ~Entity() = default;
  virtual void draw(Shader& shader) const = 0;
};

class MeshEntity : public Entity {
 public:
  std::shared_ptr<Mesh> mesh_;
  // in case of mono colored Mesh, this will be used
  bool useColor_;
  glm::vec3 color_;

  MeshEntity() = default;

  MeshEntity(std::shared_ptr<Mesh> mesh, Transform transform);

  MeshEntity(std::shared_ptr<Mesh> mesh, Transform transform, glm::vec3 color);

  void draw(Shader& shader) const;

 private:
};

class ModelEntity : public Entity {
 public:
  std::shared_ptr<Model> model_;

  ModelEntity() = default;

  ModelEntity(std::shared_ptr<Model> model, Transform transform);

  void draw(Shader& shader) const;

 private:
};

#endif