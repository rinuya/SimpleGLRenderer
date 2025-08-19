#ifndef ENTITY_H
#define ENTITY_H

#include <memory>
#include <vector>
#include "mesh.hpp"
#include "model.hpp"
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
  std::unique_ptr<Mesh> mesh_;

  MeshEntity() = default;

  MeshEntity(std::unique_ptr<Mesh> mesh, Transform transform);

  void draw(Shader& shader) const;

 private:
};

class ModelEntity : public Entity {
 public:
  std::unique_ptr<Model> model_;

  ModelEntity() = default;

  ModelEntity(std::unique_ptr<Model> model, Transform transform);

  void draw(Shader& shader) const;

 private:
};

#endif