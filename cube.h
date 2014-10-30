#ifndef _CUBE_H_
#define _CUBE_H_

#include "Matrix4.h"
#include "Vector3.h"

class Cube
{
  protected:
    Matrix4 model2world;            // model matrix (transforms model coordinates to world coordinates)
    double angle;                   // rotation angle [degrees]
	Vector3* center;                 // center of cube
	bool rotation;

public:
    Cube();   // Constructor
	int YLimit;
	int radius;
	int desaceleration;
    Matrix4& getMatrix();
	double tx, ty, tz, maxY, tempY;
    void spin(double);      // spin cube [degrees]
	void move(double, double, double);
	void reset();
	void orbit(bool);
	void scale(double);
	bool getRotation();
	void flipRotation();
	void bounce(double, double);
	double boundaries(double, double);
	void draw();
	void spinX(double);
};

#endif

