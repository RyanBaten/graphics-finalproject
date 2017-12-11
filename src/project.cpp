// Ryan Baten
// Computer graphics project

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
#include "coaster.h"
#include "emitter.h"
#include "forest.h"
#include "printsdl.h"

#define Cos(x) (cos((x)*3.1415927/180))
#define Sin(x) (sin((x)*3.1415927/180))

#define MODE_CONSTRUCT 1
#define MODE_RIDE 2
#define MODE_PRESET 3
#define MODE_FOLLOW 4
#define MODE_DEBUG 5

int mode = MODE_PRESET; 
double width = 1000; // Screen Width
double height = 800; // Screen Height
double fov = 55; // Field of view
double asp = 1; // Aspect ratio
double dim = 16; // Size of world
double scale = 70; // Scale of skybox and ground
double groundSize = 100; // Number of rows/cols in the ground matrix
double cameraViewHeight = 1.8; // Height of camera above coaster in first person mode
const GLfloat fogColor[4] = {1.0,1.0,1.0,1.0}; // Color of fog

Camera *camera = new Camera();
TextureMap *texture_map = new TextureMap();
Light *light = new Light(GL_LIGHT0);
SkyBox *skybox = new SkyBox(scale);
Ground *ground = new Ground(groundSize, groundSize);
Cursor *cursor = new Cursor();
Track *track = new Track();
Coaster *coaster = new Coaster();
Emitter *fire = new Emitter();
Emitter *lightning = new Emitter();
Forest *forest = new Forest();

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
  glFogfv(GL_FOG_COLOR, fogColor);
  glHint(GL_FOG_HINT, GL_NICEST);
  // Draw track
  track->draw();
  // Draw ground
  ground->draw(-scale,0,-scale);
  // Draw forest
  forest->draw();
  // Draw coaster
  if (mode != MODE_CONSTRUCT) coaster->draw();
  // Draw everything
  if (mode == MODE_DEBUG) {
    // Draw a quad to test out textures on
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    texture_map->bindTexture("grass");
    glColor3f(1,1,1);
    glBegin(GL_QUADS);
      glNormal3f(0,0,1);
      glTexCoord2f(1,1);  glVertex3f(0,20,-5);
      glTexCoord2f(1,0);  glVertex3f(0,21,-5);
      glTexCoord2f(0,0);  glVertex3f(1,21,-5);
      glTexCoord2f(0,1);  glVertex3f(1,20,-5);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
  }
  // Draw cursor
  if (mode == MODE_CONSTRUCT) {
    cursor->draw();
  }
  // Disable lighting
  glDisable(GL_LIGHTING);
  // Draw Particles
  fire->draw();
  lightning->draw();
  // Display Velocity
  if (mode != MODE_CONSTRUCT) {
    glColor3f(0.7,0.7,0.7);
    glWindowPos2i(5,5);
    Print("Velocity: %f\n", coaster->getVelocity());
    glColor3f(1,1,1);
  }
  // Disables
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_FOG);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_COLOR_MATERIAL);
  // Render scene and make it visible
  glFlush();
  SDL_GL_SwapBuffers();
}

int key(SDL_Event event) {
  // I wanted to find a more efficient way of doing this than a massive if statement
  // Lazyfoo SDL 1.2 tutorial page shows usage of a switch
  // http://lazyfoo.net/tutorials/SDL/04_key_presses/index.php
  switch (event.key.keysym.sym) {
    case SDLK_ESCAPE:
      return 0;
      break;
    case SDLK_1:
      mode = MODE_CONSTRUCT;
      light->indicatorOff();
      light->moveTo(.4*scale,.4*scale,scale);
      if (mode == MODE_PRESET) {
        track->clear();
      }
      break;
    case SDLK_2:
      mode = MODE_RIDE;
      light->indicatorOff();
      light->moveTo(.4*scale,.4*scale,scale);
      break;
    case SDLK_3:
      mode = MODE_PRESET;
      track->loadTrackFile("tracks/sampleTrack.track");
      light->indicatorOff();
      light->moveTo(.4*scale,.4*scale,scale);
      break;
    case SDLK_4:
      mode = MODE_FOLLOW;
      light->indicatorOff();
      light->moveTo(.4*scale,.4*scale,scale);
      break;
    case SDLK_5:
      mode = MODE_DEBUG;
      light->indicatorOn();
      break;
    case SDLK_UP:
      camera->rotate(0,5);
      break;
    case SDLK_DOWN:
      camera->rotate(0,-5);
      break;
    case SDLK_LEFT:
      camera->rotate(5,0);
      break;
    case SDLK_RIGHT:
      camera->rotate(-5,0);
      break;
    case SDLK_b:
      track->exportTrack("yourTrack.track");
      break;
    case SDLK_w:
      if (mode == MODE_CONSTRUCT) camera->moveForward(0.5);
      else {
        coaster->increaseVelocity(1);
        fire->turnOn(SDL_GetTicks()/1000.0 +2);
      }
      break;
    case SDLK_s:
      if (mode == MODE_CONSTRUCT) camera->moveForward(-0.5);
      else {
        coaster->decreaseVelocity(1);
        lightning->turnOn(SDL_GetTicks()/1000.0 +2);
      }
      break;
    case SDLK_i:
      if (mode == MODE_CONSTRUCT) cursor->move(0.5,0,0);
      break;
    case SDLK_j:
      if (mode == MODE_CONSTRUCT) cursor->move(0,0,-0.5);
      break;
    case SDLK_k:
      if (mode == MODE_CONSTRUCT) cursor->move(-0.5,0,0);
      break;
    case SDLK_l:
      if (mode == MODE_CONSTRUCT) cursor->move(0,0,0.5);
      break;
    case SDLK_t:
      if (mode == MODE_CONSTRUCT) cursor->move(0,0.5,0);
      break;
    case SDLK_y:
      if (mode == MODE_CONSTRUCT) cursor->move(0,-0.5,0);
      break;
    case SDLK_r:
      if (mode == MODE_CONSTRUCT) track->clearVertices();
      break;
    case SDLK_RETURN:
      if (mode == MODE_CONSTRUCT) {
        double x,y,z;
        cursor->getLocation(x,y,z);
        track->addVertex(x,y,z);
        track->generateTrack(0.1);
      }
      break;
    default:
    break;
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
  int last_track_vert = 0;
  double t0 = 0;
  double x = 0;
  double y = 0;
  double z = 0;
  SDL_Surface* screen;
  Mix_Music* music;

  // Initialize SDL
  SDL_Init(SDL_INIT_VIDEO);
  // Set window size, allow resizing and ask for double buffering
  screen = SDL_SetVideoMode(width,height,0,SDL_OPENGL|SDL_RESIZABLE|SDL_DOUBLEBUF);
  if (!screen) {
    fprintf(stderr, "Could not initialize SDL screen");
  }
  SDL_WM_SetCaption("Project","project");
  // Set screen size
  reshape(screen->w, screen->h);

  // Enable key repeating 
  // Needed this because I wanted to switch my huge if statement
  // to a switch statement and only do key handling when key pressed
  // https://gamedev.stackexchange.com/questions/19571/how-can-i-process-continuously-held-keys-with-sdl
  if (SDL_EnableKeyRepeat(100, 5) == -1) {
    printf("SDL Key repeat failed to be set\n");
    return 1;
  }

  // Set up camera
  camera->moveTo(0,10,0);
  camera->setViewLocation(5,5,10);

  // Initialize texture map
  texture_map->addTexture("grass", "textures/grass.png");
  texture_map->addTexture("hud", "textures/hud.png");

  // Set up skybox
  skybox->setNTexture("textures/skybox_n.png");
  skybox->setSTexture("textures/skybox_s.png");
  skybox->setETexture("textures/skybox_e.png");
  skybox->setWTexture("textures/skybox_w.png");
  skybox->setUTexture("textures/skybox_u.png");
  skybox->setDTexture("textures/skybox_d.png");

  // Set up ground 
  ground->setScale(2*scale/groundSize);
  ground->generateVertices(0,10,0.2);
  ground->setTexture("textures/grass.png");

  // Set up cursor
  cursor->setLocation(5,5,10);
  cursor->setMinY(0);
  cursor->setWidth(0.5);
  cursor->setTransparency(0.95);
  cursor->setColor(0.8, 0, 0);

  // Set up track
  track->setTrackWidth(1);
  track->setRailWidth(0.4);
  track->setRailHeight(0.1);
  track->setRailTexture("textures/metal.png");
  if (mode == MODE_PRESET) {
    track->loadTrackFile("tracks/sampleTrack.track");
  }

  // Coaster Setup
  coaster->loadFile("objects/coaster.obj");
  coaster->loadTexture("textures/coasterTexture.png");
  coaster->setScale(0.7);
  coaster->moveTo(5,5,5);
  coaster->setVelocity(5);
  coaster->setMaxVelocity(10);
  coaster->setMinVelocity(1);

  // Set up Forest
  forest->setEdges(-scale/2,scale/2,-scale/2,scale/2, 0);
  forest->generateTrees(50);

  // Setting light parameters
  light->setColor(1,1,1);
  light->setAmbient(0.3);
  light->setDiffuse(0.6);
  light->setSpecular(0.3);
  // Moving the light ontop of the sun in the skybox
  light->moveTo(.4*scale,.4*scale,scale);

  // Initialize audio
  if (Mix_OpenAudio(44100,AUDIO_S16SYS,2,4096)) exit(1);
  // Load music
  music = Mix_LoadMUS("music/408201__setuniman__mark-time-1p77b.wav");
  if (!music) exit(1);
  // Play music
  Mix_PlayMusic(music,-1);

  // Set up emitters
  fire->setRate(0.01);
  fire->setTime(SDL_GetTicks()/1000.0);
  fire->loadTexture("textures/fire.png");
  fire->setLocation(5,5,5);
  fire->setBreadth(2);
  fire->setLifetime(40);
  fire->setVelocity(0.006);
  fire->setSize(30);

  lightning->setRate(0.1);
  lightning->setTime(SDL_GetTicks()/1000.0);
  lightning->loadTexture("textures/lightning.png");
  lightning->setLocation(5,10,5);
  lightning->setBreadth(2);
  lightning->setLifetime(40);
  lightning->setVelocity(0.01);
  lightning->setSize(20);

  // Test particles for debugging purposes
  if (mode == MODE_DEBUG) {
    lightning->turnOn(SDL_GetTicks()/1000.0 + 5);
    fire->turnOn(SDL_GetTicks()/1000.0 + 5);
  }

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
          run = key(event);
          t0 = t+0.5; // Wait before repeating
          break;
        default:
          // Do Nothing
          break;
      }
    }
    // Repeat key every 50 ms
    if (t-t0>0.05) {
//      run = key();
      t0 = t;
      fire->update(t);
      lightning->update(t);
      if (mode == MODE_DEBUG) {
        light->moveTo(scale*Sin(t*30),.4*scale,scale*Cos(t*30));
      } else if (mode != MODE_CONSTRUCT && !track->isEmpty()) {
        last_track_vert = track->getIthTrackVertex(last_track_vert + coaster->getVelocity(), x, y, z);
        coaster->rotateToFace(x,y,z);
        coaster->moveTo(x,y,z);
        fire->setLocation(x,y,z);
        lightning->setLocation(x,y,z);
        if (mode == MODE_FOLLOW) {
          camera->setViewLocation(x,y+cameraViewHeight,z);
          camera->moveTo(x,y+cameraViewHeight,z);
        }
      }
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
  delete coaster;
  delete fire;
  delete lightning;
  delete forest;
  Mix_CloseAudio();
  SDL_Quit();
  return 0;
}
