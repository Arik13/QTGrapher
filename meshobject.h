#ifndef MESHOBJECT_H
#define MESHOBJECT_H

#pragma once

class MeshObject {
public:
    MeshObject(
            float* vertices,
            float* colors,
            unsigned short* indices,
            int vBytes,
            int cBytes,
            int iBytes
            );
    ~MeshObject();
private:
    float* vertices;
    float* colors;
    unsigned short* indices;
    int vBytes;
    int cBytes;
    int iBytes;
    friend class VAO;
};

#endif // MESHOBJECT_H
