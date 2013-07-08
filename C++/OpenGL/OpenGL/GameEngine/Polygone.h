#include <gl\glew.h>

struct Point
{
	double x, y;
};

struct Color
{
	double r, g, b;
};

class Polygone
{
	private:
		Point daten[500];
		int currentDataIndex;
		Color c;

	public:

		Polygone();
		void addPoint(double newX, double newY);
		void setColor( double r, double g, double b);
		void makeCircle(double radius);
		void draw(double addX, double addY);
		double getMaxXPoliLenght();
		double getMaxYPoliLenght();
};
