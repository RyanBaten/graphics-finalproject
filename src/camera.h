#ifndef CAMERA_H
#define CAMERA_H

#define FIRST_PERSON_MODE 0
#define FIXED_VIEWPOINT_MODE 1

class Camera {
  private:
    // First Person or fixed viewpoint?
    int mode;
    // View Angle
    int view_th, view_ph;
    // Eye Location
    double eye_x, eye_y, eye_z;
    // Location to look at in fixed viewpoint mode
    double look_x, look_y, look_z;
    // Update LookAt location for first Person
    void updateLookat();
  public:
    // Constructor
    Camera();
    // Moves the camera forward
    void moveForward(double amount);
    // Moves to specified location
    void moveTo(double x, double y, double z);
    // Rotates the view (in degrees)
    void rotate(int th, int ph);
    // Set view location
    void setViewLocation(double x, double y, double z);
    // Set mode to first person
    void firstPersonMode();
    // Set mode to fixed viewpoint
    void fixedViewpointMode();
    // Performs gluLookAt
    void look();
    // Performs gluLookAt with given y value for up
    void look(double up);
};

#endif
