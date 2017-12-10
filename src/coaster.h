#ifndef COASTER_H
#define COASTER_H

#include "object.h"

class Coaster : public Object {
  private:
    double x_location, y_location, z_location;
    double x_rotation, y_rotation, z_rotation;
    double scale;
    double velocity;
    double max_velocity, min_velocity;
  public:
    Coaster();
    void rotateToFace(double x, double y, double z);
    void moveTo(double x, double y, double z);
    void setScale(double _scale);
    void setVelocity(double _velocity);
    void increaseVelocity(double _velocity);
    void decreaseVelocity(double _velocity);
    void setMinVelocity(double _velocity);
    void setMaxVelocity(double _velocity);
    double getVelocity();
    void draw();
};

#endif
