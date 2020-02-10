#ifndef OPENGLCONTROLLER_H
#define OPENGLCONTROLLER_H

#define GLEW_STATIC
#include "GL/glew.h"
#include <iostream>
#include <QCursor>
#include <QObject>
#include "parser.h"
#include "function.h"
#include "vao.h"
#include "keyboardstatemap.h"
#include "glm/glm.hpp"
#include "camera.h"
#include "shader.h"

class OpenGLController{
public:
    OpenGLController();
    ~OpenGLController();
    void initialize();
    void paint();
    void update(KeyboardStateMap *ksMap, int dx, int dy);
    void addFunction(std::string fs);
    void deleteFunction(int index);
private:
    void computeMVP();
    std::vector<VAO*> graphs;
    GLuint shaderProgram;
    GLuint matrixID;
    glm::mat4 MVP;
    Camera camera;
};

#endif // OPENGLCONTROLLER_H
