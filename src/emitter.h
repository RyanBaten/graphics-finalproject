#ifndef EMITTER_H
#define EMITTER_H

#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <vector>
#include <string>
#include "particle.h"

class Emitter {
  private:
    GLuint texture;
    bool on;
    int particleSize;
    double rate;
    double x,y,z;
    double last_t;
    double lifetime;
    double velocity;
    double breadth;
    std::vector<Particle*> particles;
  public:
    Emitter();
    ~Emitter();
    bool isOn();
    void turnOn();
    void turnOff();
    void loadTexture(std::string fn);
    void draw();
    void setRate(double _rate);
    void setTime(double _t);
    void setLifetime(double _t);
    void setVelocity(double _v);
    void setBreadth(double _breadth);
    void setLocation(double _x, double _y, double _z);
    void setSize(int size);
    void update(double t);
};

#endif
