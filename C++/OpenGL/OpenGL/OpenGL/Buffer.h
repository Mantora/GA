#include <gl\glew.h>

class Vector2
{
public:
	GLdouble x;
	GLdouble y;

	Vector2(GLdouble x, GLdouble y)
	{
		this->x = x;
		this->y = y;
	};
};

struct pixel
{
	GLdouble x,y,z;
};

struct MyColor
{
	GLdouble r;
	GLdouble g;
	GLdouble b;
};

class Buffer
{
private:
	pixel bildschirm;
	MyColor col;
	pixel array[1000000];
	int currentArrayIndex;
	int maxIndex;

public:
	int side;
	Buffer(pixel bildschirmPixel);
	Buffer(void);
	void createCube(int side, MyColor col );
	void updatePos( Vector2*);
	void draw(void);
};
