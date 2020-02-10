#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/*
 * Keeps track of its own position and orientation in vector space. Takes commands to move or rotate
 * and gives back a 4D MVP matrix that is used by openGL to render vertex objects to the screen
 */
class Camera {
public:
    Camera();
    glm::mat4 MVP(float* directions, float dYawAngle, float dPitchAngle);
private:
    glm::vec3 position;
    float yawAngle;
    float pitchAngle;
    float flySpeed;
    float turnSpeed;
};

#endif // CAMERA_H
