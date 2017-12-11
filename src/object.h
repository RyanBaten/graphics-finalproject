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
    double scale;
    double x_location, y_location, z_location;
    double x_rotation, y_rotation, z_rotation;
    GLuint texture;
    std::vector<double> vertexCoords;
    std::vector<double> normalCoords;
    std::vector<double> texCoords;
  public:
    Object();
    bool loadFile(const char* file);
    void loadTexture(const char* file);
    void moveTo(double x, double y, double z);
    void rotate(double x, double y, double z);
    void setScale(double _scale);
    void draw();
};

#endif
