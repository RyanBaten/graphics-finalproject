#include <math.h>
#include <stdlib.h>

#include "ground.h"
#include "load_image.h"

Ground::Ground(double _sizeX, double _sizeY) {
  sizeX = _sizeX;
  sizeY = _sizeY;
  scale = 1;
  // Make vertices a dynamic 2d array
  vertices = new double*[sizeY];
  for (int i=0; i<sizeY; i++) {
    vertices[i] = new double[sizeX];
  }
  // Generate 1 normal per vertex
  normals = new double*[sizeY];
  for (int i=0; i<sizeY; i++) {
    normals[i] = new double[sizeX*3];
  }
}

Ground::~Ground() {
  // Free memory for normals
  for (int i=0; i<sizeY; i++) {
    delete normals[i];
  }
  delete[] normals;
  // Free memory for vertices
  for (int i=0; i<sizeY; i++) {
    delete vertices[i];
  }
  delete[] vertices;
}

void Ground::setTexture(std::string fn) {
  texture = loadImage(fn.c_str());
}

void Ground::setScale(double _scale) {
  scale = _scale;
}

void Ground::generateVertices(double min, double max, double maxDiff) {
  // Avoiding cases when fmod always returns 0
  if (fmod(rand(),maxDiff) == 0) maxDiff += 0.05;
  double result;
  double diffRange = 2*maxDiff;
  double maxRange = max-min;
  // Allows the maxdiff to be below 0.5 without returning the same result
  double randmod = 1000;
  double last = fmod(rand()/randmod,maxRange) + min;
  // Fill in first column with random entries, enforcing a max diff
  for (int i=0; i<sizeY; i++) {
    result = last+maxDiff-fmod(rand()/randmod,diffRange);
    vertices[i][0] = fmin(fmax(result,min),max);
    last = vertices[i][0];
  }
  // Fill in first row with random entries, enforcing a max diff
  for (int j=1; j<sizeX; j++) {
    last = vertices[0][j-1];
    result = last+maxDiff-fmod(rand()/randmod,diffRange);
    vertices[0][j] = fmin(fmax(result,min),max);
  }
  // Fill in everything else with random entries, enforcing a max diff
  // to the average between the coordinate above and to the left of
  // the current entry
  for (int i=1; i<sizeY; i++) {
    for (int j=1; j<sizeX; j++) {
      last = (vertices[i][j-1] + vertices[i-1][j])/2;
      result = last+maxDiff-fmod(rand()/randmod,diffRange);
      vertices[i][j] = fmin(fmax(result,min),max);
    }
  }
  // Grab the normals, assume x=z=1 per step in the array
  for (int i=0; i<sizeY-1; i++) {
    for (int j=0; j<sizeX-1; j++) {
      normals[i][3*j] = (vertices[i][j]-vertices[i+1][j]);
      normals[i][3*j+1] = 1;
      normals[i][3*j+2] = (vertices[i][j]-vertices[i][j+1]);
    }
  }
  // Smooth normals
  for (int i=sizeY-1; i>0; i--) {
    for (int j=3*(sizeX-1); j>0; j--) {
      normals[i][j] = normals[i-1][j] + normals[i-1][j-3] + normals[i][j-3] + normals[i][j] / 4;
    }
  }
}

void Ground::draw(double x, double y, double z) {
  int counter = 0;

  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
  glPushMatrix();
  // Make x,y,z the corner of the ground
  glTranslated(x,y,z);
  // Scale the ground
  glScaled(scale,scale,scale);
  // Use the ground texture
  glBindTexture(GL_TEXTURE_2D, texture);
  // Enable automatic normal normalization
  glEnable(GL_NORMALIZE);
  // Draw
  glBegin(GL_QUADS);
    for (int i=0; i<sizeY-1; i++) {
      for (int j=0; j<sizeX-1; j++) {
        glNormal3f(normals[i+1][3*j], normals[i+1][3*j+1], normals[i+1][3*j+2]);
        glTexCoord2f(1,1); glVertex3f(i+1,vertices[i+1][j],j);
        glNormal3f(normals[i][3*j], normals[i][3*j+1], normals[i][3*j+2]);
        glTexCoord2f(1,0); glVertex3f(i,vertices[i][j],j);
        glNormal3f(normals[i][3*j+3], normals[i][3*j+4], normals[i][3*j+5]);
        glTexCoord2f(0,0); glVertex3f(i,vertices[i][j+1],j+1);
        glNormal3f(normals[i+1][3*j+3], normals[i+1][3*j+4], normals[i+1][3*j+5]);
        glTexCoord2f(0,1); glVertex3f(i+1,vertices[i+1][j+1],j+1);
        counter += 3;
      }
    }
  glEnd();
  // Pop matrix and disable normalization + textures
  glPopMatrix();
  glDisable(GL_NORMALIZE);
  glDisable(GL_TEXTURE_2D);
  
}
