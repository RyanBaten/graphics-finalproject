#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "cursor.h"

Cursor::Cursor() {
  alpha = 0.75;
}

void Cursor::draw() {
  glPushMatrix();
  glColor(1.0,0,0,alpha);
  glPopMatrix();
}

void Cursor::setTransparence(double a) {
  alpha = a;
}

void Cursor::setLocation(double x, double y, double z) {
  cursorX = x;
  cursorY = y;
  cursorZ = z;
}

void Cursor::move(double x, double y, double z) {
  cursorX += x;
  cursorY += y;
  cursorZ += z;
}

void Cursor::setMinZ(double _minZ) {
  minZ = _minZ;
}

void Cursor::setWidth(double _width) {
  width = _width;
}

void Cursor::getLocation(double* x, double* y, double* z) {
  *x = cursorX;
  *y = cursorY;
  *z = cursorZ;
}
