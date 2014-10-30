#ifndef _HOUSE_H_
#define _HOUSE_H_

#include "Matrix4.h"
#include "Vector3.h"

class House
{
protected:
	Matrix4 model2world;            // model matrix (transforms model coordinates to world coordinates)


public:
	House();   // Constructor
	Matrix4& getMatrix();
	void draw();
};

#endif
