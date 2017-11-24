#ifndef TRACK_H
#define TRACK_H

#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <string>
#include <vector>

class Track {
  private:
    GLuint railTexture;
    GLuint middleTexture;
    double trackWidth;
    double railWidth;
    std::vector<double> userVertices;
    std::vector<double> trackVertices;
    std::vector<double> normals;
  public:
    Track();
    void draw();
    void clearVertices();
    void addVertex(double x, double y, double z);
    void generateTrack(double smoothness);
    void setTrackWidth(double w);
    void setRailWidth(double w);
    void setRailTexture(std::string fn);
    void setMiddleTexture(std::string fn);
};

#endif
