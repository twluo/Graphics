#include <iostream>
#include <fstream>
#include <GL/glut.h>
#include <vector>
#include "Window.h"
#include "Cube.h"
#include "Matrix4.h"
#include "main.h"

using namespace std;

int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here
bool Window::showCube = true;
int Window::showStuff = 0;
bool Window::altCamera = false;
bool Window::showBunny = true;
bool Window::read = false;
static vector<Vector3> points = vector<Vector3>();
static vector<Vector3> normals = vector<Vector3>();
static double sX,sY,sZ,lX,lY,lZ = 0;
int radius = 1;


//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback()
{
	if (showStuff == 2) {

	}
	else {
		if (showCube) {
			if (Globals::cube.getRotation())
				Globals::cube.spin(1.0);   // rotate cube; if it spins too fast try smaller values and vice versa
			else
				Globals::cube.spin(-1.0);
		}
		else {
			Globals::cube.bounce(width, height);
		}
	}
  displayCallback();         // call display routine to show the cube
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
  cerr << "Window::reshapeCallback called" << endl;
  width = w;
  height = h;
  glViewport(0, 0, w, h);  // set new viewport size
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, double(width)/(double)height, 1.0, 1000.0); // set perspective projection viewing frustum
  glTranslatef(0, 0, -20);    // move camera back 20 units so that it looks at the origin (or else it's in the origin)
  glMatrixMode(GL_MODELVIEW);
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
  glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode

  // Tell OpenGL what ModelView matrix to use:
  Matrix4 glmatrix;

  if (showStuff == 0) {

	  glEnable(GL_LIGHTING);
	  glmatrix = Globals::cube.getMatrix();
	  glmatrix.transpose();
	  glLoadMatrixd(glmatrix.getPointer());
	  if (showCube) {
		  Globals::cube.draw();
	  }
	  else {
		  glutSolidSphere(Globals::cube.radius, 30, 30);
	  }
  }
  else if (showStuff == 1) {
	  if (!altCamera) {
		  glDisable(GL_LIGHTING);
		  glMatrixMode(GL_MODELVIEW);
		  glmatrix = Globals::camera.getMatrix();
		  glmatrix.transpose();
		  glLoadMatrixd(glmatrix.getPointer());
	  }
	  else {
		  glDisable(GL_LIGHTING);
		  glMatrixMode(GL_MODELVIEW);
		  glmatrix = Globals::altCamera.getMatrix();
		  glmatrix.transpose();
		  glLoadMatrixd(glmatrix.getPointer());
	  }
	  // This data structure defines a simple house
	  Globals::house->draw();
  }
  else {
	  glEnable(GL_LIGHTING);
	  glmatrix = Globals::cube.getMatrix();
	  if (!read)
		  glmatrix.identity();
	  glmatrix.transpose();
	  glLoadMatrixd(glmatrix.getPointer());
	  ifstream file;
	  double x,y,z,nX,nY,nZ = 0;
	  Vector3 *normal, *point;
	  if (showBunny) {
		  file.open("bunny.xyz");
		  if (!read) {
			  normals.clear();
			  points.clear();
			  sX, sY, sZ, lX, lY, lZ = 0;
			  std::cout << "Read" << std::endl;
			  while (file >> x >> y >> z >> nX >> nY >> nZ) {
				  normal = new Vector3(nX, nY, nZ);
				  point = new Vector3(x, y, z);
				  normal->normalize();
				  normals.push_back(*normal);
				  points.push_back(*point);
				  if (x < sX)
					  sX = x;
				  if (x > lX)
					  lX = x;
				  if (y < sY)
					  sY = y;
				  if (y > lY)
					  lY = y;
				  if (z < sZ)
					  sZ = z;
				  if (z > lZ)
					  lZ = z;
			  }
			  cout << "smallest x, y, z are: " << sX << ", " << sY << ", " << sZ << endl;
			  cout << "biggest x, y, z are: " << lX << ", " << lY << ", " << lZ << endl;
		  }
		  glBegin(GL_POINTS);
		  for (int i = 0; i < normals.size(); i++) {
			  glNormal3d(normals[i].getX(), normals[i].getY(), normals[i].getZ());
			  glColor3d(normals[i].getX(), normals[i].getY(), normals[i].getZ());
			  glVertex3d(points[i].getX(), points[i].getY(), points[i].getZ());
		  }
		  glEnd();
		  if (!read) {
			  read = true;
			  double scale;
			  double Y = 40*tan(30*M_PI/180);
			  double X = Y * width / height;
			  double x = lX - sX;
			  double y = lY - sY;
			  if (x < y){
				  scale = Y / y;
				  Globals::cube.scale(scale);
			  }
			  else {
				  scale = X / x;
				  Globals::cube.scale(scale);
			  }
			  x = X/ 8;
			  y = Y / 2;
			  Globals::cube.move(x, -y, 0);
		  }
	  }
	  else {
		  file.open("dragon.xyz"); 
		  if (!read) {
			  sX, sY, sZ, lX, lY, lZ = 0;
			  normals.clear();
			  points.clear();
			  std::cout << "Read" << std::endl;
			  while (file >> x >> y >> z >> nX >> nY >> nZ) {
				  normal = new Vector3(nX, nY, nZ);
				  point = new Vector3(x, y, z);
				  normal->normalize();
				  normals.push_back(*normal);
				  points.push_back(*point);
				  if (x < sX)
					  sX = x;
				  if (x > lX)
					  lX = x;
				  if (y < sY)
					  sY = y;
				  if (y > lY)
					  lY = y;
				  if (z < sZ)
					  sZ = z;
				  if (z > lZ)
					  lZ = z;
			  }
			  cout << "smallest x, y, z are: " << sX << ", " << sY << ", " << sZ << endl;
			  cout << "biggest x, y, z are: " << lX << ", " << lY << ", " << lZ << endl;
		  }
		  glBegin(GL_POINTS);
		  for (int i = 0; i < normals.size(); i++) {
			  glNormal3d(normals[i].getX(), normals[i].getY(), normals[i].getZ());
			  glColor3d(normals[i].getX(), normals[i].getY(), normals[i].getZ());
			  glVertex3d(points[i].getX(), points[i].getY(), points[i].getZ());
		  }
		  glEnd();
		  if (!read) {
			  read = true;
			  double scale;
			  double Y = 40 * tan(30 * M_PI / 180);
			  double X = Y * width / height;
			  double x = lX - sX;
			  double y = lY - sY;
			  if (x < y){
				  scale = Y / y;
				  Globals::cube.scale(scale);
			  }
			  else {
				  scale = X / x;
				  Globals::cube.scale(scale);
			  }
			  x = x*scale/ 8;
			  y = y*scale / 2;
			  Globals::cube.move(x - 2, -y, 0);
		  }
		  }
		  
  }
  glFlush();  
  glutSwapBuffers();
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when users press specific keys on the keyboard
void Window::keyboardCallback(unsigned char key, int x, int y) {
	switch (key) {
	  // toggles direction of spin between clockwise and counterclockwise
	  case 't' :
		  Globals::cube.flipRotation();
		  break;
      // moves cube left
	  case 'X' :
		  Globals::cube.move(1, 0, 0);
		  break;
	  // moves cube right
	  case 'x' :
		  Globals::cube.move(-1, 0, 0);
		  break;
	  // moves cube down
	  case 'Y':
		  Globals::cube.move(0, 1, 0);
		  break;
	  // moves cube up
	  case 'y':
		  Globals::cube.move(0, -1, 0);
		  break;
	  // moves cube towards screen
	  case 'Z':
		  Globals::cube.move(0, 0, -1);
		  break;
	  // moves cube away from screen
	  case 'z':
		  Globals::cube.move(0, 0, 1);
		  break;
	  // resets cube position
	  case 'r':
		  Globals::cube.reset();
		  break;
	  // orbits cube counterclockwise
	  case 'O':
		  Globals::cube.orbit(true);
		  break;
	  // orbits cube clockwise
	  case 'o':
		  Globals::cube.orbit(false);
		  break;
	  // scales cube down
	  case 'S':
		  Globals::cube.scale(10.0/11.0);
		  break;
	  // scales cube up
	  case 's':
		  Globals::cube.scale(11.0/10.0);
		  break;
	  case 'b':
		  if (!showCube)
			  Globals::cube.reset();
		  showCube = !showCube;
		  break;
	  case 'q':
		  Globals::cube.spin(5.0);
		  break;
	  case 'Q':
		  Globals::cube.spin(-5.0);
		  break;
	  case 'w':
		  Globals::cube.spinX(5.0);
		  break;
	  case 'W':
		  Globals::cube.spinX(-5.0);
		  break;
	}
}
void Window::funcKeyboardCallback(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_F1:
		showStuff = 0;
		showCube = true;
		Globals::cube.reset();
		break;
	case GLUT_KEY_F2:
		showStuff = 1;
		altCamera = false;
		break;
	case GLUT_KEY_F3:
		showStuff = 1;
		altCamera = true;
		break;
	case GLUT_KEY_F4:
		showStuff = 2;
		showBunny = true;
		read = false;
		Globals::cube.reset();
		break;
	case GLUT_KEY_F5:
		showStuff = 2;
		showBunny = false;
		read = false;
		Globals::cube.reset();
		break;
	}
}
