#ifndef PARTICLE_H
#define PARTICLE_H

class Particle {
  private:
    double birth;
    double lifetime;
    double x,y,z;
    double velocity;
    double x_dir,y_dir,z_dir;
  public:
    Particle(double _x, double _y, double _z, double _lifetime, double _velocity);
    void setLifetime(double t);
    void getLocation(double &_x, double &_y, double &_z);
    void setDirection(double _x, double _y, double _z);
    int update();
};

#endif
