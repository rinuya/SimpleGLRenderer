#ifndef MESH_FACTORY_H
#define MESH_FACTORY_H

#include <memory>

#include "mesh.hpp"

namespace MeshFactory {
/**
 * @brief Create a unit cube mesh.
 * @return std::unique_ptr<Mesh> Pointer to the new Mesh object.
 */
std::unique_ptr<Mesh> makeBox();

/**
 * @brief Create a flat plane mesh.
 * @return std::unique_ptr<Mesh> Pointer to the new Mesh object.
 */
std::unique_ptr<Mesh> makePlane();

/**
 * @brief Create a unit sphere mesh.
 * @return std::unique_ptr<Mesh> Pointer to the new Mesh object.
 */
std::unique_ptr<Mesh> makeSphere();
}  // namespace MeshFactory

#endif