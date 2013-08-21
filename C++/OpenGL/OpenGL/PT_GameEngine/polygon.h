//Diese Klasse verwaltet ein Polygon

#include "simple_types.h"
#include "Matrix.h"

#include "picture.h"

class polygon
{
	private:
		int pointsCount;
		vertex* points;

		int textureCoordsCount;
		vertex* textureCoords;

		int colorIndex;

		//textur
		picture texture;
		GLuint texture_id; //zur Identifikation der Textur

		//vector funktionen
		vertex VectCreate( vertex p_start, vertex p_end);
		double VectLenght( vertex p_vector);
		void VectNormalize( vertex& p_vector );
		double VectScalarProduct( vertex p_vector1, vertex p_vector2 );

		vertex normal;
	
		//funktion zum berechnen der normalen
		void calculateNormal( vertex p_vector1, vertex p_vector2 );
		double helligkeit;

		//zum Testen
		void drawNormal();

		//Weils schön ist:
		void drawMesh();

	public:
		char textureName[256];

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
 
