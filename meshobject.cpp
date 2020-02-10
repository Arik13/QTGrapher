#include "meshobject.h"

MeshObject::MeshObject(
        float *vertices,
        float *colors,
        unsigned short *indices,
        int vBytes,
        int cBytes,
        int iBytes)
{
    this->vertices = vertices;
    this->colors = colors;
    this->indices = indices;
    this->vBytes = vBytes;
    this->cBytes = cBytes;
    this->iBytes = iBytes;
}

MeshObject::~MeshObject() {
    delete[] vertices;
    delete[] colors;
    delete[] indices;
}
