#include <gl\glew.h>

#include <math.h> // für sqrt()

struct Point
{
	double x, y;
};

struct Color
{
	double r, g, b;
};

class Polygone2D
{
	private:
		Point daten[500];
		int currentDataIndex;
		Color c;
		double radius;
	public:

		Polygone2D();
		void addPoint(double newX, double newY);
		void setColor( double r, double g, double b);
		void makeCircle(double radius, int anzahlSeiten = 360);
		double getRadius();
		void draw();

		void setPosition(double newX, double newY);
		Point getPosition();
};
