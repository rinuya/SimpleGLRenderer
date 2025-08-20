#include "mesh_factory.hpp"

namespace MeshFactory {
std::unique_ptr<Mesh> makeBox() {
  return std::make_unique<Mesh>(std::vector<Vertex>{},
                                std::vector<unsigned int>{},
                                std::vector<Texture>{});
}
}  // namespace MeshFactory