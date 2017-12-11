#include "forest.h"
#include <stdlib.h>
#include <math.h>

Forest::Forest() {}

Forest::~Forest() {
  int iterations = forest.size();
  for (int i=0; i<iterations; i++) {
    delete forest.at(i);
  }
}

void Forest::setEdges(double _min_x, double _max_x, double _min_z, double _max_z, double _y) {
  min_x = _min_x;
  min_z = _min_z;
  max_x = _max_x;
  max_z = _max_z;
  y = _y;
}

void Forest::clear() {
  int iterations = forest.size();
  for (int i=0; i<iterations; i++) {
    delete forest.at(i);
  }
  forest.clear();
}

void Forest::generateTrees(double num) {
  clear();
  for (int i=0; i<num; i++) {
    Object *tree = new Object();
    tree->loadFile("objects/tree.obj");
    tree->loadTexture("textures/tree.png");
    // Choose random location and rotation
    tree->moveTo(fmod(rand()/1000,max_x-min_x)+min_x,y,fmod(rand()/1000,max_z-min_z)+min_z);
    tree->rotate(0,fmod(rand()/1000,360),0);
    tree->setScale(0.7);
    // Add tree to forest
    forest.push_back(tree);
  }
}

void Forest::draw() {
  int iterations = forest.size();
  for (int i=0; i<iterations; i++) {
    forest.at(i)->draw();
  }
}
