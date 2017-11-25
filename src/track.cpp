#include <math.h>
#include "track.h"
#include "load_image.h"

#include <stdio.h>

#define pi 3.14159265

Track::Track() {
}

void Track::draw() {
  int trackSegments = trackVertices.size()-3;

//  glEnable(GL_TEXTURE_2D);
//  glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
  glPushMatrix();
  // Draw Railing
  glColor3f(1.0,1.0,1.0);
  glLineWidth(10);
//  glBegin(GL_QUADS);
//    for (int i=0; i<trackSegments; i+=3) {
//      glNormal3f(0,0,1);
//      glVertex3f(trackVertices.at(i),trackVertices.at(i+1),trackVertices.at(i+2));
//      glVertex3f(trackVertices.at(i+3),trackVertices.at(i+4),trackVertices.at(i+5));
//      glVertex3f(trackVertices.at(i+3)+1,trackVertices.at(i+4),trackVertices.at(i+5)+1);
//      glVertex3f(trackVertices.at(i)+1,trackVertices.at(i+1),trackVertices.at(i+2)+1);
//    }
  glBegin(GL_LINES);
    for (int i=0; i<trackSegments; i+=3) {
      glVertex3f(trackVertices.at(i),trackVertices.at(i+1),trackVertices.at(i+2));
    }
  glEnd();
  glPopMatrix();
//  glDisable(GL_TEXTURE_2D);
}
 
void Track::clearVertices() {
  userVertices.clear();
  trackVertices.clear();
}

void Track::addVertex(double x, double y, double z) {
  int size = userVertices.size();
  userVertices.push_back(x);
  userVertices.push_back(y);
  userVertices.push_back(z);
  if (size >= 6) {
    double dx,dy,dz;
    dx = x-userVertices.at(size-3);
    dy = y-userVertices.at(size-2);
    dz = z-userVertices.at(size-1);
    userVertices.push_back(x+0.5*dx);
    userVertices.push_back(y+0.5*dy);
    userVertices.push_back(z+0.5*dz);
  } 
}

void Track::generateTrack(double smoothness) {
  int size = userVertices.size();
  double t;
  double distance;
  double iterations;
  double x0,y0,z0,x1,y1,z1,x2,y2,z2;
  double result_x, result_y, result_z;
  // Clear current vertices
  trackVertices.clear();
  // For each set of vertices, get points from 3 or 2 point Bezier curve
  for (int i=0; i<size; i+=6) {
    if (size-i >= 9) {
      // Get the three points to use for Bezier curve
      x0 = userVertices.at(i);
      y0 = userVertices.at(i+1);
      z0 = userVertices.at(i+2);
      x1 = userVertices.at(i+3);
      y1 = userVertices.at(i+4);
      z1 = userVertices.at(i+5);
      x2 = userVertices.at(i+6);
      y2 = userVertices.at(i+7);
      z2 = userVertices.at(i+8);
      // Use length of lines through points as approximation for distance
      distance = sqrt(pow(x1-x0,2) + pow(y1-y0,2) + pow(z1-z0,2)) +
                 sqrt(pow(x2-x1,2) + pow(y2-y1,2) + pow(z2-z1,2));
      // Calculate number of subsections to use
      iterations = distance/smoothness - smoothness;
      // Generate points using 3 point Bezier curve
      for (int j=1; j<iterations; j++) {
        t = j/iterations;
        result_x = pow(t,2)*x2 + 2*(1-t)*t*x1 + pow(1-t,2)*x0;
        result_y = pow(t,2)*y2 + 2*(1-t)*t*y1 + pow(1-t,2)*y0;
        result_z = pow(t,2)*z2 + 2*(1-t)*t*z1 + pow(1-t,2)*z0;
        trackVertices.push_back(result_x);
        trackVertices.push_back(result_y);
        trackVertices.push_back(result_z);
      }
    } 
  }
}

void Track::setTrackWidth(double w) {
  trackWidth = w;
}

void Track::setRailWidth(double w) {
  railWidth = w;
}

void Track::setRailTexture(std::string fn) {
  railTexture = loadImage(fn.c_str());
}

void Track::setMiddleTexture(std::string fn) {
  middleTexture = loadImage(fn.c_str());
}
