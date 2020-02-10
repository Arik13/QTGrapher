#ifndef MESHGENERATORS_H
#define MESHGENERATORS_H

#include "meshobject.h"
#include "graphparameters.h"
#include "function.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>
#include <iostream>
#include "function.h"
#include "graphparameters.h"

GLfloat* calculateVertices(char vars[], int resolution, int dim, Function* func, GraphParameters& gp);
MeshObject *generateGraph(GraphParameters gp, Function* function);

#endif // MESHGENERATORS_H
