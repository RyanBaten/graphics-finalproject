#ifndef CURSOR_H
#define CURSOR_H

class Cursor {
  private:
    double alpha;
    double cursorX;
    double cursorY;
    double cursorZ;
    double minY;
    double width;
    double color[3];
  public:
    Cursor();
    void draw();
    void setTransparency(double a);
    void setLocation(double x, double y, double z);
    void move(double x, double y, double z);
    void setMinY(double _minZ);
    void setWidth(double _width);
    void setColor(double r, double g, double b);
    void getLocation(double* x, double* y, double* z);
};

#endif
