#include "Polygone.h"

Polygone::Polygone()
{
	this->currentDataIndex = 0;

	this->c.r = 1;
	this->c.g = 0;
	this->c.b = 0;
}

// Einen neuen Punkt (newPoint) dem Datem hinzufügen und (currentDataIndex) erhöhen
void Polygone::addPoint(double newX, double newY)
{
	this->daten[currentDataIndex].x = newX;
	this->daten[currentDataIndex].y = newY;
	this->currentDataIndex++;
}

void Polygone::setColor(double r, double g, double b)
{
	this->c.r = r;
	this->c.g = g;
	this->c.b = b;
}

void Polygone::makeCircle(double radius)
{
	//to implement
	
	//Kreis:
	//x = Cos
	//y = sin
}

void Polygone::draw(double addX, double addY)
{
	glColor3d( this->c.r,this->c.g,this->c.b );

	glBegin( GL_POLYGON );
		for( int i = 0; i < this->currentDataIndex; i++)
			glVertex2d( this->daten[i].x+addX, this->daten[i].y+addY );
	glEnd();
}

double Polygone::getMaxXPoliLenght()
{
	double max = 0;
	for( int i = 0; i < this->currentDataIndex; i++)
	{
		if( this->daten[i].x > max )
			max = this->daten[i].x;
	}
	return max;
}

double Polygone::getMaxYPoliLenght()
{
	double max = 0;
	for( int i = 0; i < this->currentDataIndex; i++)
	{
		if( this->daten[i].y > max )
			max = this->daten[i].y;
	}
	return max;
}


