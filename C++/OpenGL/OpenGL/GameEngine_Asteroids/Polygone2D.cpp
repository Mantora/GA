#include "Polygone2D.h"

Polygone2D::Polygone2D()
{
	this->currentDataIndex = 0;

	this->c.r = 1;
	this->c.g = 0;
	this->c.b = 0;
}

// Einen neuen Punkt (newPoint) dem Datem hinzufügen und (currentDataIndex) erhöhen
void Polygone2D::addPoint(double newX, double newY)
{
	this->daten[currentDataIndex].x = newX;
	this->daten[currentDataIndex].y = newY;
	this->currentDataIndex++;
}

void Polygone2D::setColor(double r, double g, double b)
{
	this->c.r = r;
	this->c.g = g;
	this->c.b = b;
}

void Polygone2D::makeCircle(double radius, int anzahlSeiten)
{
	this->radius = radius;

	double PI = 3.1415926535897932384626433832795f;

	double DegToRad = PI / 180;

	double mx = 0;
	double my = 0;

	int seiten = 360/anzahlSeiten;

	for( int i = 0; i < 359; i+=seiten )
	{
		double x = mx + cos( i * DegToRad ) * radius ;
		double y = my + sin( i * DegToRad ) * radius ;
		this->addPoint( x, y);
	}
}

double Polygone2D::getRadius()
{
	return this->radius;
}

void Polygone2D::draw()
{
/*	//Marius: Vom Mittelpunkt aus linen zu jedem Punkt zeichnen
	double mid_x=0, mid_y=0;
	for( int i=0 ; i<this->currentDataIndex; i++ )
	{
      mid_x += this->daten[i].x;
	  mid_y += this->daten[i].y;
	}
    mid_x /= this->currentDataIndex;
    mid_y /= this->currentDataIndex;

	glColor3d( this->c.r, this->c.g, this->c.b );

	glBegin( GL_TRIANGLES );

		//for( int i = 0; i < this->currentDataIndex; i++)
		//	glVertex2d( this->daten[i].x, this->daten[i].y );
	
	int i, j;
	for( i=this->currentDataIndex-1, j=0 ; j<this->currentDataIndex; i=j, j++ )
	{
	  glVertex2d( this->daten[i].x, this->daten[i].y );
	  glVertex2d( this->daten[j].x, this->daten[j].y );
	  glVertex2d( mid_x, mid_y );
	}

	glEnd();
*/

	glColor3d( this->c.r, this->c.g, this->c.b );

	glBegin( GL_POLYGON );
		for( int i = 0; i < this->currentDataIndex; i++)
			glVertex2d( this->daten[i].x, this->daten[i].y );
	glEnd();
}

void Polygone2D::setPosition(double newX, double newY)
{
	for( int i = 0; i < this->currentDataIndex; i++ )
	{
		this->daten[i].x += newX;
		this->daten[i].y += newY;
	}
}
