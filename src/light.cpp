#include <math.h>
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "light.h"

// Sine and Cosine in degrees
#define Sin(x) (sin((x)*3.1415927/180))
#define Cos(x) (cos((x)*3.1415927/180))

Light::Light(GLenum l) {
  color_r = color_g = color_b = 0.7;
  ambient = 0.3;
  diffuse = 0.5;
  specular = 0;
  updateAmbient();
  Ambient[3] = 1;
  updateDiffuse();
  Diffuse[3] = 1;
  updateSpecular();
  Specular[3] = 1;
  Position[0] = 0;
  Position[1] = 0;
  Position[2] = 0;
  Position[3] = 1;
  pos_x = pos_y = pos_z = 0;
  indicator = INDICATOR_OFF;
  light = l;
}

void Light::showIndicator() {
  int th, ph;
  int inc = 10;
  // Want the light indicator to be unaffected by light
  glDisable(GL_LIGHTING);
  glPushMatrix();
  glTranslated(Position[0], Position[1], Position[2]);
  glScaled(0.5, 0.5, 0.5);
  // Adapted sphere function from ex13
  glColor3f(1,1,1);
  for (ph=-90; ph<90; ph+=inc) {
    glBegin(GL_QUAD_STRIP);
    for (th=0; th<=360; th+=2*inc) {
      glVertex3f(Sin(th)*Cos(ph), Cos(th)*Cos(ph), Sin(ph));
      glVertex3f(Sin(th)*Cos(ph+inc), Cos(th)*Cos(ph+inc), Sin(ph+inc));
    }
    glEnd();
  }
  glEnable(GL_LIGHTING);
  glPopMatrix();
}

void Light::moveTo(double x, double y, double z) {
  pos_x = x;
  pos_y = y;
  pos_z = z;
  Position[0] = pos_x;
  Position[1] = pos_y;
  Position[2] = pos_z;
}

void Light::updateAmbient() {
  Ambient[0] = color_r * ambient;
  Ambient[1] = color_g * ambient;
  Ambient[2] = color_b * ambient;
}

void Light::updateDiffuse() {
  Diffuse[0] = color_r * diffuse;
  Diffuse[1] = color_g * diffuse;
  Diffuse[2] = color_b * diffuse;
}

void Light::updateSpecular() {
  Specular[0] = color_r * specular;
  Specular[1] = color_g * specular;
  Specular[2] = color_b * specular;
}

void Light::setColor(double r, double g, double b) {
  color_r = r;
  color_g = g;
  color_b = b;
}

void Light::setAmbient(double a) {
  ambient = a;
  ambient = fmax(0, fmin(1, ambient));
  updateAmbient();
}

void Light::setDiffuse(double d) {
  diffuse = d;
  diffuse = fmax(0, fmin(1, diffuse));
  updateDiffuse();
}

void Light::setSpecular(double s) {
  specular = s;
  specular = fmax(0, fmin(1, specular));
  updateSpecular();
}

void Light::indicatorOn() {
  indicator = INDICATOR_ON;
}

void Light::indicatorOff() {
  indicator = INDICATOR_OFF;
}

void Light::increaseIntensity(double a, double d, double s) {
  ambient += a;
  diffuse += d;
  specular += s;
  ambient = fmax(0, fmin(1, ambient));
  diffuse = fmax(0, fmin(1, diffuse));
  specular = fmax(0, fmin(1, specular));
  updateAmbient();
  updateDiffuse();
  updateSpecular();
}

void Light::indicatorToggle() {
  if (indicator == INDICATOR_OFF) {
    indicator = INDICATOR_ON;
  } else {
    indicator = INDICATOR_OFF;
  }
}

void Light::display() {
  if (indicator == INDICATOR_ON) {
    showIndicator();
  }
  glEnable(light);
  glLightfv(light, GL_AMBIENT, Ambient);
  glLightfv(light, GL_DIFFUSE, Diffuse);
  glLightfv(light, GL_SPECULAR, Specular);
  glLightfv(light, GL_POSITION, Position);
}
