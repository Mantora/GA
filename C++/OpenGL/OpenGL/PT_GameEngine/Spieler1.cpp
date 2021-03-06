#include "Spieler1.h"

Spieler1::Spieler1( void )
{
	this->width = 0.5f;
	this->hight = 1.0f;
	this->deep = 1.0f;

	this->points = 0;
	this->ballHits = 0;

	this->localPosition = new vertex( 0,0,0 );
	this->v_globalPos = new vertex( 0,0,0 );

	this->faces = 6;

	this->polys = new polygon[ this->faces ];

	vertex* points = new vertex[4];
	//unten
	points[0] = vertex( -0.25, -0.5, -0.5 );
	points[1] = vertex( 0.25, -0.5, -0.5 );
	points[2] = vertex( 0.25, -0.5, 0.5 );
	points[3] = vertex( -0.25, -0.5, 0.5 );
	this->setNextPolygon( points, 4 );
	//oben
	points[0] = vertex( -0.25, 0.5, -0.5 );
	points[1] = vertex( -0.25, 0.5, 0.5 );
	points[2] = vertex( 0.25, 0.5, 0.5 );
	points[3] = vertex( 0.25, 0.5, -0.5 );
	this->setNextPolygon( points, 4 );
	//links
	points[0] = vertex( -0.25, 0.5, -0.5 );
	points[1] = vertex( -0.25, -0.5, -0.5 );
	points[2] = vertex( -0.25, -0.5, 0.5 );
	points[3] = vertex( -0.25, 0.5, 0.5 );
	this->setNextPolygon( points, 4 );
	//rechts
	points[0] = vertex( 0.25, 0.5, -0.5 );
	points[1] = vertex( 0.25, 0.5, 0.5 );
	points[2] = vertex( 0.25, -0.5, 0.5 );
	points[3] = vertex( 0.25, -0.5, -0.5 );
	this->setNextPolygon( points, 4 );
	//vorn
	points[0] = vertex( -0.25, 0.5, 0.5 );
	points[1] = vertex( -0.25, -0.5, 0.5 );
	points[2] = vertex( 0.25, -0.5, 0.5 );
	points[3] = vertex( 0.25, 0.5, 0.5 );
	this->setNextPolygon( points, 4 );
	//hinten
	points[0] = vertex( -0.25, 0.5, -0.5 );
	points[1] = vertex( 0.25, 0.5, -0.5 );
	points[2] = vertex( 0.25, -0.5, -0.5 );
	points[3] = vertex( -0.25, -0.5, -0.5 );
	this->setNextPolygon( points, 4 );

	//farbe erst setzen, nachdem man wei� wie viele polygone es gibt
	this->setPolygonColor( new vertex(1,0,0) );

	this->isBot = false;
}

Spieler1::~Spieler1( void )
{

}

void Spieler1::PerfectBotMovement( Ball* ball )
{
	//Der position des balles folgen:

	//bot zur�cktransformieren
	Matrix m_bot;
	m_bot.translate( this->localPosition->wx, this->localPosition->wy, (this->localPosition->wz + 20.0f ) );

	float DEV_offset4ColisionTesting = 0.0f;

	//position �bernehmen
	this->localPosition->wy = -ball->localPosition->wy;// + DEV_offset4ColisionTesting;
	this->localPosition->wz = -ball->localPosition->wz;

	this->v_globalPos->wy = ball->v_globalPos->wy;// + DEV_offset4ColisionTesting;
	this->v_globalPos->wz = ball->v_globalPos->wz;

	//bot wieder hintransformieren
	m_bot.translate( -this->localPosition->wx, -this->localPosition->wy, -(this->localPosition->wz + 20.0f) );

	//ausf�hren
	this->update_pos( m_bot );
}

//funktion zum �berpr�fen, ob der ball am spieler abprallt
void Spieler1::check4BallContakt( Ball* ball )
{
	if( ball->v_globalPos->wx < this->v_globalPos->wx + this->width*0.5f && ball->v_globalPos->wx > this->v_globalPos->wx - this->width*0.5f &&
		ball->v_globalPos->wy < this->v_globalPos->wy + this->hight*0.5f && ball->v_globalPos->wy > this->v_globalPos->wy - this->hight*0.5f &&
		ball->v_globalPos->wz < this->v_globalPos->wz + this->deep*0.5f && ball->v_globalPos->wz > this->v_globalPos->wz - this->deep*0.5f &&
		!ball->b_hasContactP1 )
	{
		this->ballHits++;
		ball->contactPlayer1();
	}
}
