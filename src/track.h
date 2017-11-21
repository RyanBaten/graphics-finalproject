#ifndef TRACK_H
#define TRACK_H

#include <vector>

class Track {
  private:
    int type;
    double width;
    std::vector<double> vertices;
  public:
    Track();
    void draw();
    void clearVertices();
    void addVertex(double x, double y, double z);
};

#endif
