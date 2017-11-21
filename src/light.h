#ifndef LIGHT_H
#define LIGHT_H

#define INDICATOR_ON 1
#define INDICATOR_OFF 0

class Light {
  private:
    // If an indicator should be shown at the light location
    int indicator;
    // Location of the light
    double pos_x, pos_y, pos_z;
    // RGB colors of the light
    double color_r, color_g, color_b;
    // Intensities
    double ambient, specular, diffuse;
    // Color vectors
    float Ambient[4], Diffuse[4], Specular[4];
    // Position
    float Position[4];
    // Show the indicator at the light's position
    void showIndicator();
    // Update functions
    void updateAmbient();
    void updateDiffuse();
    void updateSpecular();
    // The light that is used
    GLenum light; 
  public:
    // Constructor takes in a light GLenum
    Light(GLenum l);
    // Move the light to the given location
    void moveTo(double x, double y, double z);
    // Sets the rgb color of the light
    void setColor(double r, double g, double b);
    // Setting intensities
    void setAmbient(double a);
    void setDiffuse(double d);
    void setSpecular(double s);
    // Increases the intensity by specified amount
    void increaseIntensity(double a, double d, double s);
    // Set light indicator on
    void indicatorOn();
    // Set light indicator off
    void indicatorOff();
    // Toggle light indicator
    void indicatorToggle();
    // Show the light
    void display();
};

#endif
