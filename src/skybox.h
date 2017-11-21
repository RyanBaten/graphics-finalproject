#ifndef SKYBOX_H
#define SKYBOX_H

#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <string>

class SkyBox {
  private:
    GLuint NTexture;
    GLuint STexture;
    GLuint ETexture;
    GLuint WTexture;
    GLuint UTexture;
    GLuint DTexture;
    double scale;
  public:
    SkyBox();
    SkyBox(double _scale);
    void setNTexture(std::string fn);
    void setSTexture(std::string fn);
    void setETexture(std::string fn);
    void setWTexture(std::string fn);
    void setUTexture(std::string fn);
    void setDTexture(std::string fn);
    void setScale(double _scale);
    void draw(double x, double y, double z);
};

#endif
