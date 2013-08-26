#include "Ball.h"

Ball::Ball( void )
{
	this->localPosition = new vertex(0,0,0);

	this->b_hasContactP1 = false;
	this->b_hasContactP2 = false;
	
	//setup random seed 4 moveing direction
	srand( time(0) );

	this->v_direction = new vertex( BALL_MOVMENT_SPEED, BALL_MOVMENT_SPEED, BALL_MOVMENT_SPEED );

	this->m_movment = new Matrix();
	this->m_movment->translate( this->v_direction->wx, this->v_direction->wy, this->v_direction->wz );

	this->faces = 6;

	this->polys = new polygon[ this->faces ];

	vertex* points = new vertex[4];
	//unten
	points[0] = vertex( -0.05, -0.05, -0.05 );
	points[1] = vertex( 0.05, -0.05, -0.05 );
	points[2] = vertex( 0.05, -0.05, 0.05 );
	points[3] = vertex( -0.05, -0.05, 0.05 );
	this->setNextPolygon( points, 4 );
	//oben
	points[0] = vertex( -0.05, 0.05, -0.05 );
	points[1] = vertex( -0.05, 0.05, 0.05 );
	points[2] = vertex( 0.05, 0.05, 0.05 );
	points[3] = vertex( 0.05, 0.05, -0.05 );
	this->setNextPolygon( points, 4 );
	//links
	points[0] = vertex( -0.05, 0.05, -0.05 );
	points[1] = vertex( -0.05, -0.05, -0.05 );
	points[2] = vertex( -0.05, -0.05, 0.05 );
	points[3] = vertex( -0.05, 0.05, 0.05 );
	this->setNextPolygon( points, 4 );
	//rechts
	points[0] = vertex( 0.05, 0.05, -0.05 );
	points[1] = vertex( 0.05, 0.05, 0.05 );
	points[2] = vertex( 0.05, -0.05, 0.05 );
	points[3] = vertex( 0.05, -0.05, -0.05 );
	this->setNextPolygon( points, 4 );
	//vorn
	points[0] = vertex( -0.05, 0.05, 0.05 );
	points[1] = vertex( -0.05, -0.05, 0.05 );
	points[2] = vertex( 0.05, -0.05, 0.05 );
	points[3] = vertex( 0.05, 0.05, 0.05 );
	this->setNextPolygon( points, 4 );
	//hinten
	points[0] = vertex( -0.05, 0.05, -0.05 );
	points[1] = vertex( 0.05, 0.05, -0.05 );
	points[2] = vertex( 0.05, -0.05, -0.05 );
	points[3] = vertex( -0.05, -0.05, -0.05 );
	this->setNextPolygon( points, 4 );

	//farbe erst setzen, nachdem man weiß wie viele polygone es gibt
	this->setPolygonColor( new vertex(0,1,0) );
}

Ball::~Ball( void )
{

}

void Ball::doRandomMovement( Spielfeld* spielfeld )
{
	//locale position updaten
	this->localPosition->wx += this->v_direction->wx;
	this->localPosition->wy += this->v_direction->wy;
	this->localPosition->wz += this->v_direction->wz;

/*	//X
	if( this->localPosition->wx > spielfeld->v_boundsOHR->wx ||
		this->localPosition->wx < spielfeld->v_boundsOHL->wx )
	{
		//richtung umdrehen
		this->v_direction->wx *= (-1);

		//neue bewegungsmatrix def.
		this->m_movment->clear();
		this->m_movment->translate( this->v_direction->wx, this->v_direction->wy, this->v_direction->wz );
	}
*/
	//Y
	if( this->localPosition->wy > spielfeld->v_boundsOHL->wy ||
		this->localPosition->wy < spielfeld->v_boundsUHL->wy )
	{
		//richtung umdrehen
		this->v_direction->wy *= (-1);

		//neue bewegungsmatrix def.
		this->m_movment->clear();
		this->m_movment->translate( this->v_direction->wx, this->v_direction->wy, this->v_direction->wz );

	}

	//Z
	if( this->localPosition->wz > spielfeld->v_boundsOVL->wz ||
		this->localPosition->wz < spielfeld->v_boundsUHL->wz )
	{
		//richtung umdrehen
		this->v_direction->wz *= (-1);

		//neue bewegungsmatrix def.
		this->m_movment->clear();
		this->m_movment->translate( this->v_direction->wx, this->v_direction->wy, this->v_direction->wz );

	}

	this->update_pos( *this->m_movment );
}

//public funktion zum richtungsändern bei Spielerkontakt
void Ball::contactPlayer1()
{
	this->v_direction->wx *= (-1);
	this->v_direction->wz *= (-1);

	//neue bewegungsmatrix def.
	this->m_movment->clear();
	this->m_movment->translate( this->v_direction->wx, this->v_direction->wy, this->v_direction->wz );

	this->update_pos( *this->m_movment );
}

void Ball::contactPlayer2()
{
	this->v_direction->wx *= (-1);
	this->v_direction->wz *= (-1);

	//neue bewegungsmatrix def.
	this->m_movment->clear();
	this->m_movment->translate( this->v_direction->wx, this->v_direction->wy, this->v_direction->wz );

	this->update_pos( *this->m_movment );
}

void Ball::respawn()
{
	this->b_hasContactP1 = false;
	this->b_hasContactP2 = false;

	this->m_movment->clear();
	this->m_movment->translate( -this->localPosition->wx, -this->localPosition->wy, -this->localPosition->wz );
	this->update_pos( *this->m_movment );

	//neue richtung bestimmen
	this->localPosition = new vertex( 0,0,0 );
	this->v_direction = new vertex( BALL_MOVMENT_SPEED, BALL_MOVMENT_SPEED, BALL_MOVMENT_SPEED );

//	this->m_movment = new Matrix();
	this->m_movment->clear();
	this->m_movment->translate( this->v_direction->wx, this->v_direction->wy, this->v_direction->wz );
}
