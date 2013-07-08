#ifndef BUFFER_H
#define BUFFER_H

#include <gl\glew.h>

#include <iostream>
#include <math.h>

class matrix;

class Vector3
{
public:
	GLdouble x;
	GLdouble y;
	GLdouble z;

	Vector3(double x, double y, double z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	};
};

struct pixel
{
	double x,y,z;
};

struct MyColor
{
	double r;
	double g;
	double b;
};

class Buffer
{
private:
	pixel bildschirm;
	MyColor col;
	pixel position[1000000];
	int currentpositionIndex;
	int maxIndex;

public:
	Buffer(pixel bildschirmPixel);
	Buffer(void);
	void createCube(int side, MyColor col );
	void createSphere( float radius, MyColor col );
	void updatePos( Vector3*);
	void updatePos( matrix m );
	void draw(void);
};


#endif