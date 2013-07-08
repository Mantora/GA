//Diese Klasse verwaltet ein Polygon

#include "simple_types.h"
#include "matrix.h"

class polygon
{
	private:
		int pointsCount;
		vertex* points;

	public:
		//Konstruktors
		polygon();

		//SET
		void setPoints(const vertex* points, const int pointsCount );

		//Anzeigefunktionen
		void display();

		//matrix funktionen
		void addMatrix( matrix m );
};
 
