#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class Transform {
 public:
  glm::vec3 position_;
  glm::vec3 scale_;

  Transform(glm::vec3 position, glm::vec3 scale);

  /**
   * @brief Get the Model Matrix object
   *
   * @return glm::mat4
   */
  glm::mat4 getModelMatrix() const;

 private:
};

#endif