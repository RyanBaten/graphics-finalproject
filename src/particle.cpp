#include "particle.h"

Particle::Particle(double _x, double _y, double _z, double _lifetime, double _velocity) {
  birth = 0;
  x = _x;
  y = _y;
  z = _z;
  lifetime = _lifetime;
  velocity = _velocity;
}

void Particle::setLifetime(double t) {
  lifetime = t;
}

void Particle::getLocation(double &_x, double &_y, double &_z) {
  _x = x;
  _y = y;
  _z = z;
}

void Particle::setDirection(double _x, double _y, double _z) {
  x_dir = _x;
  y_dir = _y;
  z_dir = _z;
}

int Particle::update() {
  lifetime--;
  x += x_dir*velocity;
  y += y_dir*velocity;
  z += z_dir*velocity;
  if (lifetime<0) return 1;
  return 0;
}
