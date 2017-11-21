#include "skybox.h"
#include "load_image.h"

SkyBox::SkyBox() {
}

SkyBox::SkyBox(double _scale) {
  scale = _scale;
}

void SkyBox::setNTexture(std::string fn) {
  NTexture = loadImage(fn.c_str());
}

void SkyBox::setSTexture(std::string fn) {
  STexture = loadImage(fn.c_str());
}

void SkyBox::setETexture(std::string fn) {
  ETexture = loadImage(fn.c_str());
}

void SkyBox::setWTexture(std::string fn) {
  WTexture = loadImage(fn.c_str());
}

void SkyBox::setUTexture(std::string fn) {
  UTexture = loadImage(fn.c_str());
}

void SkyBox::setDTexture(std::string fn) {
  DTexture = loadImage(fn.c_str());
}

void SkyBox::setScale(double _scale) {
  scale = _scale;
}

void SkyBox::draw(double x, double y, double z) {
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
  glPushMatrix();
  // Make x,y,z the center and scale the size of the skybox
  glTranslated(x,y,z);
  glScaled(scale,scale,scale);
  // Draw the skybox using each of the textures loaded into the
  // variables NTexture STexture ...
  // North
  glBindTexture(GL_TEXTURE_2D, NTexture);
    glBegin(GL_QUADS);
      glNormal3f(0,0,1);
      glTexCoord2f(1,1); glVertex3f(x-1,y-1,z-1);
      glTexCoord2f(1,0); glVertex3f(x-1,y+1,z-1);
      glTexCoord2f(0,0); glVertex3f(x+1,y+1,z-1);
      glTexCoord2f(0,1); glVertex3f(x+1,y-1,z-1);
    glEnd();
  // South
  glBindTexture(GL_TEXTURE_2D, STexture);
    glBegin(GL_QUADS);
      glNormal3f(0,0,-1);
      glTexCoord2f(0,1); glVertex3f(x-1,y-1,z+1);
      glTexCoord2f(0,0); glVertex3f(x-1,y+1,z+1);
      glTexCoord2f(1,0); glVertex3f(x+1,y+1,z+1);
      glTexCoord2f(1,1); glVertex3f(x+1,y-1,z+1);
    glEnd();
  // East
  glBindTexture(GL_TEXTURE_2D, ETexture);
    glBegin(GL_QUADS);
      glNormal3f(-1,0,0);
      glTexCoord2f(1,1); glVertex3f(x+1,y-1,z-1);
      glTexCoord2f(1,0); glVertex3f(x+1,y+1,z-1);
      glTexCoord2f(0,0); glVertex3f(x+1,y+1,z+1);
      glTexCoord2f(0,1); glVertex3f(x+1,y-1,z+1);
    glEnd();
  // West
  glBindTexture(GL_TEXTURE_2D, WTexture);
    glBegin(GL_QUADS);
      glNormal3f(1,0,0);
      glTexCoord2f(0,1); glVertex3f(x-1,y-1,z-1);
      glTexCoord2f(0,0); glVertex3f(x-1,y+1,z-1);
      glTexCoord2f(1,0); glVertex3f(x-1,y+1,z+1);
      glTexCoord2f(1,1); glVertex3f(x-1,y-1,z+1);
    glEnd();
  // Up
  glBindTexture(GL_TEXTURE_2D, UTexture);
    glBegin(GL_QUADS);
      glNormal3f(0,1,0);
      glTexCoord2f(1,1); glVertex3f(x-1,y+1,z-1);
      glTexCoord2f(1,0); glVertex3f(x-1,y+1,z+1);
      glTexCoord2f(0,0); glVertex3f(x+1,y+1,z+1);
      glTexCoord2f(0,1); glVertex3f(x+1,y+1,z-1);
    glEnd();
  // Down
  glBindTexture(GL_TEXTURE_2D, DTexture);
    glBegin(GL_QUADS);
      glNormal3f(0,-1,0);
      glTexCoord2f(0,1); glVertex3f(x-1,y-1,z-1);
      glTexCoord2f(0,0); glVertex3f(x-1,y-1,z+1);
      glTexCoord2f(1,0); glVertex3f(x+1,y-1,z+1);
      glTexCoord2f(1,1); glVertex3f(x+1,y-1,z-1);
    glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}

