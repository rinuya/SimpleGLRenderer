#include "shader.hpp"

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
  // 1. retrieve the source code from filePath
  std::string vertexCode;
  std::string fragmentCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;
  // ensure ifstream objects can throw exceptions (usually, ifstream fails
  // silently)
  vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  std::stringstream vShaderStream, fShaderStream;
  try {
    vShaderFile.open(vertexPath);
    // read file buffer contents into streams
    vShaderStream << vShaderFile.rdbuf();
    vShaderFile.close();
    vertexCode = vShaderStream.str();

  } catch (std::ifstream::failure e) {
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    std::cout << "Issue at: " << vertexPath << std::endl;
  }

  try {
    fShaderFile.open(fragmentPath);
    // read file buffer contents into streams

    fShaderStream << fShaderFile.rdbuf();
    fShaderFile.close();
    fragmentCode = fShaderStream.str();

  } catch (std::ifstream::failure e) {
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    std::cout << "Issue at: " << fragmentPath << std::endl;
  }
  const char* vShaderCode = vertexCode.c_str();
  const char* fShaderCode = fragmentCode.c_str();

  // 2. compile shaders
  unsigned int vertex, fragment;
  int success;
  char infoLog[512];

  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);
  // print compile errors
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, NULL);
  glCompileShader(fragment);

  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  ID = glCreateProgram();
  glAttachShader(ID, vertex);
  glAttachShader(ID, fragment);
  glLinkProgram(ID);
  // print linking errors if any
  glGetProgramiv(ID, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(ID, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << infoLog << std::endl;
  }

  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

void Shader::use() {
  glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const {
  int boolLocation = glGetUniformLocation(ID, name.c_str());
  glUniform1i(boolLocation, (int)value);
}

void Shader::setInt(const std::string& name, int value) const {
  glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
  glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec3(const std::string& name, const glm::vec3& vec) const {
  glUniform3f(glGetUniformLocation(ID, name.c_str()), vec.x, vec.y, vec.z);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const {
  glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const {
  glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE,
                     &mat[0][0]);
}