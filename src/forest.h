#ifndef FOREST_H
#define FOREST_H

#include "object.h"
#include <vector>

class Forest {
  private:
    double min_x, min_z;
    double max_x, max_z;
    double y;
    std::vector<Object*> forest;
  public:
    Forest();
    ~Forest();
    void setEdges(double _min_x, double _max_x, double _min_z, double _max_z, double _y);
    void clear();
    void generateTrees(double num);
    void draw();
};

#endif
