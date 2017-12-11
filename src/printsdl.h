#ifndef PRINTSDL_H
#define PRINTSDL_H

#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

void Print(const char* format , ...);

#endif
