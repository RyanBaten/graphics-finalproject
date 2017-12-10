#include <math.h>
#include "coaster.h"
#include <stdio.h>

#define ArcCos(x) (acos(x)*180/3.1415927)

Coaster::Coaster() {
  scale = 1;
  x_location = 0;
  y_location = 0;
  z_location = 0;
  x_rotation = 0;
  y_rotation = 0;
  z_rotation = 0;
}

void Coaster::rotateToFace(double x, double y, double z) {
  double x_diff = x-x_location;
  double y_diff = y-y_location;
  double z_diff = z-z_location;
  double x2 = x_diff*x_diff;
  double z2 = z_diff*z_diff;
  double xzdist = sqrt(x2+z2);
  double dist = sqrt(x2+y_diff*y_diff+z2);
  if (dist == 0) return;
  if (xzdist == 0) return;
  
  y_rotation = ArcCos(-x_diff/dist)*(z_diff<0?-1:1);
  z_rotation = ArcCos((x2+z2)/(xzdist*dist))*(y_diff<0?-1:1);
}

void Coaster::moveTo(double x, double y, double z) {
  x_location = x;
  y_location = y;
  z_location = z;
}

void Coaster::setScale(double _scale) {
  scale = _scale;
}

void Coaster::setVelocity(double _velocity) {
  velocity = _velocity;
}

double Coaster::getVelocity() {
  return velocity;
}

void Coaster::draw() {
  // Pass in the coaster's variables to the object class draw function
  Object::draw(x_location, y_location, z_location, x_rotation, y_rotation, z_rotation, scale);
}
