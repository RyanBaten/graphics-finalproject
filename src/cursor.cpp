#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "cursor.h"

Cursor::Cursor() {
  alpha = 0.75;
  width = 0.5;
  color[0] = 1.0;
  color[1] = 1.0;
  color[2] = 1.0;
}

void Cursor::draw() {
  glPushMatrix();
  // Translation and scaling
  glTranslated(cursorX,0,cursorZ);
  glScaled(width,width,width);
  // Enabling transparency
  glEnable(GL_BLEND);
  glDepthMask(0);
  glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);
  glColor4f(color[0],color[1],color[2],alpha);
  // Draw cube
  glBegin(GL_QUADS);
    // Front
    glNormal3f(0,0,1);
    glVertex3f(-1,minY,-1);
    glVertex3f(-1,cursorY,-1);
    glVertex3f(1,cursorY,-1);
    glVertex3f(1,minY,-1);
    // Back
    glNormal3f(0,0,-1);
    glVertex3f(-1,minY,1);
    glVertex3f(-1,cursorY,1);
    glVertex3f(1,cursorY,1);
    glVertex3f(1,minY,1);
    // Right
    glNormal3f(-1,0,0);
    glVertex3f(1,minY,-1);
    glVertex3f(1,cursorY,-1);
    glVertex3f(1,cursorY,1);
    glVertex3f(1,minY,1);
    // Left
    glNormal3f(1,0,0);
    glVertex3f(-1,minY,-1);
    glVertex3f(-1,cursorY,-1);
    glVertex3f(-1,cursorY,1);
    glVertex3f(-1,minY,1);
  glEnd();
  // Slightly more opaque top and bottom
  if (alpha > 0.5) glColor4f(color[0],color[1],color[2],alpha-0.2);
  glBegin(GL_QUADS);
    // Top
    glNormal3f(0,1,0);
    glVertex3f(-1,cursorY,-1);
    glVertex3f(-1,cursorY,1);
    glVertex3f(1,cursorY,1);
    glVertex3f(1,cursorY,-1);
    // Bottom
    glNormal3f(0,-1,0);
    glVertex3f(-1,minY,-1);
    glVertex3f(-1,minY,1);
    glVertex3f(1,minY,1);
    glVertex3f(1,minY,-1);
  glEnd();
  glDepthMask(1);
  glDisable(GL_BLEND);
  glPopMatrix();
  glColor4f(1.0,1.0,1.0,1.0);
}

void Cursor::setTransparency(double a) {
  alpha = a;
}

void Cursor::setLocation(double x, double y, double z) {
  cursorX = x;
  cursorY = y;
  cursorZ = z;
  cursorY = (cursorY<minY ? minY : cursorY);
}

void Cursor::move(double x, double y, double z) {
  cursorX += x;
  cursorY += y;
  cursorZ += z;
  cursorY = (cursorY<minY ? minY : cursorY);
}

void Cursor::setMinY(double _minY) {
  minY = _minY;
}

void Cursor::setWidth(double _width) {
  width = _width/2;
}

void Cursor::setColor(double r, double g, double b) {
  color[0] = r;
  color[1] = g;
  color[2] = b;
}

void Cursor::getLocation(double* x, double* y, double* z) {
  *x = cursorX;
  *y = cursorY;
  *z = cursorZ;
}
