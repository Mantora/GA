//Klasse zum verwalten eines Polyeder

#include "polygon.h"
#include "simple_types.h"
#include "Matrix.h"

class Polyeder
{
	private:
		int faces;
		polygon* polys;
		int currentPoly;

	public:
		//kontruktor
		Polyeder( int maxFaces );

		//set
		void setNextPolygon( const vertex* points, const int pointsCount );

		//funktion zum bewegen
		void update_pos( Matrix m );

		//anzeigefunktion
		void display( void );
};
