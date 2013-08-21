#include "Polyeder.h"

//kontruktor
Polyeder::Polyeder()
{
	this->faces = 0;
	this->polys = NULL;

	this->currentPoly = 0;
}

Polyeder::Polyeder( int maxFaces )
{
	this->faces = maxFaces;
	this->polys = new polygon[maxFaces];

	this->currentPoly = 0;
}

//generate primitives
void Polyeder::generatePrimitivCube()
{
	this->faces = 6;
	this->polys = new polygon[ this->faces ];

	vertex* points = new vertex[4];
	//unten
	points[0] = vertex( -1, -1, -1 );
	points[1] = vertex( 1, -1, -1 );
	points[2] = vertex( 1, -1, 1 );
	points[3] = vertex( -1, -1, 1 );
	this->setNextPolygon( points, 4 );
	//oben
	points[0] = vertex( -1, 1, -1 );
	points[1] = vertex( -1, 1, 1 );
	points[2] = vertex( 1, 1, 1 );
	points[3] = vertex( 1, 1, -1 );
	this->setNextPolygon( points, 4 );
	//links
	points[0] = vertex( -1, 1, -1 );
	points[1] = vertex( -1, -1, -1 );
	points[2] = vertex( -1, -1, 1 );
	points[3] = vertex( -1, 1, 1 );
	this->setNextPolygon( points, 4 );
	//rechts
	points[0] = vertex( 1, 1, -1 );
	points[1] = vertex( 1, 1, 1 );
	points[2] = vertex( 1, -1, 1 );
	points[3] = vertex( 1, -1, -1 );
	this->setNextPolygon( points, 4 );
	//vorn
	points[0] = vertex( -1, 1, 1 );
	points[1] = vertex( -1, -1, 1 );
	points[2] = vertex( 1, -1, 1 );
	points[3] = vertex( 1, 1, 1 );
	this->setNextPolygon( points, 4 );
	//hinten
	points[0] = vertex( -1, 1, -1 );
	points[1] = vertex( 1, 1, -1 );
	points[2] = vertex( 1, -1, -1 );
	points[3] = vertex( -1, -1, -1 );
	this->setNextPolygon( points, 4 );
}

//set
void Polyeder::setNextPolygon( const vertex* points, const int pointsCount )
{
	this->polys[ this->currentPoly ].setPoints( points, pointsCount );

	this->currentPoly++;
}

void Polyeder::setTextureCoords( const vertex* points, const int pointsCount )
{
	this->polys[ this->currentPoly ].setTextureCoords( points, pointsCount );
}

void Polyeder::setTexture( char* textureName )
{
	this->polys[ this->currentPoly ].setTexture( textureName );
}

void Polyeder::setPolygonColor( int colorIndex )
{
	this->polys[ this->currentPoly ].setColorIndex( colorIndex );
}

//get
polygon* Polyeder::getPolys()
{
	return this->polys;
}


//funktion zum bewegen
void Polyeder::update_pos( Matrix m )
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
