#include "meshgenerators.h"

//MeshObject* generateAxes(float axisLength) {
//    GLfloat axesVertices[] = {
//            axisLength, 0, 0,
//            -axisLength, 0, 0,
//            0, axisLength, 0,
//            0, -axisLength, 0,
//            0, 0, axisLength,
//            0, 0, -axisLength
//    };
//    GLfloat axesColors[] = {
//        1, 0, 0, 1,
//        1, 0, 0, 1,
//        0, 1, 0, 1,
//        0, 1, 0, 1,
//        0, 0, 1, 1,
//        0, 0, 1, 1
//    };

//    GLushort axesIndices[] = {
//        0, 1, 2, 3, 4, 5
//    };
//    MeshObject axes;
//    axes.vertices = axesVertices;
//    axes.colors = axesColors;
//    axes.indices = axesIndices;
//    axes.vBytes = sizeof(axesVertices);
//    axes.cBytes = sizeof(axesColors);
//    axes.iBytes = sizeof(axesIndices);
//    return &axes;
//}

GLfloat* calculateColors(GLfloat* vertices, int numOfColors, int resolution, int dim) {
//    const int numOfColors = resolution * resolution * (dim + 1);
    GLfloat* graphColors = new GLfloat[numOfColors];

    // Calculate the graph colors
    float colorSensitivity = 10;
    for (int i = 0; i < resolution; i++) {
        for (int j = 0; j < resolution; j++) {
            int k = i * resolution * dim + j * dim;
            int l = i * resolution * (dim + 1) + j * (dim + 1);
            float relativeZ = vertices[k + 1] / (1 / colorSensitivity);
            graphColors[l] = (relativeZ <= 0) ? abs(relativeZ) : 0;
            graphColors[l + 1] = 1 - abs(relativeZ);
            graphColors[l + 2] = (relativeZ >= 0) ? relativeZ : 0;
            graphColors[l + 3] = 1;
        }
    }
    return graphColors;
}

MeshObject *generateGraph(GraphParameters gp, Function *function) {
    // Get sampling of vertices from the function
    char vars[] = { 'x', 'y' };
    const int resolution = 250;
    const int dim = 3;
    GLfloat* graphVertices = calculateVertices(vars, resolution, dim, function, gp);
    int numOfVertices = resolution * resolution;
    const int numOfColors = resolution * resolution * (dim + 1);
    GLfloat* graphColors = calculateColors(graphVertices, numOfColors, resolution, dim);//new GLfloat[numOfColors];

    // Calculate the indices that describe a grid of the graph vertices
    const int indicesPerLine = 2;
    const int linesPerTrace = resolution - 1;
    const int tracesPerDim = resolution;
    const int indicesPerGraph = indicesPerLine * linesPerTrace * tracesPerDim * 2;
    GLushort* graphIndices = new GLushort[indicesPerGraph];

    // Calculate the indices representing the traces in the x direction
    for (int trace = 0; trace < tracesPerDim; trace++) {
        for (int line = 0; line < linesPerTrace; line++) {
            int k = line * indicesPerLine + trace * linesPerTrace * indicesPerLine;
            int l = line + trace * linesPerTrace + trace;
            graphIndices[k] = l;
            graphIndices[k + 1] = l + 1;
        }
    }

    // calculate the indices representing the traces in the y direction
    const int sI = indicesPerGraph / 2;
    for (int trace = 0; trace < tracesPerDim; trace++) {
        for (int line = 0; line < linesPerTrace; line++) {
            int k = line * indicesPerLine + trace * linesPerTrace * indicesPerLine;
            int l = k / 2;
            graphIndices[sI + k] = l;
            graphIndices[sI + k + 1] = l + tracesPerDim;
        }
    }
    MeshObject* graph = new MeshObject(
                graphVertices,
                graphColors,
                graphIndices,
                numOfVertices * sizeof(GLfloat) * dim,
                numOfColors * sizeof(GLfloat),
                indicesPerGraph * sizeof(GLushort)
                );
    return graph;
}

GLfloat* calculateVertices(char vars[], int resolution, int dim, Function* func, GraphParameters &gp) {
    int numOfScalars = dim * resolution * resolution;
    GLfloat* vertexArray = new GLfloat[numOfScalars];
    GLfloat xDif = gp.maxVisDomain - gp.minVisDomain;
    GLfloat yDif = gp.maxVisDomain - gp.minVisDomain;
    GLfloat xy[2];
    for (int i = 0; i < resolution; i++) {
        for (int j = 0; j < resolution; j++) {
            GLfloat x = gp.minVisDomain + xDif * (float(i) / (resolution - 1));
            GLfloat y = gp.minVisDomain + yDif * (float(j) / (resolution - 1));
            xy[0] = x;
            xy[1] = y;
            int k = i * resolution * dim + j * dim;
            vertexArray[k] = x;
            vertexArray[k + 1] = func->evaluate(vars, xy, 2);
            vertexArray[k + 2] = y;
        }
    }
    return vertexArray;
}

