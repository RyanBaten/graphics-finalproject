#ifndef CURSOR_H
#define CURSOR_H

class Cursor {
  private:
    double alpha;
    double cursorX;
    double cursorY;
    double cursorZ;
    double minZ;
    double width;
  public:
    Cursor();
    void draw();
    void setTransparency(double a);
    void setLocation(double x, double y, double z);
    void move(double x, double y, double z);
    void setMinZ(double _minZ);
    void setWidth(double _width);
    void getLocation(double* x, double* y, double* z);
};

#endif
