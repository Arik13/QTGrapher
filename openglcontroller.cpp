#include "openglcontroller.h"
#include "meshgenerators.h"
#include <iterator>

OpenGLController::OpenGLController() {

}

OpenGLController::~OpenGLController() {
    for (unsigned int i = 0; i < graphs.size(); i++) {
        delete graphs[i];
    }
}

void OpenGLController::initialize() {
    //    std::string fs = "sin(10*(x^2+y^2))/10";
    // Boot Glew
    glewExperimental = GL_TRUE;
    glewInit();

    // Get shader program
    shaderProgram = loadShaders();
    matrixID = glGetUniformLocation(shaderProgram, "MVP");
    glEnable(GL_DEPTH_TEST);
    float directions[3] = {};
    MVP = camera.MVP(directions, 0.0f, 0.0f);
}

void OpenGLController::paint() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);
    for (unsigned int i = 0; i < graphs.size(); i++) {
        glBindVertexArray(graphs[i]->ID());
        int size = graphs[i]->getSize();
        glDrawElements(GL_LINES, size, GL_UNSIGNED_SHORT, nullptr);
    }
    glFinish();
}

void OpenGLController::update(KeyboardStateMap *ksMap, int dx, int dy) {
    float directions[3] = {};
    if ((*ksMap)[Qt::Key_W] || (*ksMap)[Qt::Key_S]) {
        directions[0] = ((*ksMap)[Qt::Key_W])? 1 : -1;
    }

    if ((*ksMap)[Qt::Key_D] || (*ksMap)[Qt::Key_A]) {
        directions[1] = ((*ksMap)[Qt::Key_D])? 1 : -1;
    }

    if ((*ksMap)[Qt::Key_Space] || (*ksMap)[Qt::Key_Shift]) {
        directions[2] = ((*ksMap)[Qt::Key_Space])? 1 : -1;
    }

    MVP = camera.MVP(directions, -dx, -dy);
}

void OpenGLController::addFunction(std::string fs) {
    // Parse function
    Function *f = parseFunction(fs);

    if (f == nullptr) return;
    GraphParameters gp;

    // Generate and load graph into gpu
    MeshObject *mo = generateGraph(gp, f);
    delete f;
    graphs.push_back(new VAO(mo));
}

void OpenGLController::deleteFunction(int index) {
    VAO *vao = graphs[index];
    graphs.erase(graphs.begin() + index);
    delete vao;
}
