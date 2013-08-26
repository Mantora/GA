#include "Spielfeld.h"

Spielfeld::Spielfeld( void )
{
	this->faces = 6;

	this->polys = new polygon[ this->faces ];

	this->v_boundsUHL = new vertex( -5, -2.5, -2.5 );
	this->v_boundsUVL = new vertex( 5, -2.5, -2.5 );
	this->v_boundsUVR = new vertex( 5, -2.5, 2.5 );
	this->v_boundsUHR = new vertex( -5, -2.5, 2.5 );

	this->v_boundsOHL = new vertex( -5, 2.5, -2.5 );
	this->v_boundsOVL = new vertex( -5, 2.5, 2.5 );
	this->v_boundsOVR = new vertex( 5, 2.5, 2.5 );
	this->v_boundsOHR = new vertex( 5, 2.5, -2.5 );

	vertex* points = new vertex[4];
	//unten
	points[0] = *this->v_boundsUHL;
	points[1] = *this->v_boundsUVL;
	points[2] = *this->v_boundsUVR;
	points[3] = *this->v_boundsUHR;
	this->setNextPolygon( points, 4 );
	//oben
	points[0] = *this->v_boundsOHL;
	points[1] = *this->v_boundsOVL;
	points[2] = *this->v_boundsOVR;
	points[3] = *this->v_boundsOHR;
	this->setNextPolygon( points, 4 );
	//links
	points[0] = *this->v_boundsOHL;
	points[1] = *this->v_boundsUHL;
	points[2] = *this->v_boundsUHR;
	points[3] = *this->v_boundsOVL;
	this->setNextPolygon( points, 4 );
	//rechts
	points[0] = *this->v_boundsOHR;
	points[1] = *this->v_boundsOVR;
	points[2] = *this->v_boundsUVR;
	points[3] = *this->v_boundsUVL;
	this->setNextPolygon( points, 4 );
	//vorn
	points[0] = *this->v_boundsOVL;
	points[1] = *this->v_boundsUHR;
	points[2] = *this->v_boundsUVR;
	points[3] = *this->v_boundsOVR;
	this->setNextPolygon( points, 4 );
	//hinten
	points[0] = *this->v_boundsOHL;
	points[1] = *this->v_boundsOHR;
	points[2] = *this->v_boundsUVL;
	points[3] = *this->v_boundsUHL;
	this->setNextPolygon( points, 4 );

	//farbe erst setzen, nachdem man weiß wie viele polygone es gibt
	this->setPolygonColor( new vertex(1,1,1) );
}

Spielfeld::~Spielfeld( void )
{

}
