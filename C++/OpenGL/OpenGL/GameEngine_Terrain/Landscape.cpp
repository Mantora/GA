#pragma once

#include "Landscape.h"

Landscape::Landscape( int size )
{
	this->size = size;

	this->translation = new vertex(0,0,0);

	this->points = 0;
	this->points = new vertex[ size * size ]; // array mit size*size elementen

	double fix = (size - 1) * 0.5f;

	//dyn Array füllen
	for( int x = 0; x < size; x++ )
	{
		for( int y = 0; y < size; y++ )
		{
			this->points[ size * y + x ].wx = x - fix;
			this->points[ size * y + x ].wy = y - fix;
			this->points[ size * y + x ].wz = 0 ;
		}
	}
}

Landscape::~Landscape()
{
	delete [] points;
}

void Landscape::draw()
{
	glBegin( GL_POINTS );

	for( int x = 0; x < this->size; x++ )
	{
		for( int y = 0; y < this->size; y++ )
		{
			vertex current = this->points[ size * y + x ];

			glVertex3d( current.wx, 
						current.wy, 
						current.wz );
		}
	}

	glEnd();
}

//matrixfunktionen
void Landscape::updatePos( matrix m )
{
	int lengt = this->size * this->size;

	for( int i = 0; i < lengt; i++)
	{
		this->points[i] = m * this->points[i];
	}
}

//funktionen zum speichern der verschiebung
void Landscape::setTranslation( double x, double y, double z )
{
	this->translation->wx += x;
	this->translation->wy += y;
	this->translation->wz += z;
}

vertex* Landscape::getTranslation()
{
	return this->translation;
}

