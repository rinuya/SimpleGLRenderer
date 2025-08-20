#ifndef MESH_FACTORY_H
#define MESH_FACTORY_H

#include <memory>

#include "mesh.hpp"

namespace MeshFactory {
std::unique_ptr<Mesh> makeBox();
std::unique_ptr<Mesh> makePlane();
std::unique_ptr<Mesh> makeSphere();
}  // namespace MeshFactory

#endif