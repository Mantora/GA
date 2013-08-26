#include "Spieler2.h"

Spieler2::Spieler2( void )
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

	//farbe erst setzen, nachdem man weiß wie viele polygone es gibt
	this->setPolygonColor( new vertex(0,0,1) );

	this->isBot = true;
}

Spieler2::~Spieler2( void )
{
}

void Spieler2::PerfectBotMovement( Ball* ball )
{
	//Der position des balles folgen:

	//bot zurücktransformieren
	Matrix m_bot;
	m_bot.translate( this->localPosition->wx, this->localPosition->wy, (this->localPosition->wz + 20 ) );

	float DEV_offset4ColisionTesting = 0.0f;

	//position übernehmen
	this->localPosition->wx = 0;
	this->localPosition->wy = -ball->localPosition->wy + DEV_offset4ColisionTesting;
	this->localPosition->wz = -ball->localPosition->wz;

	this->v_globalPos->wy = ball->localPosition->wy + DEV_offset4ColisionTesting;
	this->v_globalPos->wz = ball->localPosition->wz;

	//bot wieder hintransformieren
	m_bot.translate( -this->localPosition->wx, -this->localPosition->wy, -(this->localPosition->wz + 20) );

	//ausführen
	this->update_pos( m_bot );
}


//funktion zum überprüfen, ob der ball am spieler abprallt
void Spieler2::check4BallContakt( Ball* ball )
{
	if( ball->localPosition->wx > this->v_globalPos->wx - this->width*0.5f &&
		ball->localPosition->wy < this->v_globalPos->wy + this->hight*0.5f && ball->localPosition->wy > this->v_globalPos->wy - this->hight*0.5f &&
		ball->localPosition->wz < this->v_globalPos->wz + this->deep*0.5f && ball->localPosition->wz > this->v_globalPos->wz - this->deep*0.5f &&
		!ball->b_hasContactP2 )
	{
		ball->b_hasContactP2 = true;
		ball->b_hasContactP1 = false;
		this->ballHits++;
		ball->contactPlayer2();
	}
}
