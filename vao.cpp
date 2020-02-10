#include "vao.h"
#include <cstddef>
#include <iostream>

VAO::VAO(MeshObject *mo) {
    this->mo = mo;
    // Init VAO
    glGenVertexArrays(1, &VAOID);
    glBindVertexArray(VAOID);
    glEnableVertexAttribArray(0);	// Enable vertex attribute
    glEnableVertexAttribArray(1);	// Enable color attribute

    // Vertex buffer
    glGenBuffers(1, &vertexVBO);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    glBufferData(GL_ARRAY_BUFFER, mo->vBytes, mo->vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Color buffer
    glGenBuffers(1, &colorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glBufferData(GL_ARRAY_BUFFER, mo->cBytes, mo->colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Index buffer
    glGenBuffers(1, &indexVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mo->iBytes, mo->indices, GL_STATIC_DRAW);

    // Unbind
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

VAO::~VAO() {
    glDeleteVertexArrays(1, &VAOID);
    glDeleteBuffers(1, &vertexVBO);
    glDeleteBuffers(1, &colorVBO);
    glDeleteBuffers(1, &indexVBO);
    delete mo;
}

void VAO::bind() {
    glBindVertexArray(VAOID);
}

GLuint VAO::ID() {
    return VAOID;
}

GLuint VAO::vertexID() {
    return vertexVBO;
}

GLuint VAO::colorID() {
    return colorVBO;
}

GLuint VAO::indexID() {
    return indexVBO;
}

size_t VAO::getSize() {
    return mo->iBytes;
}
