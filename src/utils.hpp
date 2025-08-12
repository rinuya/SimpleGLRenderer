#ifndef UTILS_H
#define UTILS_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>

/**
 * @brief Loads a texture in a path from a specified directory
 *
 * @param path
 * @param directory
 * @param gamma
 * @return unsigned int `textureID`
 */
unsigned int loadTextureFromFile(const char* path,
                                 const std::string& directory,
                                 bool gamma = false);

#endif
