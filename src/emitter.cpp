#include "load_image.h"
#include "emitter.h"
#include <stdlib.h>
#include <math.h>

double getFRand() {
  return ((float)rand())/1000;
}

Emitter::Emitter() {
  on = false;
}

Emitter::~Emitter() {
  // Clean up the particles array by freeing allocated memory
  int iterations = particles.size();
  for (int i=0; i<iterations; i++) {
    delete particles.at(i);
  }
}

bool Emitter::isOn() {
  return on;
}

void Emitter::turnOn() {
  on = true;
}

void Emitter::turnOff() {
  on = false;
}

void Emitter::loadTexture(std::string fn) {
  texture = loadImage(fn.c_str());
}

// Used to draw the particles themselves
void Emitter::draw() {
  if (!isOn()) return;
  int iterations = particles.size();
  double x,y,z;

  glPushMatrix();
  // Enable Textures
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture);
  // Point sprites are 2d images that get put in place of points
  glEnable(GL_POINT_SPRITE);
  glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
  glPointSize(particleSize);
  // Want transparency to work with images for particles
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  // Must mask the a buffer to have the textures not fight with eachother
  glDepthMask(GL_FALSE);
  glBegin(GL_POINTS);
    // Draw a point for each particle in the vector
    for (int i=0; i<iterations; i++) {
      particles.at(i)->getLocation(x,y,z);
      glVertex3f(x,y,z);
    }
  glEnd();
  glDepthMask(GL_TRUE);
  glDisable(GL_BLEND);
  glDisable(GL_POINT_SPRITE);
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();
}

void Emitter::setRate(double _rate) {
  rate = _rate;
}

void Emitter::setTime(double _t) {
  last_t = _t;
}

void Emitter::setLifetime(double _t) {
  lifetime = _t;
}

void Emitter::setVelocity(double _v) {
  velocity = _v;
}

void Emitter::setBreadth(double _breadth) {
  breadth = _breadth;
}

void Emitter::setLocation(double _x, double _y, double _z) {
  x = _x;
  y = _y;
  z = _z;
}

void Emitter::setSize(int size) {
  particleSize = size;
}

void Emitter::update(double t) {
  int particle_count, lifetime_rand;
  double velocity_rand;
  int iterations = particles.size();
  std::vector<int> deaths;
  // Addition of new particles
  if (t-last_t>rate) {
    particle_count = (t-last_t)/rate;
    for (int i=0; i<particle_count; i++) {
      // Want variation in lifetime so allow the second half of lifetime to be random
      lifetime_rand = fmod(rand(), lifetime/2) + lifetime/2;
      // Want variation in velocity
      velocity_rand = fmod(getFRand(), velocity/2) + velocity/2;
      // Generate new particle
      Particle *newParticle = new Particle(x,y,z,lifetime_rand,velocity_rand);
      newParticle->setDirection(fmod(getFRand(),breadth)-breadth/2,1,fmod(getFRand(),breadth)-breadth/2);
      particles.push_back(newParticle);
    }
    last_t = t;
  }
  // Find out which particles died
  for (int i=0; i<iterations; i++) {
    if (particles.at(i)->update()) {
      deaths.push_back(i);
    }
  }
  // Remove dead particles
  iterations = deaths.size();
  for (int i=iterations-1; i>=0; i--) {
    delete particles.at(deaths.at(i));
    particles.erase(particles.begin() + deaths.at(i));
  }
}
