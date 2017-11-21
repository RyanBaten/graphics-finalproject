#include <math.h>
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "load_image.h"

// Used loadtexbmp from instructor example as reference for sopying image and scaling
// Used http://www.sdltutorials.com/sdl-tip-sdl-surface-to-opengl-texture and
// http://lazyfoo.net/tutorials/SDL/06_extension_libraries_and_loading_other_image_formats/index2.php
// as reference for sdl image loading and dealing with surfaces

GLuint loadImage(const char* filename) {
  GLuint texture;
  int mode;
  SDL_Surface* surface = IMG_Load(filename);
  // Check if image is loaded correctly
  if (surface ==  NULL) {
    fprintf(stderr, "Unable to load surface. Error: %s\n", IMG_GetError());
    return -1;
  }
  // Get the right mode for the later glTexImage2D call
  mode = GL_RGB;
  if (surface->format->BytesPerPixel == 4) {
    mode = GL_RGBA;
  }
  // Generate 2D openGL texture
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  // Copy image
  glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
  // Scale linearly when image size doesn't match
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  // free the sdl surface
  SDL_FreeSurface(surface);
  // return texture name
  return texture;
}
