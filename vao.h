#ifndef VAO_H
#define VAO_H


#include <GL/glew.h>
#include "meshobject.h"

class VAO {
public:
    VAO(MeshObject *mo);
    ~VAO();
    void bind();
    GLuint ID();
    size_t getSize();
    GLuint vertexID();
    GLuint indexID();
    GLuint colorID();
private:
    GLuint VAOID = 0;
    GLuint vertexVBO = 0;
    GLuint colorVBO = 0;
    GLuint indexVBO = 0;
    MeshObject *mo;
};

#endif // VAO_H
