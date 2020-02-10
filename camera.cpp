#define _USE_MATH_DEFINES

#include <math.h>
#include "camera.h"
#include <iostream>

Camera::Camera() {
    flySpeed = 0.1f;
    turnSpeed = 0.01f;
    yawAngle = float(M_PI);
    pitchAngle = 0.0f;
    position = glm::vec3(0, 0, 0);
}

glm::mat4 Camera::MVP(float *directions, float dYawAngle, float dPitchAngle) {
    // Increment orientation by given amount
    yawAngle += dYawAngle * turnSpeed;
    pitchAngle += dPitchAngle * turnSpeed;

    // Prevent pitch angle from going past -90 and 90 degrees, with 0 being on the horizon
    // Prevents flipping head over heels
    if (pitchAngle < -float(M_PI/2)) pitchAngle = -float(M_PI/2);
    if (pitchAngle > float(M_PI/2)) pitchAngle = float(M_PI/2);

    // Calculate orientation vector from angles
    glm::vec3 orientation = glm::vec3(
            cos(pitchAngle) * sin(yawAngle),
            sin(pitchAngle),
            cos(pitchAngle) * cos(yawAngle)
        );

    // Calculate right vector
    glm::vec3 right = glm::vec3(
            sin(yawAngle - 3.14f / 2.0f),
            0,
            cos(yawAngle - 3.14f / 2.0f)
        );

    // Calculate up vector (the normal to the plane of the forward and right vectors)
    glm::vec3 up = glm::cross(right, orientation);

    // Increment the position in the forward/back, right/left and up/down directions
    position += (orientation * directions[0] * flySpeed);
    position += (right * directions[1] * flySpeed);
    position += (glm::vec3(0, 1, 0) * directions[2] * flySpeed);

    // Calculate the projection, view and model matrices (model matrix is just an identity matrix for now)
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(
                position,
                position + orientation,
                up
            );
    glm::mat4 model = glm::mat4(1.0);

    // Return MVP matrix (matrix multiplication must occur in opposite order of intuition)
    return projection * view * model;
}

