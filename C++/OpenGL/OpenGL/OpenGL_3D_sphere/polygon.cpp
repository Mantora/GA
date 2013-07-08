#include "polygon.h"

//Konstruktors
polygon::polygon()
{
	this->pointsCount = 0;
	this->points = 0;
}

//SET
void polygon::setPoints( const vertex* points, const int pointsCount )
{
	this->pointsCount = pointsCount;
	this->points = new vertex[ pointsCount ];

	for( int i = 0; i < pointsCount; i++ )
	{
		this->points[i].wx = points[i].wx;
		this->points[i].wy = points[i].wy;
		this->points[i].wz = points[i].wz;
	}
}

//Anzeigefunktionen
void polygon::display()
{
	// Farbe des Polygons festlegen
	glColor3d(1,0,0);
	glBegin( GL_TRIANGLE_FAN );

	for( long i = 0; i < this->pointsCount; i++ )
	{
		vertex pos = this->points[ i ];
		glVertex3d( pos.wx, pos.wy, pos.wz );
	}
	glEnd();
}

//matrix funktionen
void polygon::addMatrix( matrix m )
{
	for( int i = 0; i < this->pointsCount; i++ )
	{
		this->points[i] = m * this->points[i];
	}

		
	//ToDelet: sind alle Vertex in "vertex* points" ?
/*	vertex test[20];
	for( int i = 0; i < pointsCount; i++ )
		test[i] = this->points[i];
*/
}
