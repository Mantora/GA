#pragma once

#include "polyeder.h"

#include "Ball.h"

class Spieler1 : public Polyeder
{
	private:
		float width;
		float hight;
		float deep;

	public:
		Spieler1( void );
		~Spieler1( void );

		//zur positionsbestimmung
		vertex* localPosition;
		vertex* v_globalPos;

		//BOT: auto follow ball
		void PerfectBotMovement( Ball* ball );

		//funktion zum überprüfen, ob der ball am spieler abprallt
		void check4BallContakt( Ball* ball );

		//punkte dieses spielers
		int points;
		int ballHits;

		bool isBot;
};

