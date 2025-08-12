#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include <sstream>
#include <string>

class Shader {
 public:
  // the program ID (bound by OpenGL)
  unsigned int ID;

  // constructor reads and builds the shader
  Shader(const char* vertexPath, const char* fragmentPath);

  /**
   * @brief Bind this shader to be the active shader in OpenGL
   *
   * Use `use()` to activate the shader
   */
  void use();

  /**
   * @brief Set a Bool uniform for this shader
   *
   * @param name Uniform variable name
   * @param value Uniform value
   */
  void setBool(const std::string& name, bool value) const;

  /**
   * @brief Set an Int uniform for this shader
   *
   * @param name Uniform variable name
   * @param value Uniform value
   */
  void setInt(const std::string& name, int value) const;

  /**
   * @brief Set a Float uniform for this shader
   *
   * @param name Uniform variable name
   * @param value Uniform value
   */
  void setFloat(const std::string& name, float value) const;

  /**
   * @brief Set a `glm::vec3` uniform for this shader
   *
   * @param name Uniform variable name
   * @param vec Uniform value
   */
  void setVec3(const std::string& name, const glm::vec3& vec) const;

  /**
   * @brief Set a `glm::vec3` uniform for this shader
   *
   * @param name Uniform variable name
   * @param x Uniform value `glm::vec3.x`
   * @param y Uniform value `glm::vec3.y`
   * @param z Uniform value `glm::vec3.u`
   */
  void setVec3(const std::string& name, float x, float y, float z) const;

  /**
   * @brief Set a `glm::mat4` uniform for this shader
   *
   * @param name Uniform variable name
   * @param mat Uniform value
   */
  void setMat4(const std::string& name, const glm::mat4& mat) const;
};

#endif