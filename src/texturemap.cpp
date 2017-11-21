#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include<limits.h>

#include "texturemap.h"
#include "load_image.h"

// Can be added to in the future
TextureMap::TextureMap() {}

void TextureMap::addTexture(std::string name, std::string fn){
  GLuint texture_name = loadImage(fn.c_str());
  texture_map[name] = texture_name;
}

void TextureMap::removeTexture(std::string name) {
  if (texture_map.find(name) != texture_map.end()) {
    glDeleteTextures(1, &texture_map.at(name));
    texture_map.erase(name);
  }
}

void TextureMap::bindTexture(std::string name) {
  if (texture_map.find(name) != texture_map.end()) {
    glBindTexture(GL_TEXTURE_2D, texture_map.at(name));
  }
}
