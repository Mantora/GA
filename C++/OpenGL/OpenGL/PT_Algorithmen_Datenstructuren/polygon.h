//Diese Klasse verwaltet ein Polygon

#include "simple_types.h"
#include "Matrix.h"



class polygon
{
	private:
		int pointsCount;
		vertex* points;

		int textureCoordsCount;
		vertex* textureCoords;

		int colorIndex;

	public:
		//Konstruktors
		polygon();

		//SET
		void setPoints(const vertex* points, const int pointsCount );
		void setTextureCoords(const vertex* points, const int pointsCount );
		void setTexture( char* textureName );
		void setColorIndex( int colorIndex );

		//Anzeigefunktionen
		void display();

		//matrix funktionen
		void addMatrix( Matrix m );
};
 
