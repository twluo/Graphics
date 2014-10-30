#ifndef _VECTOR4_H_
#define _VECTOR4_H_

#include "string"

class Vector4 {
protected:
	double v[4];   // array elements

public:

	
	Vector4(double, double, double, double);
	Vector4& operator+(const Vector4&);
	Vector4& operator-(const Vector4&);
	double getValue(int);
	void dehomogenize();
	void print(std::string);

	void setValue(int, double);
	void translate(double, double, double);
	void reset();
	double get(int);
};

#endif