#include "Cube.h"
#include "Matrix4.h"
#include "Vector4.h"
#include <GL/glut.h>

using namespace std;

Cube::Cube()
{
  center = new Vector3(0.0, 0.0, 0.0);
  angle = 0.0;
  rotation = true;
  tx = 1;
  ty = 1;
  tz = 1;
  maxY = 11;
  tempY = maxY;
  radius = 1;
}

Matrix4& Cube::getMatrix()
{
  return model2world;
}

void Cube::spin(double deg)   // deg is in degrees
{
	Matrix4 mat;
	mat.makeRotateY(deg);
	model2world = model2world * mat;
}

void Cube::spinX(double deg)   // deg is in degrees
{
	Matrix4 mat;
	mat.makeRotateX(deg);
	model2world = model2world * mat;
}

void Cube::move(double x, double y, double z) {
	Matrix4 mat;
	mat.makeTranslate(x, y, z);
	mat.print("Translation Matrix");
	model2world = mat * model2world;
	center->translate(x, y, z);
	//center->print("DERP");
}

void Cube::reset() {
	model2world.identity();
	center->reset();
	tx = rand() % 2 + 1;
	ty = rand() % 2 + 1;
	tz = 1;
	maxY = 11;
	tempY = maxY;
	rotation = true;
}

void Cube::orbit(bool counter) {
	Matrix4 mat;
	const Vector3* axis = new Vector3(0, 0, 1);
	if (counter) {
		//mat.makeRotateZ(10);
		mat.makeRotate(10, *axis);
		center->orbit(10);
	}
	else {
		//mat.makeRotateZ(-10);
		mat.makeRotate(-10, *axis);
		center->orbit(-10);
	}
	model2world = mat * model2world;
	//center = mat * *center;
	//center->print("DERP");
}

void Cube::scale(double x) {
	Matrix4 mat;
	mat.makeScale(x, x, x);
	mat.print("Scaling Matrix");
	model2world = model2world * mat;
	//center->print("DERP");
}

bool Cube::getRotation() {
	return rotation;
}

void Cube::flipRotation() {
	rotation = !rotation;
}

void Cube::bounce(double width, double height) {
	Matrix4  mat;
		double Y = 20*sin(30*M_PI/180);
		double X = Y * width / height ;
		if (center->getX() < -X)
				tx = -tx;
		else if (center->getX() > X)
			tx = -tx;
		if (center->getY() > Y)
			ty = -ty;
		else if (center->getY() < -Y)
			ty = -ty;
		mat.makeTranslate(tx, ty, 0);
		center->translate(tx, ty, 0);
		center->print("ASD");
		model2world = mat * model2world;
}
void Cube::draw() {
	// Draw all six faces of the cube:
	glBegin(GL_QUADS);
	glColor3f(0.0, 1.0, 0.0);		// This makes the cube green; the parameters are for red, green and blue. 
	// To change the color of the other faces you will need to repeat this call before each face is drawn.
	// Draw front face:
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(-5.0, 5.0, 5.0);
	glVertex3f(5.0, 5.0, 5.0);
	glVertex3f(5.0, -5.0, 5.0);
	glVertex3f(-5.0, -5.0, 5.0);

	// Draw left side:
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(-5.0, 5.0, 5.0);
	glVertex3f(-5.0, 5.0, -5.0);
	glVertex3f(-5.0, -5.0, -5.0);
	glVertex3f(-5.0, -5.0, 5.0);

	// Draw right side:
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(5.0, 5.0, 5.0);
	glVertex3f(5.0, 5.0, -5.0);
	glVertex3f(5.0, -5.0, -5.0);
	glVertex3f(5.0, -5.0, 5.0);

	// Draw back face:
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(-5.0, 5.0, -5.0);
	glVertex3f(5.0, 5.0, -5.0);
	glVertex3f(5.0, -5.0, -5.0);
	glVertex3f(-5.0, -5.0, -5.0);

	// Draw top side:
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(-5.0, 5.0, 5.0);
	glVertex3f(5.0, 5.0, 5.0);
	glVertex3f(5.0, 5.0, -5.0);
	glVertex3f(-5.0, 5.0, -5.0);

	// Draw bottom side:
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(-5.0, -5.0, -5.0);
	glVertex3f(5.0, -5.0, -5.0);
	glVertex3f(5.0, -5.0, 5.0);
	glVertex3f(-5.0, -5.0, 5.0);
	glEnd();
}