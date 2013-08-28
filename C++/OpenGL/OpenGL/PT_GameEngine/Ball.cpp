#include "Ball.h"

Ball::Ball( void )
{
	this->localPosition = new vertex( 0,0,0 );
	this->v_globalPos = new vertex( 0,0,0 );

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

void Ball::doRandomMovement( Spielfeld* spielfeld, vertex* rotations )
{
	//locale position updaten
	this->localPosition->wx += this->v_direction->wx;
	this->localPosition->wy += this->v_direction->wy;
	this->localPosition->wz += this->v_direction->wz;

	this->v_globalPos->wx += this->v_direction->wx;
	this->v_globalPos->wy += this->v_direction->wy;
	this->v_globalPos->wz += this->v_direction->wz;
/*
	this->m_movment->clear();
	this->m_movment->rotate_x( rotations->wx );
	this->m_movment->rotate_y( rotations->wy );
	this->m_movment->rotate_z( rotations->wz );
	(*this->v_direction) = (*this->m_movment) * (*this->v_direction);
*/
	//Y
/*	if( this->localPosition->wy > spielfeld->v_boundsOHL->wy || this->localPosition->wy < spielfeld->v_boundsUHL->wy )
	{
		//richtung umdrehen
		this->v_direction->wy *= (-1);

		//neue bewegungsmatrix def.
//		this->m_movment->clear();

		// this->m_movment->rows( user_ls.right, user_ls.up, user_ls.sight );
		this->m_movment->translate( this->v_direction->wx, this->v_direction->wy, this->v_direction->wz );
	}
*/

	//Z
/*	if( this->localPosition->wz > spielfeld->v_boundsOHL->wz || this->localPosition->wz < spielfeld->v_boundsUHL->wz )
	{
		//richtung umdrehen
		this->v_direction->wz *= (-1);

		//neue bewegungsmatrix def.
//		this->m_movment->clear();

		// this->m_movment->rows( user_ls.right, user_ls.up, user_ls.sight );
		this->m_movment->translate( this->v_direction->wx, this->v_direction->wy, this->v_direction->wz );
	}
*/
	this->update_pos( *this->m_movment );
}

//public funktion zum richtungsändern bei Spielerkontakt
void Ball::contactPlayer1()
{
	this->b_hasContactP1 = true;
	this->b_hasContactP2 = false;

	this->v_direction->wx *= (-1);
	this->v_direction->wz *= (-1);

	//neue bewegungsmatrix def.
	this->m_movment->clear();
	this->m_movment->translate( this->v_direction->wx, this->v_direction->wy, this->v_direction->wz );

	this->update_pos( *this->m_movment );
}

void Ball::contactPlayer2()
{
	this->b_hasContactP1 = false;
	this->b_hasContactP2 = true;

	this->v_direction->wx *= (-1);
	this->v_direction->wz *= (-1);

	//neue bewegungsmatrix def.
	this->m_movment->clear();
	this->m_movment->translate( this->v_direction->wx, this->v_direction->wy, this->v_direction->wz );

	this->update_pos( *this->m_movment );
}

void Ball::respawn()
{
	//neue richtung bestimmen
	this->localPosition = new vertex( 0,0,0 );
	if( this->b_hasContactP1 )
		this->v_direction = new vertex( -BALL_MOVMENT_SPEED, BALL_MOVMENT_SPEED, BALL_MOVMENT_SPEED );
	else
		this->v_direction = new vertex( BALL_MOVMENT_SPEED, BALL_MOVMENT_SPEED, BALL_MOVMENT_SPEED );

	this->b_hasContactP1 = false;
	this->b_hasContactP2 = false;
}

//aus DEBUG gründen
void Ball::DEBUG_drawDirection()
{
	glPushAttrib( GL_CURRENT_BIT );
	
	int scaling = 10;
	
	glBegin( GL_LINES );
		glColor3d( 0,1,0 );
		glVertex3d( 0, 0, -20 );
		glVertex3d( this->v_direction->wx * scaling, this->v_direction->wy * scaling, this->v_direction->wz * scaling);
	glEnd();

	glPopAttrib();
}