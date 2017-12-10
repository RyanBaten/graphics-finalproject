#ifndef LOADIMAGE_H
#define LOADIMAGE_H

#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

GLuint loadImage(const char* filename);

#endif
