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
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 texCoords;
};

struct Texture {
  unsigned int id;
  std::string type;
  std::string path;  // empty if texture is generated
};

class Mesh {
 public:
  // mesh data
  std::vector<Vertex> vertices_;
  std::vector<unsigned int> indices_;
  std::vector<Texture> textures_;

  /**
   * @brief Construct a new Mesh object
   *
   * @param vertices
   * @param indices
   * @param textures
   */
  Mesh(std::vector<Vertex> vertices,
       std::vector<unsigned int> indices,
       std::vector<Texture> textures);

  /**
   * @brief Draws mesh to screen
   *
   * @param shader
   */
  void draw(Shader& shader);

  /**
   * @brief Draws mesh to screen (mono colored Mesh)
   *
   * @param shader
   */
  void draw(Shader& shader, glm::vec3 color);

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
