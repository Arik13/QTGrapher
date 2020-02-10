#version 400 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec4 vertexColor;
out vec4 color;
uniform mat4 MVP;

void main() {
        gl_Position = MVP * vec4(vertexPosition, 1);
        color = vertexColor;
};
