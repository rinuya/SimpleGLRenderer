#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Defines several possible options for camera movement.
// Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement { FORWARD, BACKWARD, LEFT, RIGHT };

// Default camera yaw
const float YAW = -90.0f;
// Default camera pitch
const float PITCH = 0.0f;
// Default camera speed
const float SPEED = 2.5f;
// Default camera sensitivity
const float SENSITIVITY = 0.1f;
// Default camera FOV
const float FOV = 45.0f;

// An abstract camera class that processes input and calculates the
// corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera {
 public:
  // camera Attributes
  glm::vec3 Position;
  glm::vec3 Front;
  glm::vec3 Up;
  glm::vec3 Right;
  glm::vec3 WorldUp;
  // euler Angles
  float Yaw;
  float Pitch;
  // camera options
  float MovementSpeed;
  float MouseSensitivity;
  float Fov;

  /**
   * @brief Constructs a Camera object with optional initial position, up
   * vector, yaw, and pitch.
   *
   * @param position Initial position of the camera in world space. Defaults to
   * (0, 0, 0).
   * @param up       The world up vector. Defaults to (0, 1, 0).
   * @param yaw      Initial yaw angle (rotation around the Y axis). Defaults
   * to YAW constant.
   * @param pitch    Initial pitch angle (rotation around the X axis). Defaults
   * to PITCH constant.
   */
  Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
         glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
         float yaw = YAW,
         float pitch = PITCH);

  /**
   * @brief Constructs a Camera object with explicit position and up vector
   * components, yaw, and pitch.
   *
   * @param posX  X coordinate of the camera position in world space.
   * @param posY  Y coordinate of the camera position in world space.
   * @param posZ  Z coordinate of the camera position in world space.
   * @param upX   X component of the world up vector.
   * @param upY   Y component of the world up vector.
   * @param upZ   Z component of the world up vector.
   * @param yaw   Initial yaw angle (rotation around the Y axis).
   * @param pitch Initial pitch angle (rotation around the X axis).
   */
  Camera(float posX,
         float posY,
         float posZ,
         float upX,
         float upY,
         float upZ,
         float yaw,
         float pitch);

  /**
   * @brief Returns the view matrix calculated using Euler Angles and the
   * LookAt matrix.
   *
   * @return glm::mat4 The view transformation matrix.
   */
  glm::mat4 getViewMatrix();

  /**
   * @brief Processes keyboard input to move the camera position.
   *
   * @param direction The direction of camera movement (defined by
   * Camera_Movement enum).
   * @param deltaTime Time elapsed since last frame to maintain consistent
   * movement speed.
   */
  void processKeyboard(Camera_Movement direction, float deltaTime);

  /**
   * @brief Processes mouse movement input to adjust the camera's yaw and pitch
   * angles.
   *
   * @param xoffset Mouse movement offset in the X direction.
   * @param yoffset Mouse movement offset in the Y direction.
   * @param constrainPitch Whether to constrain the pitch angle to avoid screen
   * flipping (default true).
   */
  void processMouseMovement(float xoffset,
                            float yoffset,
                            GLboolean constrainPitch = true);

  /**
   * @brief Processes mouse scroll-wheel input to adjust the camera's field of
   * view (zoom).
   *
   * @param yoffset Scroll offset in the vertical direction.
   */
  void processMouseScroll(float yoffset);

 private:
  /**
   * @brief Updates the camera's Front, Right, and Up vectors from the current
   * Euler angles.
   *
   * This function recalculates the direction vectors to reflect changes in yaw
   * and pitch.
   */
  void updateCameraVectors();
};

#endif