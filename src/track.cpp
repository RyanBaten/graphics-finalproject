#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "track.h"

Track::Track() {
}

void Track::draw() {
}

void Track::clearVertices() {
  vertices.clear();
}

void Track::addVertex(double x, double y, double z) {
  vertices.push_back(x);
  vertices.push_back(y);
  vertices.push_back(z);
}
