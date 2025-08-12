#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>

#include "shader.hpp"
#include "utils.hpp"

struct Vertex {
  glm::vec3 Position;
  glm::vec3 Normal;
  glm::vec2 TexCoords;
};

struct Texture {
  unsigned int id;
  std::string type;
  std::string path;
};

class Mesh {
 public:
  // mesh data
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  std::vector<Texture> textures;

  Mesh(std::vector<Vertex> vertices,
       std::vector<unsigned int> indices,
       std::vector<Texture> textures);

  /**
   * @brief Draws mesh to screen
   *
   * @param shader
   */
  void Draw(Shader& shader);

 private:
  // render data
  unsigned int VAO, VBO, EBO;

  /**
   * @brief Creates and maps VAO, VBO and EBO in OpenGL
   *
   */
  void setupMesh();
};

#endif
