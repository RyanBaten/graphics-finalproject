#ifndef GROUND_H
#define GROUND_H

#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <string>

class Ground {
  private:
    GLuint texture;
    int sizeX; 
    int sizeY; 
    double scale;
    double **normals;
    double **vertices;
  public:
    Ground(double _sizeX, double _sizeY);
    ~Ground();
    void setTexture(std::string fn);
    void setScale(double _scale);
    void generateVertices(double min, double max, double maxDiff);
    void draw(double x, double y, double z);
};

#endif
