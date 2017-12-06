#ifndef OBJECT_H
#define OBJECT_H

#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <string>
#include <vector>

class Object {
  protected:
    GLuint texture;
    std::vector<double> vertexCoords;
    std::vector<double> normalCoords;
    std::vector<double> texCoords;
  public:
    Object();
    bool loadFile(const char* file);
    void loadTexture(const char* file);
    void draw(double x, double y, double z, double rx, double ry, double rz, double scale);
};

#endif
