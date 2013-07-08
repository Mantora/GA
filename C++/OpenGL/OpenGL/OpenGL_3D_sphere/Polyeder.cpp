#include "Polyeder.h"

//kontruktor
Polyeder::Polyeder( int maxFaces )
{
	this->faces = maxFaces;
	this->polys = new polygon[maxFaces];

	this->currentPoly = 0;
}

//set
void Polyeder::setNextPolygon( const vertex* points, const int pointsCount )
{
	this->polys[ this->currentPoly ].setPoints( points, pointsCount );

	this->currentPoly++;
}

//funktion zum bewegen
void Polyeder::update_pos( matrix m )
{
	for( int i = 0; i < this->faces; i++)
	{
		this->polys[i].addMatrix( m );
	}
}

//anzeigefunktion
void Polyeder::display( void )
{
	for( int i = 0; i < this->faces; i++)
	{
		this->polys[i].display();
	}
//	for( long i=0 ; i<6 ; i++ )
//		ps[ i ].display( vs );
// polyhedron::vs[] ist das Array, das alle Vertices des Polyeders enthält
}
