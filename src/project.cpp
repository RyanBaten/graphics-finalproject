// Used ex21 sdl as a reference for use of sdl and opengl together

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

#include <stdio.h>
// OpenGL with prototypes
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

#include "camera.h"
#include "light.h"
#include "texturemap.h"
#include "skybox.h"
#include "ground.h"
#include "cursor.h"
#include "track.h"

#define Cos(x) (cos((x)*3.1415927/180))
#define Sin(x) (sin((x)*3.1415927/180))

int debug = 0; // debug mode
double fov = 55; // Field of view
double asp = 1; // Aspect ratio
double dim = 8; // Size of world
double scale = 70; // Scale of skybox and ground
double groundSize = 100; // Number of rows/cols in the ground matrix
const GLfloat fogColor[4] = {1.0,1.0,1.0,1.0}; // Color of fog

Camera *camera = new Camera();
TextureMap *texture_map = new TextureMap();
Light *light = new Light(GL_LIGHT0);
SkyBox *skybox = new SkyBox(scale);
Ground *ground = new Ground(groundSize, groundSize);
Cursor *cursor = new Cursor();
Track *track = new Track();

void display() {
  // Clear color and depth buffer
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  // Enable Z buffering
  glEnable(GL_DEPTH_TEST);
  // Undo previous transformations
  glLoadIdentity();
  // Camera
  camera->look();
  // Draw skybox x,y,z,scale
  skybox->draw(0,0,0);
  // Enable lighting
  glEnable(GL_LIGHTING);
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 0);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
  light->display();
  // Fog
  glEnable(GL_FOG);
  glFogi(GL_FOG_MODE, GL_LINEAR);
  glFogf(GL_FOG_START, 0);
  glFogf(GL_FOG_END, 2*scale);
//  glFogf(GL_FOG_DENSITY, 0.025);
  glFogfv(GL_FOG_COLOR, fogColor);
  glHint(GL_FOG_HINT, GL_NICEST);
  // Draw track
  track->draw();
  // Draw ground
  ground->draw(-scale,0,-scale);
  // Draw everything
  if (debug) {
    // Draw a quad to test out textures on
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    texture_map->bindTexture("wood");
    glColor3f(1,1,1);
    glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    glTexCoord2f(1,1);  glVertex3f(0,20,-5);
    glTexCoord2f(1,0);  glVertex3f(0,21,-5);
    glTexCoord2f(0,0);  glVertex3f(1,21,-5);
    glTexCoord2f(0,1);  glVertex3f(1,20,-5);
    glEnd();
  }
  // Draw cursor
  cursor->draw();
  // Disables
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_FOG);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);
  glDisable(GL_COLOR_MATERIAL);
  // Render scene and make it visible
  glFlush();
  SDL_GL_SwapBuffers();
}

int key() {
  Uint8* keys = SDL_GetKeyState(NULL);
//  int shift = SDL_GetModState()&KMOD_SHIFT;
  // Exit on ESC
  if (!debug) {
    if (keys[SDLK_ESCAPE]) {
      return 0;
    } else if (keys[SDLK_UP]) {
      camera->rotate(0,5);
    } else if (keys[SDLK_DOWN]) {
      camera->rotate(0,-5);
    } else if (keys[SDLK_LEFT]) {
      camera->rotate(5,0);
    } else if (keys[SDLK_RIGHT]) {
      camera->rotate(-5,0);
    } else if (keys[SDLK_w]) {
      camera->moveForward(0.5);
    } else if (keys[SDLK_0]) {
      debug = !debug;
      light->indicatorOn();
    } else if (keys[SDLK_i]) {
      cursor->move(0.5,0,0);
    } else if (keys[SDLK_j]) {
      cursor->move(0,0,-0.5);
    } else if (keys[SDLK_k]) {
      cursor->move(-0.5,0,0);
    } else if (keys[SDLK_l]) {
      cursor->move(0,0,0.5);
    } else if (keys[SDLK_t]) {
      cursor->move(0,0.5,0);
    } else if (keys[SDLK_y]) {
      cursor->move(0,-0.5,0);
    } else if (keys[SDLK_RETURN]) {
      double x,y,z;
      cursor->getLocation(x,y,z);
      track->addVertex(x,y,z);
      track->generateTrack(0.1);
    }
  } else {
    if (keys[SDLK_ESCAPE]) {
      return 0;
    } else if (keys[SDLK_UP]) {
      camera->rotate(0,5);
    } else if (keys[SDLK_DOWN]) {
      camera->rotate(0,-5);
    } else if (keys[SDLK_LEFT]) {
      camera->rotate(5,0);
    } else if (keys[SDLK_RIGHT]) {
      camera->rotate(-5,0);
    } else if (keys[SDLK_w]) {
      camera->moveForward(0.5);
    } else if (keys[SDLK_0]) {
      debug = !debug;
      light->indicatorOff();
    }
  }
  // Keep the program running
  return 1;
}

void reshape(int width, int height) {
  // Ratio of the width to the height of the window
  asp = (height>0) ? (double)width/height : 1;
  // Set the viewport to the entire window
  glViewport(0,0,width,height);
  // Set perspective projection
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(fov, asp, dim/16, 16*dim);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

int main() {
  int run = 1;
  double t0 = 0;
  SDL_Surface* screen;
  Mix_Music* music;

  // Initialize SDL
  SDL_Init(SDL_INIT_VIDEO);
  // Set window size, allow resizing and ask for double buffering
  screen = SDL_SetVideoMode(1000,800,0,SDL_OPENGL|SDL_RESIZABLE|SDL_DOUBLEBUF);
  if (!screen) {
    fprintf(stderr, "Could not initialize SDL screen");
  }
  SDL_WM_SetCaption("Project","project");
  // Set screen size
  reshape(screen->w, screen->h);

  // Set up camera
  camera->moveTo(0,20,0);
  camera->setViewLocation(0,20,-1);

  // Initialize texture map
  texture_map->addTexture("wood", "textures/wood.png");
  texture_map->addTexture("grass", "textures/grass.png");

  // Set up skybox
  skybox->setNTexture("textures/skybox_n.png");
  skybox->setSTexture("textures/skybox_s.png");
  skybox->setETexture("textures/skybox_e.png");
  skybox->setWTexture("textures/skybox_w.png");
  skybox->setUTexture("textures/skybox_u.png");
  skybox->setDTexture("textures/skybox_d.png");

  // Set up ground 
  ground->setScale(2*scale/groundSize);
  ground->generateVertices(0,10,0.15);
  ground->setTexture("textures/grass.png");

  // Set up cursor
  cursor->setLocation(5,10,10);
  cursor->setMinY(0);
  cursor->setWidth(0.5);
  cursor->setTransparency(0.95);
  cursor->setColor(0.8, 0, 0);

  // Setting light parameters
  light->setColor(1,1,1);
  light->setAmbient(0.3);
  light->setDiffuse(0.6);
  light->setSpecular(0.3);
  // Moving the light ontop of the sun in the skybox
  light->moveTo(.4*scale,.4*scale,scale);
  if (debug) {
    light->indicatorOn();
  }

  // Initialize audio
  if (Mix_OpenAudio(44100,AUDIO_S16SYS,2,4096)) exit(1);
  // Load music
  music = Mix_LoadMUS("music/408201__setuniman__mark-time-1p77b.wav");
  if (!music) exit(1);
  // Play music
//  Mix_PlayMusic(music,-1);
//  printf("This project uses these sounds from freesound:\n");
//  printf("mark time 1P77b by Setuniman (https://freesound.org/people/Setuniman/sounds/408201/)\n");

  // SDL event loop
  while (run) {
    double t = SDL_GetTicks()/1000.0;
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_VIDEORESIZE:
          screen = SDL_SetVideoMode(event.resize.w,event.resize.h,0,SDL_OPENGL|SDL_RESIZABLE|SDL_DOUBLEBUF);
          reshape(screen->w, screen->h);
          break;
        case SDL_QUIT:
          run = 0;
          break;
        case SDL_KEYDOWN:
          run = key();
          t0 = t+0.5; // Wait before repeating
          break;
        default:
          // Do Nothing
          break;
      }
    }
    // Repeat key every 50 ms
    if (t-t0>0.05) {
      run = key();
      t0 = t;
    }
    // Display
    display();
    // Slow down display rate by sleeping 5 ms
    SDL_Delay(5);
  }
  delete camera;
  delete texture_map;
  delete light;
  delete skybox;
  delete ground;
  delete cursor;
  delete track;
  Mix_CloseAudio();
  SDL_Quit();
  return 0;
}
