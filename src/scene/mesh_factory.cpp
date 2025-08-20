#include "mesh_factory.hpp"

namespace MeshFactory {
std::unique_ptr<Mesh> makeBox() {
  // clang-format off
  // 8 cube vertices (positions + normals + texcoords)
  std::vector<Vertex> vertices = {
    // positions           // normals           // texcoords
    {{-0.5f,-0.5f,-0.5f}, { 0.0f, 0.0f,-1.0f}, {0.0f, 0.0f}},
    {{ 0.5f,-0.5f,-0.5f}, { 0.0f, 0.0f,-1.0f}, {1.0f, 0.0f}},
    {{ 0.5f, 0.5f,-0.5f}, { 0.0f, 0.0f,-1.0f}, {1.0f, 1.0f}},
    {{-0.5f, 0.5f,-0.5f}, { 0.0f, 0.0f,-1.0f}, {0.0f, 1.0f}},

    {{-0.5f,-0.5f, 0.5f}, { 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
    {{ 0.5f,-0.5f, 0.5f}, { 0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
    {{ 0.5f, 0.5f, 0.5f}, { 0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
    {{-0.5f, 0.5f, 0.5f}, { 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},

    {{-0.5f, 0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
    {{-0.5f, 0.5f,-0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
    {{-0.5f,-0.5f,-0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
    {{-0.5f,-0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},

    {{ 0.5f, 0.5f, 0.5f}, { 1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
    {{ 0.5f, 0.5f,-0.5f}, { 1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
    {{ 0.5f,-0.5f,-0.5f}, { 1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
    {{ 0.5f,-0.5f, 0.5f}, { 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},

    {{-0.5f,-0.5f,-0.5f}, { 0.0f,-1.0f, 0.0f}, {0.0f, 1.0f}},
    {{ 0.5f,-0.5f,-0.5f}, { 0.0f,-1.0f, 0.0f}, {1.0f, 1.0f}},
    {{ 0.5f,-0.5f, 0.5f}, { 0.0f,-1.0f, 0.0f}, {1.0f, 0.0f}},
    {{-0.5f,-0.5f, 0.5f}, { 0.0f,-1.0f, 0.0f}, {0.0f, 0.0f}},

    {{-0.5f, 0.5f,-0.5f}, { 0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
    {{ 0.5f, 0.5f,-0.5f}, { 0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
    {{ 0.5f, 0.5f, 0.5f}, { 0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
    {{-0.5f, 0.5f, 0.5f}, { 0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}}
  };

  // 12 triangles (36 indices)
  std::vector<unsigned int> indices = {
    0,1,2,    2,3,0,     // back
    4,5,6,    6,7,4,     // front
    8,9,10,   10,11,8,   // left
    12,13,14, 14,15,12,  // right
    16,17,18, 18,19,16,  // bottom
    20,21,22, 22,23,20   // top
  };
  // clang-format on

  // no textures (fallback color in shader will be used)
  std::vector<Texture> textures;

  return std::make_unique<Mesh>(vertices, indices, textures);
}
}  // namespace MeshFactory