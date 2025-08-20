#include "unitCube.hpp"

// UnitCube::UnitCube() {
//   // setup VAO
//   glGenVertexArrays(1, &VAO_);
//   glBindVertexArray(VAO_);
//   // load vertex data
//   glGenBuffers(1, &VBO_);
//   glBindBuffer(GL_ARRAY_BUFFER, VBO_);
//   glBufferData(GL_ARRAY_BUFFER, sizeof(unitCubeVertices), unitCubeVertices,
//                GL_STATIC_DRAW);
//   // set position attribute
//   /* func(attr_pos, sizeof_vertex_attr, type_data, norm, stride, offset) */
//   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
//   (void*)0); glEnableVertexAttribArray(0);
//   // set normal vector
//   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
//                         (void*)(3 * sizeof(float)));
//   glEnableVertexAttribArray(1);

//   glBindVertexArray(0);
// }