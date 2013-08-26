//Klasse zum verwalten eines Polyeder
#pragma once

#include "simple_types.h"
#include "Matrix.h"

#include "polygon.h"

class Polyeder
{
	private:
		int currentPoly;

	public:
		polygon* polys;
		int faces;

		//kontruktor
		Polyeder();
		Polyeder( int maxFaces );

		//generate primitives
		void generatePrimitivCube();

		//set
		void setNextPolygon( const vertex* points, const int pointsCount );
		void setTextureCoords( const vertex* points, const int pointsCount );
		void setTexture( char* textureName );
		void setPolygonColor( int colorIndex );
		void setPolygonColor( vertex* v_RGBcolor );

		//get
		polygon* getPolys();

		//funktion zum bewegen
		void update_pos( Matrix m );

		//anzeigefunktion
		void display( void );
};
