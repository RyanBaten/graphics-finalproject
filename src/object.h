#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <vector>

class Object {
  protected:
    std::string texName;
    std::vector<double> vertexCoords;
    std::vector<double> normalCoords;
    std::vector<double> texCoords;
  public:
    Object();
    void loadFile(const char* file);
    void draw(double x, double y, double z, double rx, double ry, double rz, double scale);
};

#endif
