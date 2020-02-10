#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

GLuint loadShaders(const char* vertex_file_path, const char* fragment_file_path);
GLuint loadShaders();

#endif // SHADER_H
