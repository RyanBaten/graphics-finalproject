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
    double trackWidth;
    double railWidth;
    double railHeight;
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
    void setRailHeight(double h);
    void setRailTexture(std::string fn);
    bool isEmpty();
    void getIthTrackVertex(int i, double &x, double &y, double &z);
};

#endif
