#include <math.h>
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "camera.h"

// Cosine and Sine in degrees
#define Cos(x) (cos((x)*3.1415927/180))
#define Sin(x) (sin((x)*3.1415927/180))
#define ArcSin(x) (asin(x)*180/3.1415927)
#define ArcCos(x) (acos(x)*180/3.1415927)

Camera::Camera() {
  eye_x = eye_y = eye_z = 0;
  view_th = view_ph = 0;
  look_x = look_y = look_z = 0;
  mode = FIRST_PERSON_MODE;
}

void Camera::moveForward(double amount) {
  if (mode == FIRST_PERSON_MODE) {
    eye_x += amount*Sin(view_th)*Cos(view_ph);
    eye_y += amount*Sin(view_ph);
    eye_z += amount*Cos(view_th)*Cos(view_ph);
    updateLookat();
  }
}

void Camera::moveTo(double x, double y, double z) {
  eye_x = x;
  eye_y = y;
  eye_z = z;
  updateLookat();
}

void Camera::rotate(int th, int ph) {
  view_th += th;
  view_ph += ph;
  view_th %= 360;
  view_ph %= 360;
  updateLookat();
}

void Camera::setViewLocation(double x, double y, double z) {
  look_x = x;
  look_y = y;
  look_z = z;
  if (mode == FIRST_PERSON_MODE) {
    double d, dx, dy, dz;
    double xvt, zvt;
    dx = look_x - eye_x;
    dy = look_y - eye_y;
    dz = look_z - eye_z;
    d = sqrt(pow(dx,2) + pow(dy,2) + pow(dz,2));
    view_ph = ArcSin(dy/d);
    xvt = ArcSin((dx/d)/Cos(view_ph));
    zvt = ArcCos((dz/d)/Cos(view_ph));
    if (xvt > 0) {
      view_th = zvt;
    } else {
      view_th = -zvt;
    }
    view_th %= 360;
    view_ph %= 360;
    updateLookat();
  }
}

void Camera::firstPersonMode() {
  mode = FIRST_PERSON_MODE;
  updateLookat();
}

void Camera::fixedViewpointMode() {
  mode = FIXED_VIEWPOINT_MODE;
}

void Camera::look() {
  gluLookAt(eye_x, eye_y, eye_z, look_x, look_y, look_z, 0, Cos(view_ph), 0);
}

void Camera::look(double up) {
  gluLookAt(eye_x, eye_y, eye_z, look_x, look_y, look_z, 0, up, 0);
}

void Camera::updateLookat() {
  if (mode == FIRST_PERSON_MODE) {
    look_x = eye_x + Sin(view_th)*Cos(view_ph);
    look_y = eye_y + Sin(view_ph);
    look_z = eye_z + Cos(view_th)*Cos(view_ph);
  }
}
