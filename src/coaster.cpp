#include <math.h>
#include "coaster.h"
#include <stdio.h>

#define ArcCos(x) (acos(x)*180/3.1415927)

Coaster::Coaster() {
  min_velocity = 10;
  max_velocity = 40;
}

void Coaster::rotateToFace(double x, double y, double z) {
  double x_diff = x-x_location;
  double y_diff = y-y_location;
  double z_diff = z-z_location;
  double x2 = x_diff*x_diff;
  double z2 = z_diff*z_diff;
  double xzdist = sqrt(x2+z2);
  double dist = sqrt(x2+y_diff*y_diff+z2);
  double y_calc = -x_diff/dist;
  double z_calc = (x2+z2)/(xzdist*dist);
  if (y_calc>1) y_calc=1;
  if (y_calc<-1) y_calc=-1;
  if (z_calc>1) z_calc=1;
  if (z_calc<-1) z_calc=-1;
  y_rotation = ArcCos(y_calc)*(z_diff<0?-1:1);
  z_rotation = ArcCos(z_calc)*(y_diff<0?1:-1);
}

void Coaster::setScale(double _scale) {
  scale = _scale;
}

void Coaster::setVelocity(double _velocity) {
  velocity = _velocity;
}

void Coaster::increaseVelocity(double _velocity) {
  velocity += _velocity;
  if (velocity > max_velocity) velocity = max_velocity;
}

void Coaster::decreaseVelocity(double _velocity) {
  velocity -= _velocity;
  if (velocity < min_velocity) velocity = min_velocity;
}

void Coaster::setMinVelocity(double _velocity) {
  min_velocity = _velocity;
}

void Coaster::setMaxVelocity(double _velocity) {
  max_velocity = _velocity;
}

double Coaster::getVelocity() {
  return velocity;
}

void Coaster::draw() {
  // Call the object class draw function
  Object::draw();
}
