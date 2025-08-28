#ifndef ENTITY_H
#define ENTITY_H

#include <memory>
#include <vector>
#include "scene/mesh.hpp"
#include "scene/model.hpp"
#include "scene/transform.hpp"
#include "shader.hpp"

// TODO: Add proper interface for Entity to be used by e.g. UI API

class Entity {
 public:
  std::string label_;
  Transform transform_;

  /**
   * @brief Construct an Entity.
   * @param label Name of the entity.
   * @param transform Initial transform.
   */
  Entity(std::string label, Transform transform)
      : label_(label), transform_(transform) {};

  /**
   * @brief Virtual destructor.
   */
  virtual ~Entity() = default;

  /**
   * @brief Draw the entity using the given shader.
   * @param shader Shader to use for rendering.
   */
  virtual void draw(Shader& shader) const = 0;
};

class MeshEntity : public Entity {
 public:
  std::shared_ptr<Mesh> mesh_;
  // in case of mono colored Mesh, this will be used
  bool useColor_;
  glm::vec3 color_;

  /**
   * @brief Construct a MeshEntity with a mesh.
   * @param label Name of the entity.
   * @param mesh Mesh data.
   * @param transform Initial transform.
   */
  MeshEntity(std::string label,
             std::shared_ptr<Mesh> mesh,
             Transform transform);

  /**
   * @brief Construct a MeshEntity with a mesh and color.
   * @param label Name of the entity.
   * @param mesh Mesh data.
   * @param transform Initial transform.
   * @param color Color to use for the mesh.
   */
  MeshEntity(std::string label,
             std::shared_ptr<Mesh> mesh,
             Transform transform,
             glm::vec3 color);

  /**
   * @brief Draw the mesh entity using the given shader.
   * @param shader Shader to use for rendering.
   */
  void draw(Shader& shader) const;
};

class ModelEntity : public Entity {
 public:
  std::shared_ptr<Model> model_;

  /**
   * @brief Construct a ModelEntity.
   * @param label Name of the entity.
   * @param model Model data.
   * @param transform Initial transform.
   */
  ModelEntity(std::string label,
              std::shared_ptr<Model> model,
              Transform transform);

  /**
   * @brief Draw the model entity using the given shader.
   * @param shader Shader to use for rendering.
   */
  void draw(Shader& shader) const;
};

#endif