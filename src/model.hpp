#ifndef MODEL_H
#define MODEL_H

#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>

#include <iostream>
#include <string>
#include <vector>

#include "mesh.hpp"
#include "shader.hpp"

class Model {
 public:
  Model(const char* path);

  /**
   * @brief Draws all of the models meshes
   *
   * @param shader
   */
  void draw(Shader& shader);

 private:
  // model data
  std::vector<Mesh> meshes;
  std::string directory;
  std::vector<Texture> textures_loaded;

  /**
   * @brief Loads model with ASSIMP and recursively processes each Node
   *
   * @param path
   */
  void loadModel(std::string path);

  /**
   * @brief Processes the Nodes Meshes and recursively processes child Nodes
   *
   * @param node
   * @param scene
   */
  void processNode(aiNode* node, const aiScene* scene);

  /**
   * @brief Processes a Mesh and loads necessary Textures
   *
   * @param mesh
   * @param scene
   * @return Mesh
   */
  Mesh processMesh(aiMesh* mesh, const aiScene* scene);

  /**
   * @brief Hanldes Texture loading
   *
   * @param mat
   * @param type
   * @param typeName
   * @return std::vector<Texture>
   */
  std::vector<Texture> loadMaterialTextures(aiMaterial* mat,
                                            aiTextureType type,
                                            std::string typeName);
};

#endif