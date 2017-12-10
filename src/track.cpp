#include <math.h>
#include "track.h"
#include "load_image.h"

#include <stdio.h>

#define pi 3.14159265

Track::Track() {
}

void Track::draw() {
  int iterations = trackVertices.size()-24;
  int norm = 0;

  glPushMatrix();
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
  glBindTexture(GL_TEXTURE_2D, railTexture);
  glEnable(GL_NORMALIZE);
  // Draw Railing
  glBegin(GL_QUADS);
    for (int i=0; i<iterations; i+=12) {
      // Top
      glNormal3f(normals.at(norm+6), normals.at(norm+7), normals.at(norm+8));
      glVertex3f(trackVertices.at(i+6),trackVertices.at(i+7),trackVertices.at(i+8));
      glVertex3f(trackVertices.at(i),trackVertices.at(i+1),trackVertices.at(i+2));
      glNormal3f(normals.at(norm+18), normals.at(norm+19), normals.at(norm+20));
      glVertex3f(trackVertices.at(i+24),trackVertices.at(i+25),trackVertices.at(i+26));
      glVertex3f(trackVertices.at(i+30),trackVertices.at(i+31),trackVertices.at(i+32));
      // Bottom
      glNormal3f(normals.at(norm+9), normals.at(norm+10), normals.at(norm+11));
      glVertex3f(trackVertices.at(i+9),trackVertices.at(i+10),trackVertices.at(i+11));
      glVertex3f(trackVertices.at(i+3),trackVertices.at(i+4),trackVertices.at(i+5));
      glNormal3f(normals.at(norm+21), normals.at(norm+22), normals.at(norm+23));
      glVertex3f(trackVertices.at(i+27),trackVertices.at(i+28),trackVertices.at(i+29));
      glVertex3f(trackVertices.at(i+33),trackVertices.at(i+34),trackVertices.at(i+35));
      // Left Side
      glNormal3f(normals.at(norm), normals.at(norm+1), normals.at(norm+2));
      glVertex3f(trackVertices.at(i),trackVertices.at(i+1),trackVertices.at(i+2));
      glVertex3f(trackVertices.at(i+3),trackVertices.at(i+4),trackVertices.at(i+5));
      glNormal3f(normals.at(norm+12), normals.at(norm+13), normals.at(norm+14));
      glVertex3f(trackVertices.at(i+27),trackVertices.at(i+28),trackVertices.at(i+29));
      glVertex3f(trackVertices.at(i+24),trackVertices.at(i+25),trackVertices.at(i+26));
      // Right Side
      glNormal3f(normals.at(norm+3), normals.at(norm+4), normals.at(norm+5));
      glVertex3f(trackVertices.at(i+9),trackVertices.at(i+10),trackVertices.at(i+11));
      glVertex3f(trackVertices.at(i+6),trackVertices.at(i+7),trackVertices.at(i+8));
      glNormal3f(normals.at(norm+15), normals.at(norm+16), normals.at(norm+17));
      glVertex3f(trackVertices.at(i+30),trackVertices.at(i+31),trackVertices.at(i+32));
      glVertex3f(trackVertices.at(i+33),trackVertices.at(i+34),trackVertices.at(i+35));
      // Iterate on normals
      if ((i/12)%2 == 1) {
        norm += 12;
      }
    }
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_NORMALIZE);
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
    userVertices.push_back(x+dx);
    userVertices.push_back(y+dy);
    userVertices.push_back(z+dz);
  } 
}

void Track::generateTrack(double smoothness) {
  int size = userVertices.size();
  double t;
  double distance;
  double iterations;
  double x0,y0,z0,x1,y1,z1,x2,y2,z2;
  double result_x, result_y, result_z;
  double last_x, last_y, last_z;
  double diff_x, diff_y, diff_z, diff_dist;
  double side_norm_x, side_norm_z;
  // Clear current vertices
  trackVertices.clear();
  // Setting the veriables containing the last point
  last_x = last_y = last_z = 0;
  if (size >= 3) {
    last_x = userVertices.at(0);
    last_y = userVertices.at(1);
    last_z = userVertices.at(2);
  }
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
        // Calculate next point
        result_x = pow(t,2)*x2 + 2*(1-t)*t*x1 + pow(1-t,2)*x0;
        result_y = pow(t,2)*y2 + 2*(1-t)*t*y1 + pow(1-t,2)*y0;
        result_z = pow(t,2)*z2 + 2*(1-t)*t*z1 + pow(1-t,2)*z0;
        // Calculate differences
        diff_x = result_x - last_x;
        diff_y = result_y - last_y;
        diff_z = result_z - last_z;
        // Normalize differences using softmax
        diff_dist = sqrt(diff_x*diff_x + diff_z*diff_z);
        if (diff_dist != 0) {
          side_norm_x = diff_x / diff_dist;
          side_norm_z = diff_z / diff_dist;
        } else {
          side_norm_x = 0;
          side_norm_z = 0;
        }
        // Insert vertices for the track
        // Use cross product of vector between last and current point
        // and the up vector the get offsets right
          // Top left, left side
          trackVertices.push_back(last_x-side_norm_z*(-trackWidth/2-railWidth));
          trackVertices.push_back(last_y+railHeight/2);
          trackVertices.push_back(last_z+side_norm_x*(-trackWidth/2-railWidth));
          // Bottom left, left side
          trackVertices.push_back(last_x-side_norm_z*(-trackWidth/2-railWidth));
          trackVertices.push_back(last_y-railHeight/2);
          trackVertices.push_back(last_z+side_norm_x*(-trackWidth/2-railWidth));
          // Top Right, left side
          trackVertices.push_back(last_x-side_norm_z*(-trackWidth/2));
          trackVertices.push_back(last_y+railHeight/2);
          trackVertices.push_back(last_z+side_norm_x*(-trackWidth/2));
          // Bottom Right, left side
          trackVertices.push_back(last_x-side_norm_z*(-trackWidth/2));
          trackVertices.push_back(last_y-railHeight/2);
          trackVertices.push_back(last_z+side_norm_x*(-trackWidth/2));
          // Top left, right side
          trackVertices.push_back(last_x-side_norm_z*(trackWidth/2));
          trackVertices.push_back(last_y+railHeight/2);
          trackVertices.push_back(last_z+side_norm_x*(trackWidth/2));
          // Bottom left, right side
          trackVertices.push_back(last_x-side_norm_z*(trackWidth/2));
          trackVertices.push_back(last_y-railHeight/2);
          trackVertices.push_back(last_z+side_norm_x*(trackWidth/2));
          // Top Right, right side
          trackVertices.push_back(last_x-side_norm_z*(trackWidth/2+railWidth));
          trackVertices.push_back(last_y+railHeight/2);
          trackVertices.push_back(last_z+side_norm_x*(trackWidth/2+railWidth));
          // Bottom Right, left side
          trackVertices.push_back(last_x-side_norm_z*(trackWidth/2+railWidth));
          trackVertices.push_back(last_y-railHeight/2);
          trackVertices.push_back(last_z+side_norm_x*(trackWidth/2+railWidth));
        // Put in correct normals for lighting
        // Since the side normals are used in generating the trackVertices,
        // put them in the vector first before finding the up and down vectors
          // Left
          normals.push_back(diff_z);
          normals.push_back(0);
          normals.push_back(-diff_x);
          // Right
          normals.push_back(-diff_z);
          normals.push_back(0);
          normals.push_back(diff_x);
          // Up
          normals.push_back(-diff_y*diff_x);
          normals.push_back(diff_x*diff_x+diff_z*diff_z);
          normals.push_back(-diff_y*diff_z);
          // Down
          normals.push_back(diff_y*diff_x);
          normals.push_back(-diff_x*diff_x-diff_z*diff_z);
          normals.push_back(diff_y*diff_z);
        // Update Last values
        last_x = result_x;
        last_y = result_y;
        last_z = result_z;
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

void Track::setRailHeight(double h) {
  railHeight = h;
}

void Track::setRailTexture(std::string fn) {
  railTexture = loadImage(fn.c_str());
}

bool Track::isEmpty() {
  if (trackVertices.size() == 0) return true;
  return false;
}

void Track::getIthTrackVertex(int i, double &x, double &y, double &z) {
  if (i > int(trackVertices.size()/24-24)) i %= trackVertices.size()/24-24;
  // Average the vertex of the top left rail and the top right rail
  x = (trackVertices.at(24*i) + trackVertices.at(24*i+18))/2;
  y = (trackVertices.at(24*i+1) + trackVertices.at(24*i+19))/2;
  z = (trackVertices.at(24*i+2) + trackVertices.at(24*i+20))/2;
}
